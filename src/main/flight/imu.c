// Inertial Measurement Unit (IMU)

#include <stdbool.h>
#include <stdint.h>
#include <math.h>

#include "platform.h"

#include "build/build_config.h"
#include "build/debug.h"

#include "common/axis.h"

#include "pg/pg.h"
#include "pg/pg_ids.h"

#include "drivers/time.h"

#include "fc/runtime_config.h"

#include "flight/imu.h"
#include "flight/mixer.h"
#include "flight/pid.h"

#include "io/gps.h"
#include "io/beeper.h"

#include "sensors/acceleration.h"
#include "sensors/barometer.h"
#include "sensors/compass.h"
#include "sensors/gyro.h"
#include "sensors/sensors.h"

#ifdef USE_ACC_IMUF9001
#include "drivers/accgyro/accgyro_imuf9001.h"
#endif

#if (defined(SIMULATOR_BUILD) && defined(SIMULATOR_MULTITHREAD))
#include <stdio.h>
#include <pthread.h>

static pthread_mutex_t imuUpdateLock;

#if defined(SIMULATOR_IMU_SYNC)
static uint32_t imuDeltaT = 0;
static bool imuUpdated = false;
#endif

#define IMU_LOCK pthread_mutex_lock(&imuUpdateLock)
#define IMU_UNLOCK pthread_mutex_unlock(&imuUpdateLock)

#else

#define IMU_LOCK
#define IMU_UNLOCK

#endif

static float smallAngleCosZ;
static imuRuntimeConfig_t imuRuntimeConfig;

// sensor frame relative to earth frame
quaternion qAttitude = QUATERNION_INITIALIZE;
STATIC_UNIT_TESTED quaternionProducts qpAttitude = QUATERNION_PRODUCTS_INITIALIZE;
// headfree
quaternion qHeadfree = QUATERNION_INITIALIZE;
quaternion qOffset = QUATERNION_INITIALIZE;

// euler angles resolution = 0.1 degree   180 deg = 1800
attitudeEulerAngles_t attitude = EULER_INITIALIZE;

PG_REGISTER_WITH_RESET_TEMPLATE(imuConfig_t, imuConfig, PG_IMU_CONFIG, 0);

PG_RESET_TEMPLATE(imuConfig_t, imuConfig,
    .dcm_kp = 7013,
    .dcm_ki = 13,
    .small_angle = 25,
    .accDeadband = {.xy = 40, .z= 40},
    .acc_unarmedcal = 1
);

void imuConfigure(void) {
    imuRuntimeConfig.dcm_kp = imuConfig()->dcm_kp / 10000.0f;
    imuRuntimeConfig.dcm_ki = imuConfig()->dcm_ki / 10000.0f;
    imuRuntimeConfig.acc_unarmedcal = imuConfig()->acc_unarmedcal;
    imuRuntimeConfig.small_angle = imuConfig()->small_angle;
}

void imuInit(void) {
    smallAngleCosZ = cos_approx(degreesToRadians(imuRuntimeConfig.small_angle));

#if (defined(SIMULATOR_BUILD) && defined(SIMULATOR_MULTITHREAD))
    if (pthread_mutex_init(&imuUpdateLock, NULL) != 0) {
        printf("Create imuUpdateLock error!\n");
    }
#endif
}

static float imuUseFastGains(void) {
   if (!ARMING_FLAG(ARMED)) {
        return (17.0f);
    }
    else {
        //onboard beeper influences vAcc
        if (isBeeperOn()) {
          return (0.17f);
        } else {
          return (1.0f);
        }
    }
}

#ifndef SITL
#if (defined(USE_MAG) || defined(USE_GPS))
static void applyVectorError(float ez_ef, quaternion *vError){
    // Rotate mag error vector back to BF and accumulate
    vError->x += (2.0f * (qpAttitude.xz + -qpAttitude.wy)) * ez_ef;
    vError->y += (2.0f * (qpAttitude.yz - -qpAttitude.wx)) * ez_ef;
    vError->z += (1.0f - 2.0f * qpAttitude.xx - 2.0f * qpAttitude.yy) * ez_ef;
}
#endif

static void applyAccError(quaternion *vAcc, quaternion *vError) {
    quaternionNormalize(vAcc);
    // Error is sum of cross product between estimated direction and measured direction of gravity
    vError->x += (vAcc->y * (1.0f - 2.0f * qpAttitude.xx - 2.0f * qpAttitude.yy) - vAcc->z * (2.0f * (qpAttitude.yz - -qpAttitude.wx)));
    vError->y += (vAcc->z * (2.0f * (qpAttitude.xz + -qpAttitude.wy)) - vAcc->x * (1.0f - 2.0f * qpAttitude.xx - 2.0f * qpAttitude.yy));
    vError->z += (vAcc->x * (2.0f * (qpAttitude.yz - -qpAttitude.wx)) - vAcc->y * (2.0f * (qpAttitude.xz + -qpAttitude.wy)));
}

static void applySensorCorrection(quaternion *vError){
#if (!defined(USE_MAG) && !defined(USE_GPS))
    UNUSED(vError);
#endif

#ifdef USE_GPS
    if (sensors(SENSOR_GPS) && STATE(GPS_FIX) && gpsSol.numSat >= 5 && gpsSol.groundSpeed >= 600) {
        float courseOverGround = DECIDEGREES_TO_RADIANS(gpsSol.groundCourse);
        static bool hasInitializedGPSHeading = false;
        // In case of a fixed-wing aircraft we can use GPS course over ground to correct heading
        if(!STATE(FIXED_WING))
        {
            float tiltDirection = atan2_approx(attitude.values.roll, attitude.values.pitch); // For applying correction to heading based on craft tilt in 2d space
            courseOverGround += tiltDirection;

            if (!hasInitializedGPSHeading && GPS_distanceToHome > 50) { // Initially correct the gps heading, we can deal with gradual corrections later
                attitude.values.yaw = RADIANS_TO_DECIDEGREES(courseOverGround);
                hasInitializedGPSHeading = true;
            }
        }
        // Use raw heading error (from GPS or whatever else)
        while (courseOverGround >  M_PIf) courseOverGround -= (2.0f * M_PIf);
        while (courseOverGround < -M_PIf) courseOverGround += (2.0f * M_PIf);

        // William Premerlani and Paul Bizard, Direction Cosine Matrix IMU - Eqn. 22-23
        // (Rxx; Ryx) - measured (estimated) heading vector (EF)
        // (cos(COG), sin(COG)) - reference heading vector (EF)
        // error is cross product between reference heading and estimated heading (calculated in EF)
        courseOverGround = -(float)sin_approx(courseOverGround) * (1.0f - 2.0f * qpAttitude.yy - 2.0f * qpAttitude.zz) - cos_approx(courseOverGround) * (2.0f * (qpAttitude.xy - -qpAttitude.wz));
        applyVectorError(courseOverGround, vError);
    }
#endif

#ifdef USE_MAG
    if (sensors(SENSOR_MAG)) {
      quaternion vMagAverage;
      // assumption  magnetic field is perpendicular to gravity (ignore Z-component in EF).
      // magnetic field correction will only affect heading not roll/pitch angles

      compassGetAverage(&vMagAverage);
      if (compassIsHealthy(&vMagAverage)){
        quaternionNormalize(&vMagAverage);

        // (hx; hy; 0) - measured mag field vector in EF (assuming Z-component is zero)
        // (bx; 0; 0) - reference mag field vector heading due North in EF (assuming Z-component is zero)
        const float hx = (1.0f - 2.0f * qpAttitude.yy - 2.0f * qpAttitude.zz) * vMagAverage.x + (2.0f * (qpAttitude.xy + -qpAttitude.wz)) * vMagAverage.y + (2.0f * (qpAttitude.xz - -qpAttitude.wy)) * vMagAverage.z;
        const float hy = (2.0f * (qpAttitude.xy - -qpAttitude.wz)) * vMagAverage.x + (1.0f - 2.0f * qpAttitude.xx - 2.0f * qpAttitude.zz) * vMagAverage.y + (2.0f * (qpAttitude.yz + -qpAttitude.wx)) * vMagAverage.z;
        const float bx = sqrtf(sq(hx) + sq(hy));

        // magnetometer error is cross product between estimated magnetic north and measured magnetic north (calculated in EF)
        applyVectorError(-(float)(hy * bx), vError);
      }

    }
#endif
}
#endif

static void imuMahonyAHRSupdate(float dt, quaternion *vGyro, quaternion *vError) {
    quaternion vKpKi = VECTOR_INITIALIZE;
    static quaternion vIntegralFB = VECTOR_INITIALIZE;
    quaternion qBuff, qDiff;

    // scale dcm to converge faster (if not armed)
    const float dcmKpGain = imuRuntimeConfig.dcm_kp * imuUseFastGains();
    const float dcmKiGain = imuRuntimeConfig.dcm_ki * imuUseFastGains();

    // calculate integral feedback
    if (imuRuntimeConfig.dcm_ki > 0.0f) {
        vIntegralFB.x += dcmKiGain * vError->x * dt;
        vIntegralFB.y += dcmKiGain * vError->y * dt;
        vIntegralFB.z += dcmKiGain * vError->z * dt;
    } else {
        quaternionInitVector(&vIntegralFB);
    }

    // apply proportional and integral feedback
    vKpKi.x += dcmKpGain * vError->x + vIntegralFB.x;
    vKpKi.y += dcmKpGain * vError->y + vIntegralFB.y;
    vKpKi.z += dcmKpGain * vError->z + vIntegralFB.z;

    // vGyro integration
    // PCDM Acta Mech 224, 3091–3109 (2013)
    const float vGyroModulus = quaternionModulus(vGyro);
    // reduce gyro noise integration integrate only above vGyroStdDevModulus
    if (vGyroModulus > vGyroStdDevModulus) {
        qDiff.w = cosf(vGyroModulus * 0.5f * dt);
        qDiff.x = sinf(vGyroModulus * 0.5f * dt) * (vGyro->x / vGyroModulus);
        qDiff.y = sinf(vGyroModulus * 0.5f * dt) * (vGyro->y / vGyroModulus);
        qDiff.z = sinf(vGyroModulus * 0.5f * dt) * (vGyro->z / vGyroModulus);
        quaternionMultiply(&qAttitude, &qDiff, &qAttitude);
    }

    // vKpKi integration
    // Euler integration (q(n+1) is determined by a first-order Taylor expansion) (old bf method adapted)
    const float vKpKiModulus = quaternionModulus(&vKpKi);
    if (vKpKiModulus > 0.007f) {
        qDiff.w = 0;
        qDiff.x = vKpKi.x * 0.5f * dt;
        qDiff.y = vKpKi.y * 0.5f * dt;
        qDiff.z = vKpKi.z * 0.5f * dt;
        quaternionMultiply(&qAttitude, &qDiff, &qBuff);
        quaternionAdd(&qAttitude, &qBuff, &qAttitude);
        quaternionNormalize(&qAttitude);
    }

    // compute caching products
    quaternionComputeProducts(&qAttitude, &qpAttitude);

    DEBUG_SET(DEBUG_IMU, DEBUG_IMU0, lrintf(vGyroModulus * 1000));
    DEBUG_SET(DEBUG_IMU, DEBUG_IMU1, lrintf(vKpKiModulus * 1000));
    //DEBUG_SET(DEBUG_IMU, DEBUG_IMU3, lrintf(quaternionModulus(&qAttitude) * 1000));
    DEBUG_SET(DEBUG_IMU, DEBUG_IMU3, lrintf(vGyroStdDevModulus * 1000));
}

STATIC_UNIT_TESTED void imuUpdateEulerAngles(void) {
    quaternionProducts buffer;

    if (FLIGHT_MODE(HEADFREE_MODE)) {
        quaternionMultiply(&qOffset, &qAttitude, &qHeadfree);
        quaternionComputeProducts(&qHeadfree, &buffer);
    } else {
        quaternionComputeProducts(&qAttitude, &buffer);
    }

    attitude.values.roll = lrintf(atan2_approx((+2.0f * (buffer.wx + buffer.yz)), (+1.0f - 2.0f * (buffer.xx + buffer.yy))) * (1800.0f / M_PIf));
    attitude.values.pitch = lrintf(((0.5f * M_PIf) - acos_approx(+2.0f * (buffer.wy - buffer.xz))) * (1800.0f / M_PIf));
    attitude.values.yaw = lrintf((-atan2_approx((+2.0f * (buffer.wz + buffer.xy)), (+1.0f - 2.0f * (buffer.yy + buffer.zz))) * (1800.0f / M_PIf)));

    if (attitude.values.yaw < 0) {
        attitude.values.yaw += 3600;
    }

    if (getCosTiltAngle() > smallAngleCosZ) {
        ENABLE_STATE(SMALL_ANGLE);
    } else {
        DISABLE_STATE(SMALL_ANGLE);
    }
}

static void imuCalculateEstimatedAttitude(timeUs_t currentTimeUs) {
    static timeUs_t previousIMUUpdateTime;
    const timeDelta_t deltaT = currentTimeUs - previousIMUUpdateTime;
    previousIMUUpdateTime = currentTimeUs;

#if defined(SIMULATOR_BUILD) && defined(SKIP_IMU_CALC)
    UNUSED(imuMahonyAHRSupdate);
#else

#if defined(SIMULATOR_BUILD) && defined(SIMULATOR_IMU_SYNC)
//  printf("[imu]deltaT = %u, imuDeltaT = %u, currentTimeUs = %u, micros64_real = %lu\n", deltaT, imuDeltaT, currentTimeUs, micros64_real());
    deltaT = imuDeltaT;
#endif
    // get sensor data
#ifdef USE_GYRO_IMUF9001
    if (gyroConfig()->imuf_mode != GTBCM_GYRO_ACC_QUAT_FILTER_F) {
#endif
    quaternion vError = VECTOR_INITIALIZE;
    quaternion vGyroAverage;
    quaternion vAccAverage;

    gyroGetAverage(&vGyroAverage);
    accGetAverage(&vAccAverage);
    DEBUG_SET(DEBUG_IMU, DEBUG_IMU2, lrintf((quaternionModulus(&vAccAverage)/ acc.dev.acc_1G) * 1000));
    if (accIsHealthy(&vAccAverage)) {
         applyAccError(&vAccAverage, &vError);
    }
    applySensorCorrection(&vError);
    imuMahonyAHRSupdate(deltaT * 1e-6f, &vGyroAverage, &vError);
#ifdef USE_GYRO_IMUF9001
    } else {
        UNUSED(deltaT);
        UNUSED(applyAccError);
        UNUSED(imuMahonyAHRSupdate);

        qAttitude.w = imufQuat.w;
        qAttitude.x = imufQuat.x;
        qAttitude.y = imufQuat.y;
        qAttitude.z = imufQuat.z;

        DEBUG_SET(DEBUG_IMU, DEBUG_IMU0, lrintf(quaternionModulus(&qAttitude) * 1000));
        DEBUG_SET(DEBUG_IMU, DEBUG_IMU1, lrintf(vGyroStdDevModulus * 1000));

        quaternionNormalize(&qAttitude);
        quaternionComputeProducts(&qAttitude, &qpAttitude);
    }
#endif
    imuUpdateEulerAngles();
#endif
}

void imuUpdateAttitude(timeUs_t currentTimeUs) {
    if (sensors(SENSOR_ACC) && acc.isAccelUpdatedAtLeastOnce) {
        IMU_LOCK;
#if defined(SIMULATOR_BUILD) && defined(SIMULATOR_IMU_SYNC)
        if (imuUpdated == false) {
            IMU_UNLOCK;
            return;
        }
        imuUpdated = false;
#endif
        imuCalculateEstimatedAttitude(currentTimeUs);
        IMU_UNLOCK;
    } else {
        acc.accADC[X] = 0;
        acc.accADC[Y] = 0;
        acc.accADC[Z] = 0;
    }
}

float getCosTiltAngle(void) {
    return (1.0f - 2.0f * (qpAttitude.xx + qpAttitude.yy));
}

#ifdef SIMULATOR_BUILD
void imuSetAttitudeRPY(float roll, float pitch, float yaw) {
    IMU_LOCK;

    attitude.values.roll = roll * 10;
    attitude.values.pitch = pitch * 10;
    attitude.values.yaw = yaw * 10;

    IMU_UNLOCK;
}

void imuSetAttitudeQuat(float w, float x, float y, float z) {
    IMU_LOCK;

    qAttitude.w = w;
    qAttitude.x = x;
    qAttitude.y = y;
    qAttitude.z = z;

    imuUpdateEulerAngles();

    IMU_UNLOCK;
}
#endif
#if defined(SIMULATOR_BUILD) && defined(SIMULATOR_IMU_SYNC)
void imuSetHasNewData(uint32_t dt) {
    IMU_LOCK;

    imuUpdated = true;
    imuDeltaT = dt;

    IMU_UNLOCK;
}
#endif

// HEADFREE HEADADJ allowed for tilt below 37°
bool imuQuaternionHeadfreeOffsetSet(void) {
    if ((ABS(getCosTiltAngle()) > 0.8f)) {
        const float yawHalf = atan2_approx((+2.0f * (qpAttitude.wz + qpAttitude.xy)), (+1.0f - 2.0f * (qpAttitude.yy + qpAttitude.zz))) / 2.0f;
        qOffset.w = cos_approx(yawHalf);
        qOffset.x = 0;
        qOffset.y = 0;
        qOffset.z = sin_approx(yawHalf);
        quaternionConjugate(&qOffset, &qOffset);
        return (true);
    } else {
        return (false);
    }
}

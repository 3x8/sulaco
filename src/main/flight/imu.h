// Inertial Measurement Unit (IMU)

#pragma once

#include "common/axis.h"
#include "common/time.h"
#include "common/maths.h"
#include "pg/pg.h"

#ifndef DEFAULT_ATTITUDE_UPDATE_INTERVAL
#define DEFAULT_ATTITUDE_UPDATE_INTERVAL 200
#endif

extern uint32_t accTimeSum;
extern int accSumCount;
extern float accVelScale;
extern int32_t accSum[XYZ_AXIS_COUNT];

// euler angles resolution = 0.1 degree   180 deg = 1800
typedef union {
    int16_t raw[XYZ_AXIS_COUNT];
    struct {
        int16_t roll;
        int16_t pitch;
        int16_t yaw;
    } values;
} attitudeEulerAngles_t;
#define EULER_INITIALIZE  { { 0, 0, 0 } }

extern attitudeEulerAngles_t attitude;
extern quaternion qHeadfree;
extern quaternion qAttitude;

typedef struct accDeadband_s {
    uint8_t xy;
    uint8_t z;
} accDeadband_t;

typedef struct imuConfig_s {
    uint16_t dcm_kp;                        // DCM proportional gain ( x 10000)
    uint16_t dcm_ki;                        // DCM integral gain ( x 10000)
    uint8_t small_angle;
    uint8_t acc_unarmedcal;                 // turn automatic acc compensation on/off
    accDeadband_t accDeadband;
} imuConfig_t;

PG_DECLARE(imuConfig_t, imuConfig);

typedef struct imuRuntimeConfig_s {
    float dcm_ki;
    float dcm_kp;
    uint8_t acc_unarmedcal;
    uint8_t small_angle;
    accDeadband_t accDeadband;
} imuRuntimeConfig_t;

enum {
    DEBUG_IMU0,
    DEBUG_IMU1,
    DEBUG_IMU2,
    DEBUG_IMU3
};

void imuConfigure();

float getCosTiltAngle(void);
void imuUpdateAttitude(timeUs_t currentTimeUs);

void imuResetAccelerationSum(void);
void imuInit(void);

#ifdef SIMULATOR_BUILD
void imuSetAttitudeRPY(float roll, float pitch, float yaw);
void imuSetAttitudeQuat(float w, float x, float y, float z);
#if defined(SIMULATOR_IMU_SYNC)
void imuSetHasNewData(uint32_t dt);
#endif
#endif

bool imuQuaternionHeadfreeOffsetSet(void);

#pragma once

#include "common/axis.h"
#include "common/time.h"
#include "common/maths.h"
#include "pg/pg.h"

#ifndef DEFAULT_ATTITUDE_UPDATE_INTERVAL
#define DEFAULT_ATTITUDE_UPDATE_INTERVAL 200
#endif

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

typedef struct imuConfig_s {
    uint16_t dcm_kp;
    uint16_t dcm_ki;
    uint8_t small_angle;
    uint8_t dcm_fastgain;
} imuConfig_t;

PG_DECLARE(imuConfig_t, imuConfig);

typedef struct imuRuntimeConfig_s {
    float dcm_ki;
    float dcm_kp;
    uint8_t small_angle;
} imuRuntimeConfig_t;

enum {
    DEBUG_IMU0,
    DEBUG_IMU1,
    DEBUG_IMU2,
    DEBUG_IMU3
};

void imuInit(void);
void imuConfigure();

float getCosTiltAngle(void);
void imuUpdateAttitude(timeUs_t currentTimeUs);

#ifdef SIMULATOR_BUILD
void imuSetAttitudeEuler(float roll, float pitch, float yaw);
void imuSetAttitudeQuaternion(float w, float x, float y, float z);
#if defined(SIMULATOR_IMU_SYNC)
void imuSetHasNewData(uint32_t dt);
#endif
#endif

bool imuSetHeadfreeOffsetQuaternion(void);

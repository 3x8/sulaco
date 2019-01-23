#pragma once

#include "common/time.h"
#include "common/maths.h"
#include "pg/pg.h"
#include "drivers/accgyro/accgyro.h"
#include "sensors/sensors.h"

#ifndef DEFAULT_ACC_SAMPLE_INTERVAL
#define DEFAULT_ACC_SAMPLE_INTERVAL 1000
#endif

// Type of accelerometer used/detected
typedef enum {
    ACC_DEFAULT,
    ACC_NONE,
    ACC_ADXL345,
    ACC_MPU6050,
    ACC_MMA8452,
    ACC_BMA280,
    ACC_LSM303DLHC,
    ACC_MPU6000,
    ACC_MPU6500,
    ACC_MPU9250,
    ACC_ICM20601,
    ACC_ICM20602,
    ACC_ICM20608G,
    ACC_ICM20649,
    ACC_ICM20689,
    ACC_BMI160,
    ACC_IMUF9001,
    ACC_FAKE
} accelerationSensor_e;

typedef struct acc_s {
    accDev_t dev;
    float accADC[XYZ_AXIS_COUNT];
    bool accUpdatedOnce;
} acc_t;

extern acc_t acc;

typedef struct rollAndPitchTrims_s {
    int16_t roll;
    int16_t pitch;
} rollAndPitchTrims_t_def;

typedef union rollAndPitchTrims_u {
    int16_t raw[2];
    rollAndPitchTrims_t_def values;
} rollAndPitchTrims_t;


typedef struct accelerometerConfig_s {
    uint16_t acc_lpf_hz;
    sensor_align_e acc_align;
    uint8_t acc_hardware;
    bool acc_high_fsr;
    flightDynamicsTrims_t accZero;
    rollAndPitchTrims_t accelerometerTrims;
} accelerometerConfig_t;

PG_DECLARE(accelerometerConfig_t, accelerometerConfig);

bool accInit(void);
bool accCalibrationComplete(void);
void accSetCalibrationCycles(uint16_t calibrationCyclesRequired);
void resetRollAndPitchTrims(rollAndPitchTrims_t *rollAndPitchTrims);
void accUpdate(timeUs_t currentTimeUs, rollAndPitchTrims_t *rollAndPitchTrims);
bool accGetVector(quaternion *average);
union flightDynamicsTrims_u;
void accSetTrims(union flightDynamicsTrims_u *accelerationTrimsToUse);
void accInitFilters(void);
bool accIsHealthy(quaternion *q);

#pragma once

typedef enum {
    SENSOR_INDEX_GYRO = 0,
    SENSOR_INDEX_ACC,
    SENSOR_INDEX_BARO,
    SENSOR_INDEX_MAG,
    SENSOR_INDEX_RANGEFINDER,
    SENSOR_INDEX_COUNT
} sensorIndex_e;

extern uint8_t requestedSensors[SENSOR_INDEX_COUNT];
extern uint8_t detectedSensors[SENSOR_INDEX_COUNT];

typedef struct int16_flightDynamicsTrims_s {
    int16_t roll;
    int16_t pitch;
    int16_t yaw;
} flightDynamicsTrims_def_t;

typedef union flightDynamicsTrims_u {
    int16_t raw[6];
    flightDynamicsTrims_def_t values;
} flightDynamicsTrims_t;

#define CALIBRATING_ACC_CYCLES              400
#define CALIBRATING_BARO_CYCLES             200 // 10 seconds init_delay + 200 * 25 ms = 15 seconds before ground pressure settles

typedef enum {
    SENSOR_GYRO = 1 << 0, // always present
    SENSOR_ACC = 1 << 1,
    SENSOR_BARO = 1 << 2,
    SENSOR_MAG = 1 << 3,
    SENSOR_SONAR = 1 << 4,
    SENSOR_RANGEFINDER = 1 << 4,
    SENSOR_GPS = 1 << 5,
    SENSOR_GPSMAG = 1 << 6
} sensors_e;

#pragma once

typedef enum {
    X = 0,
    Y,
    Z
} axis_e;

#define XYZ_AXIS_COUNT 3

typedef enum {
    OFFSET_X = 0,
    OFFSET_Y,
    OFFSET_Z,
    FACTOR_X,
    FACTOR_Y,
    FACTOR_Z
} accCalibration_t;

#define ACC_CALIBRATION_SIZE 6


// See http://en.wikipedia.org/wiki/Flight_dynamics
typedef enum {
    FD_ROLL = 0,
    FD_PITCH,
    FD_YAW
} flight_dynamics_index_t;

#define FLIGHT_DYNAMICS_INDEX_COUNT 3

typedef enum {
    AI_ROLL = 0,
    AI_PITCH
} angle_index_t;

#define ANGLE_INDEX_COUNT 2

#define GET_DIRECTION(isReversed) ((isReversed) ? -1 : 1)

#pragma once

#include "drivers/bus.h"

struct baroDev_s;

typedef void (*baroOpFuncPtr)(struct baroDev_s *baro);                       // baro start operation
typedef void (*baroCalculateFuncPtr)(int32_t *pressure, int32_t *temperature); // baro calculation (filled params are pressure and temperature)

typedef struct baroDev_s {
    busDevice_t busdev;
    uint16_t ut_delay;
    uint16_t up_delay;
    baroOpFuncPtr start_ut;
    baroOpFuncPtr get_ut;
    baroOpFuncPtr start_up;
    baroOpFuncPtr get_up;
    baroCalculateFuncPtr calculate;
} baroDev_t;

#ifndef BARO_I2C_INSTANCE
#define BARO_I2C_INSTANCE I2C_DEVICE
#endif

#pragma once

#include "drivers/bus.h"
#include "drivers/sensor.h"
#include "drivers/exti.h"

typedef struct magDev_s {
    sensorMagInitFuncPtr init;                              // initialize function
    sensorMagReadFuncPtr read;                              // read 3 axis data function
    extiCallbackRec_t exti;
    busDevice_t busdev;
    sensor_align_e magAlign;
    ioTag_t magIntExtiTag;
    int16_t magGain[3];
} magDev_t;

#ifndef MAG_I2C_INSTANCE
#define MAG_I2C_INSTANCE I2C_DEVICE
#endif

#pragma once

#include "platform.h"

#include "pg/pg.h"

typedef struct tricopterMixerConfig_s {
    uint8_t dummy;
} tricopterMixerConfig_t;

PG_DECLARE(tricopterMixerConfig_t, tricopterMixerConfig);


bool mixerTricopterIsServoSaturated(float errorRate);
void mixerTricopterInit(void);
float mixerTricopterMotorCorrection(int motor);

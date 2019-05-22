#pragma once

#include "drivers/io_types.h"
#include "drivers/rx/rx_pwm.h"

#include "pg/pg.h"

typedef struct ppmConfig_s {
    ioTag_t ioTag;
} ppmConfig_t;

PG_DECLARE(ppmConfig_t, ppmConfig);

typedef struct pwmConfig_s {
    ioTag_t ioTags[PWM_INPUT_PORT_COUNT];
    inputFilteringMode_e inputFilteringMode;
} pwmConfig_t;

PG_DECLARE(pwmConfig_t, pwmConfig);

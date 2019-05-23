#pragma once

#include "pg/pg.h"

typedef enum {
    GIMBAL_MODE_NORMAL = 0,
    GIMBAL_MODE_MIXTILT = 1
} gimbalMode_e;

#define GIMBAL_MODE_MAX (GIMBAL_MODE_MIXTILT)

typedef struct gimbalConfig_s {
    uint8_t mode;
} gimbalConfig_t;

PG_DECLARE(gimbalConfig_t, gimbalConfig);

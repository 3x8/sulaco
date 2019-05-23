#pragma once

#include "pg/pg.h"
#include "common/time.h"

typedef struct rcdeviceConfig_s {
    uint8_t initDeviceAttempts;
    timeMs_t initDeviceAttemptInterval;
} rcdeviceConfig_t;

PG_DECLARE(rcdeviceConfig_t, rcdeviceConfig);

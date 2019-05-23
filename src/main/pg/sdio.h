#pragma once

#include "pg/pg.h"

typedef struct sdioConfig_s {
    uint8_t clockBypass;
    uint8_t useCache;
} sdioConfig_t;

PG_DECLARE(sdioConfig_t, sdioConfig);

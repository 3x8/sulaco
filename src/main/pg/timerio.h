#pragma once

#include "pg/pg.h"
#include "pg/pg_ids.h"

#include "drivers/io.h"

#ifdef USE_TIMER_MGMT

#define MAX_TIMER_PINMAP_COUNT   10

typedef struct timerIOConfig_s {
    ioTag_t ioTag;
    uint8_t index;
} timerIOConfig_t;

PG_DECLARE_ARRAY(timerIOConfig_t, MAX_TIMER_PINMAP_COUNT, timerIOConfig);

#endif

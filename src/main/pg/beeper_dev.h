#pragma once

#include "drivers/io_types.h"

#include "pg/pg.h"
#include "drivers/io_types.h"

typedef struct beeperDevConfig_s {
    ioTag_t ioTag;
    uint8_t isInverted;
    uint8_t isOpenDrain;
    uint16_t frequency;
} beeperDevConfig_t;

PG_DECLARE(beeperDevConfig_t, beeperDevConfig);

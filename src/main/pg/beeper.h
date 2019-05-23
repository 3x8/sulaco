#pragma once

#include "pg/pg.h"
#include "drivers/io_types.h"

typedef struct beeperConfig_s {
    uint32_t beeper_off_flags;
    uint8_t dshotBeaconTone;
    uint32_t dshotBeaconOffFlags;
} beeperConfig_t;

PG_DECLARE(beeperConfig_t, beeperConfig);

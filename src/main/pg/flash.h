#pragma once

#include <stdint.h>

#include "drivers/io_types.h"

#include "pg/pg.h"

typedef struct flashConfig_s {
    ioTag_t csTag;
    uint8_t spiDevice;
} flashConfig_t;

PG_DECLARE(flashConfig_t, flashConfig);

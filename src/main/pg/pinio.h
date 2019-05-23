#pragma once

#include "pg/pg.h"
#include "drivers/io_types.h"
#include "drivers/pinio.h"

typedef struct pinioConfig_s {
    ioTag_t ioTag[PINIO_COUNT];
    uint8_t config[PINIO_COUNT];
} pinioConfig_t;

PG_DECLARE(pinioConfig_t, pinioConfig);

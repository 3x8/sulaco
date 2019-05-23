#pragma once

#include "drivers/pinio.h"
#include "fc/rc_modes.h"
#include "pg/pg.h"

typedef struct pinioBoxConfig_s {
    uint8_t permanentId[PINIO_COUNT];
} pinioBoxConfig_t;

PG_DECLARE(pinioBoxConfig_t, pinioBoxConfig);

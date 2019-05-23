#pragma once

#include "drivers/bus_i2c.h"
#include "drivers/io_types.h"
#include "drivers/rcc_types.h"

#include "pg/pg.h"

typedef struct i2cConfig_s {
    ioTag_t ioTagScl;
    ioTag_t ioTagSda;
    bool overClock;
    bool pullUp;
} i2cConfig_t;

PG_DECLARE_ARRAY(i2cConfig_t, I2CDEV_COUNT, i2cConfig);

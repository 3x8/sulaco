#pragma once

#include "drivers/bus_spi.h"
#include "drivers/io_types.h"

#include "pg/pg.h"

typedef struct spiPinConfig_s {
    ioTag_t ioTagSck;
    ioTag_t ioTagMiso;
    ioTag_t ioTagMosi;
} spiPinConfig_t;

PG_DECLARE_ARRAY(spiPinConfig_t, SPIDEV_COUNT, spiPinConfig);

// Place holder for CS pins for pre-initialization

typedef struct spiCs_s {
    ioTag_t csnTag;
} spiCs_t;

PG_DECLARE_ARRAY(spiCs_t, SPI_PREINIT_IPU_COUNT, spiPreinitIPUConfig);
PG_DECLARE_ARRAY(spiCs_t, SPI_PREINIT_OPU_COUNT, spiPreinitOPUConfig);

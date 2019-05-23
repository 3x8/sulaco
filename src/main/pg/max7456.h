#pragma once

#include "drivers/io_types.h"
#include "pg/pg.h"

typedef struct max7456Config_s {
    uint8_t clockConfig; // SPI clock based on device type and overclock state (MAX7456_CLOCK_CONFIG_xxxx)
    ioTag_t csTag;
    uint8_t spiDevice;
} max7456Config_t;

// clockConfig values
#define MAX7456_CLOCK_CONFIG_HALF 0  // Force half clock
#define MAX7456_CLOCK_CONFIG_OC   1  // Half clock if OC
#define MAX7456_CLOCK_CONFIG_FULL 2  // Force full clock

PG_DECLARE(max7456Config_t, max7456Config);

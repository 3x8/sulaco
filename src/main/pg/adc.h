#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "pg/pg.h"
#include "drivers/io_types.h"

typedef struct adcChannelConfig_t {
    bool enabled;
    ioTag_t ioTag;
} adcChannelConfig_t;

typedef struct adcConfig_s {
    adcChannelConfig_t vbat;
    adcChannelConfig_t rssi;
    adcChannelConfig_t current;
    adcChannelConfig_t external1;
    int8_t device; // ADCDevice
} adcConfig_t;

PG_DECLARE(adcConfig_t, adcConfig);

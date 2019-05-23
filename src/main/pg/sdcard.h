#pragma once

#include "pg/pg.h"
#include "drivers/io.h"

typedef struct sdcardConfig_s {
    uint8_t useDma;
    uint8_t enabled;
    uint8_t device;
    ioTag_t cardDetectTag;
    ioTag_t chipSelectTag;
    uint8_t cardDetectInverted;
    uint8_t dmaIdentifier;
    uint8_t dmaChannel;
} sdcardConfig_t;

PG_DECLARE(sdcardConfig_t, sdcardConfig);

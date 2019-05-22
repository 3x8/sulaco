#pragma once

#include "drivers/io_types.h"

#include "pg/pg.h"

enum USB_DEV {
    DEFAULT,
    COMPOSITE
};

typedef struct usbDev_s {
    uint8_t type;
    ioTag_t mscButtonPin;
    uint8_t mscButtonUsePullup;
} usbDev_t;

PG_DECLARE(usbDev_t, usbDevConfig);

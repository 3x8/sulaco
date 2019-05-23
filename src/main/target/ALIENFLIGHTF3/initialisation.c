#include <stdbool.h>
#include <stdint.h>

#include "platform.h"
#include "drivers/bus.h"
#include "drivers/bus_i2c.h"
#include "drivers/bus_spi.h"
#include "io/serial.h"
#include "hardware_revision.h"
#include "pg/bus_i2c.h"
#include "pg/bus_spi.h"

extern void spiPreInit(void);

void targetBusInit(void)
{
    if (hardwareRevision == AFF3_REV_2) {
        spiPinConfigure(spiPinConfig(0));
        spiPreInit();
        spiInit(SPIDEV_3);
    }
    i2cHardwareConfigure(i2cConfig(0));
    i2cInit(I2CDEV_2);
}

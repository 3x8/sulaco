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


extern void spiPreInit(void); // XXX In fc/fc_init.c

void targetBusInit(void)
{
#ifdef USE_SPI
    spiPinConfigure(spiPinConfig(0));
    spiPreInit();
#ifdef USE_SPI_DEVICE_2
    spiInit(SPIDEV_2);
#endif
#endif

    if (hardwareRevision == NAZE32_SP) {
        serialRemovePort(SERIAL_PORT_SOFTSERIAL2);

        if (!doesConfigurationUsePort(SERIAL_PORT_USART3)) {
            serialRemovePort(SERIAL_PORT_USART3);
            i2cHardwareConfigure(i2cConfig(0));
            i2cInit(I2C_DEVICE);
        }
    } else {
        i2cHardwareConfigure(i2cConfig(0));
        i2cInit(I2C_DEVICE);
    }
}

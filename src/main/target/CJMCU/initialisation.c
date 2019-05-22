#include <stdbool.h>
#include <stdint.h>

#include "platform.h"
#include "drivers/bus.h"
#include "drivers/bus_i2c.h"
#include "drivers/bus_spi.h"
#include "io/serial.h"
#include "pg/bus_i2c.h"
#include "pg/bus_spi.h"


extern void spiPreInit(void); // XXX In fc/fc_init.c

void targetBusInit(void)
{
#if defined(USE_SPI) && defined(USE_SPI_DEVICE_1)
    spiPinConfigure(spiPinConfig(0));
    spiPreInit();
    spiInit(SPIDEV_1);
#endif

    if (!doesConfigurationUsePort(SERIAL_PORT_USART3)) {
        serialRemovePort(SERIAL_PORT_USART3);
        i2cHardwareConfigure(i2cConfig(0));
        i2cInit(I2C_DEVICE);
    }
}

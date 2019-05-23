#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "platform.h"

#if defined(USE_I2C)

#include "drivers/bus.h"
#include "drivers/bus_i2c.h"

bool i2cBusWriteRegister(const busDevice_t *busdev, uint8_t reg, uint8_t data)
{
    return i2cWrite(busdev->busdev_u.i2c.device, busdev->busdev_u.i2c.address, reg, data);
}

bool i2cBusReadRegisterBuffer(const busDevice_t *busdev, uint8_t reg, uint8_t *data, uint8_t length)
{
    return i2cRead(busdev->busdev_u.i2c.device, busdev->busdev_u.i2c.address, reg, length, data);
}

uint8_t i2cBusReadRegister(const busDevice_t *busdev, uint8_t reg)
{
    uint8_t data;
    i2cRead(busdev->busdev_u.i2c.device, busdev->busdev_u.i2c.address, reg, 1, &data);
    return data;
}
#endif

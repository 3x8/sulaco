#pragma once

#include "platform.h"

#include "drivers/bus_i2c.h"
#include "drivers/io_types.h"

typedef enum {
    BUSTYPE_NONE = 0,
    BUSTYPE_I2C,
    BUSTYPE_SPI,
    BUSTYPE_MPU_SLAVE // Slave I2C on SPI master
} busType_e;

typedef struct busDevice_s {
    busType_e bustype;
    union {
        struct deviceSpi_s {
            SPI_TypeDef *instance;
#if defined(USE_HAL_DRIVER)
            SPI_HandleTypeDef* handle; // cached here for efficiency
#endif
            IO_t csnPin;

#if defined(USE_GYRO_IMUF9001)
            IO_t rstPin;
#endif
        } spi;
        struct deviceI2C_s {
            I2CDevice device;
            uint8_t address;
        } i2c;
        struct deviceMpuSlave_s {
            const struct busDevice_s *master;
            uint8_t address;
        } mpuSlave;
    } busdev_u;
} busDevice_t;

#ifdef TARGET_BUS_INIT
void targetBusInit(void);
#endif

bool busWriteRegister(const busDevice_t *bus, uint8_t reg, uint8_t data);
bool busReadRegisterBuffer(const busDevice_t *bus, uint8_t reg, uint8_t *data, uint8_t length);
uint8_t busReadRegister(const busDevice_t *bus, uint8_t reg);

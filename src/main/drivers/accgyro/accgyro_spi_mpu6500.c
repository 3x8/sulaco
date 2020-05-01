#include <stdbool.h>
#include <stdint.h>

#include "platform.h"

#include "common/axis.h"
#include "common/maths.h"

#include "drivers/bus_spi.h"
#include "drivers/exti.h"
#include "drivers/io.h"
#include "drivers/sensor.h"
#include "drivers/time.h"

#include "accgyro.h"
#include "accgyro_mpu.h"
#include "accgyro_mpu6500.h"
#include "accgyro_spi_mpu6500.h"

#define BIT_SLEEP                   0x40

static void mpu6500SpiInit(const busDevice_t *bus) {

#ifndef USE_DUAL_GYRO
    IOInit(bus->busdev_u.spi.csnPin, OWNER_MPU_CS, 0);
    IOConfigGPIO(bus->busdev_u.spi.csnPin, SPI_IO_CS_CFG);
    IOHi(bus->busdev_u.spi.csnPin);
#endif

    spiSetDivisor(bus->busdev_u.spi.instance, SPI_CLOCK_FAST);
}

uint8_t mpu6500SpiDetect(const busDevice_t *bus) {
    mpu6500SpiInit(bus);

    const uint8_t whoAmI = spiBusReadRegister(bus, MPU_RA_WHO_AM_I);

    uint8_t mpuDetected = MPU_NONE;
    switch (whoAmI) {
    case MPU6500_WHO_AM_I_CONST:
        mpuDetected = MPU_65xx_SPI;
        break;
    case MPU9250_WHO_AM_I_CONST:
    case MPU9255_WHO_AM_I_CONST:
        mpuDetected = MPU_9250_SPI;
        break;
    case ICM20601_WHO_AM_I_CONST:
        mpuDetected = ICM_20601_SPI;
        break;
    case ICM20602_WHO_AM_I_CONST:
        mpuDetected = ICM_20602_SPI;
        break;
    case ICM20608G_WHO_AM_I_CONST:
        mpuDetected = ICM_20608_SPI;
        break;
    default:
        mpuDetected = MPU_NONE;
    }
    return (mpuDetected);
}

void mpu6500SpiAccInit(accDev_t *acc) {
    mpu6500AccInit(acc);
}

void mpu6500SpiGyroInit(gyroDev_t *gyro) {
    spiSetDivisor(gyro->bus.busdev_u.spi.instance, SPI_CLOCK_SLOW);
    delayMicroseconds(1);

    mpu6500GyroInit(gyro);

    // Disable Primary I2C Interface
    spiBusWriteRegister(&gyro->bus, MPU_RA_USER_CTRL, MPU6500_BIT_I2C_IF_DIS);
    delay(100);

    spiSetDivisor(gyro->bus.busdev_u.spi.instance, SPI_CLOCK_FAST);
    delayMicroseconds(1);
}

bool mpu6500SpiAccDetect(accDev_t *acc) {
    // MPU6500 is used as a equivalent of other accelerometers by some flight controllers
    switch (acc->mpuDetectionResult.sensor) {
    case MPU_65xx_SPI:
    case MPU_9250_SPI:
    case ICM_20608_SPI:
    case ICM_20602_SPI:
    case ICM_20601_SPI:
        break;
    default:
        return (false);
    }

    acc->initFn = mpu6500SpiAccInit;
    acc->readFn = mpuAccRead;

    return (true);
}

bool mpu6500SpiGyroDetect(gyroDev_t *gyro) {
    // MPU6500 is used as a equivalent of other gyros by some flight controllers
    switch (gyro->mpuDetectionResult.sensor) {
    case MPU_65xx_SPI:
    case MPU_9250_SPI:
    case ICM_20608_SPI:
    case ICM_20602_SPI:
        gyro->scale = GYRO_SCALE_2000DPS;
        break;
    case ICM_20601_SPI:
        gyro->scale = (gyro->gyro_high_fsr ? GYRO_SCALE_4000DPS : GYRO_SCALE_2000DPS);
        break;
    default:
        return (false);
    }

    gyro->initFn = mpu6500SpiGyroInit;
    gyro->readFn = mpuGyroReadSPI;

    return (true);
}

#include <stdbool.h>
#include <stdint.h>

#include "platform.h"

#include "drivers/bus_i2c.h"

#include "drivers/sensor.h"
#include "drivers/accgyro/accgyro.h"
#include "accgyro_bma280.h"

// BMA280, default I2C address mode 0x18
#define BMA280_ADDRESS     0x18
#define BMA280_ACC_X_LSB   0x02
#define BMA280_PMU_BW      0x10
#define BMA280_PMU_RANGE   0x0F

static void bma280Init(accDev_t *acc)
{
    i2cWrite(MPU_I2C_INSTANCE, BMA280_ADDRESS, BMA280_PMU_RANGE, 0x08); // +-8g range
    i2cWrite(MPU_I2C_INSTANCE, BMA280_ADDRESS, BMA280_PMU_BW, 0x0E); // 500Hz BW

    acc->acc_1G = 512 * 8;
}

static bool bma280Read(accDev_t *acc)
{
    uint8_t buf[6];

    if (!i2cRead(MPU_I2C_INSTANCE, BMA280_ADDRESS, BMA280_ACC_X_LSB, 6, buf)) {
        return false;
    }

    // Data format is lsb<5:0><crap><new_data_bit> | msb<13:6>
    acc->ADCRaw[0] = (int16_t)((buf[0] >> 2) + (buf[1] << 8));
    acc->ADCRaw[1] = (int16_t)((buf[2] >> 2) + (buf[3] << 8));
    acc->ADCRaw[2] = (int16_t)((buf[4] >> 2) + (buf[5] << 8));

    return true;
}

bool bma280Detect(accDev_t *acc)
{
    uint8_t sig = 0;
    bool ack = i2cRead(MPU_I2C_INSTANCE, BMA280_ADDRESS, 0x00, 1, &sig);

    if (!ack || sig != 0xFB)
        return false;

    acc->initFn = bma280Init;
    acc->readFn = bma280Read;
    return true;
}

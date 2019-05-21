#pragma once

#include "drivers/bus.h"

uint8_t mpu6500SpiDetect(const busDevice_t *bus);

bool mpu6500SpiAccDetect(accDev_t *acc);
bool mpu6500SpiGyroDetect(gyroDev_t *gyro);

void mpu6500SpiGyroInit(gyroDev_t *gyro);
void mpu6500SpiAccInit(accDev_t *acc);

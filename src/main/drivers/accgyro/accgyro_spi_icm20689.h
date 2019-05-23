#pragma once

#include "drivers/bus.h"

#define ICM20689_BIT_RESET                  (0x80)

bool icm20689AccDetect(accDev_t *acc);
bool icm20689GyroDetect(gyroDev_t *gyro);

void icm20689AccInit(accDev_t *acc);
void icm20689GyroInit(gyroDev_t *gyro);

uint8_t icm20689SpiDetect(const busDevice_t *bus);

bool icm20689SpiAccDetect(accDev_t *acc);
bool icm20689SpiGyroDetect(gyroDev_t *gyro);

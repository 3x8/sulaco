#pragma once

#include "drivers/accgyro/accgyro.h"

bool gyroSyncCheckUpdate(gyroDev_t *gyro);
uint32_t gyroSetSampleRate(gyroDev_t *gyro, uint8_t lpf, uint8_t gyroSyncDenominator, bool gyro_use_32khz);

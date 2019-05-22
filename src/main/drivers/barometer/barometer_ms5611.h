#pragma once

// MS5611, Standard address 0x77
#define MS5611_I2C_ADDR                 0x77

bool ms5611Detect(baroDev_t *baro);

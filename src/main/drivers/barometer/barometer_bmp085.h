#pragma once

#include "drivers/io_types.h"

#define BMP085_I2C_ADDR         0x77

typedef struct bmp085Config_s {
    ioTag_t xclrIO;
    ioTag_t eocIO;
} bmp085Config_t;

bool bmp085Detect(const bmp085Config_t *config, baroDev_t *baro);
void bmp085Disable(const bmp085Config_t *config);

#if defined(BARO_EOC_GPIO)
bool bmp085TestEOCConnected(const bmp085Config_t *config);
#endif

#ifdef UNIT_TEST
void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState);
#endif

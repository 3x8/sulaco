#pragma once

typedef struct drv_adxl345_config_s {
    uint16_t dataRate;
    bool useFifo;
} drv_adxl345_config_t;

bool adxl345Detect(drv_adxl345_config_t *init, accDev_t *acc);

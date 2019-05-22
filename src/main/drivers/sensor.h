#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    ALIGN_DEFAULT = 0,                                      // driver-provided alignment
    CW0_DEG = 1,
    CW90_DEG = 2,
    CW180_DEG = 3,
    CW270_DEG = 4,
    CW0_DEG_FLIP = 5,
    CW90_DEG_FLIP = 6,
    CW180_DEG_FLIP = 7,
    CW270_DEG_FLIP = 8,
#ifdef USE_GYRO_IMUF9001
    CW45_DEG = 9,
    CW135_DEG = 10,
    CW225_DEG = 11,
    CW315_DEG = 12,
    CW45_DEG_FLIP = 13,
    CW135_DEG_FLIP = 14,
    CW225_DEG_FLIP = 15,
    CW315_DEG_FLIP = 16,
#endif
} sensor_align_e;

typedef bool (*sensorInterruptFuncPtr)(void);
struct magDev_s;
typedef bool (*sensorMagInitFuncPtr)(struct magDev_s *magdev);
typedef bool (*sensorMagReadFuncPtr)(struct magDev_s *magdev, int16_t *data);
struct accDev_s;
typedef void (*sensorAccInitFuncPtr)(struct accDev_s *acc);
typedef bool (*sensorAccReadFuncPtr)(struct accDev_s *acc);
struct gyroDev_s;
typedef void (*sensorGyroInitFuncPtr)(struct gyroDev_s *gyro);
typedef bool (*sensorGyroReadFuncPtr)(struct gyroDev_s *gyro);
typedef bool (*sensorGyroReadDataFuncPtr)(struct gyroDev_s *gyro, int16_t *data);

#pragma once

#include "pg/pg.h"
#include "drivers/barometer/barometer.h"

typedef enum {
  BARO_DEFAULT,
  BARO_NONE,
  BARO_BMP085,
  BARO_MS5611,
  BARO_BMP280,
  BARO_LPS,
  BARO_QMP6988
} baroSensor_e;

#define BARO_SAMPLE_COUNT_MAX   48

typedef struct barometerConfig_s {
  uint8_t baro_bustype;
  uint8_t baro_spi_device;
  ioTag_t baro_spi_csn;                   // Also used as XCLR (positive logic) for BMP085
  uint8_t baro_i2c_device;
  uint8_t baro_i2c_address;
  uint8_t baro_hardware;                  // Barometer hardware to use
  uint8_t baro_sample_count;              // size of baro filter array
  uint16_t baro_noise_lpf;                // additional LPF to reduce baro noise
  uint16_t baro_cf_vel;                   // apply Complimentary Filter to keep the calculated velocity based on baro velocity (i.e. near real velocity)
  uint16_t baro_cf_alt;                   // apply CF to use ACC for height estimation
} barometerConfig_t;

PG_DECLARE(barometerConfig_t, barometerConfig);

typedef struct baro_s {
  baroDev_t dev;
  int32_t BaroAlt;
  int32_t baroTemperature;             // Use temperature for telemetry
  int32_t baroPressure;                // Use pressure for telemetry
} baro_t;

extern baro_t baro;

bool baroDetect(baroDev_t *dev, baroSensor_e baroHardwareToUse);
bool isBaroCalibrationComplete(void);
void baroSetCalibrationCycles(uint16_t calibrationCyclesRequired);
uint32_t baroUpdate(void);
bool isBaroReady(void);
int32_t baroCalculateAltitude(void);
void performBaroCalibrationCycle(void);

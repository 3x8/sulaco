#pragma once

#include "common/axis.h"
#include "common/time.h"
#include "common/maths.h"
#include "pg/pg.h"
#include "drivers/bus.h"
#include "drivers/sensor.h"

#define GYRO_SCALE_2000DPS (2000.0f / (1 << 15))   // 16.384 dps/lsb scalefactor for 2000dps sensors
#define GYRO_SCALE_4000DPS (4000.0f / (1 << 15))   //  8.192 dps/lsb scalefactor for 4000dps sensors

extern float vGyroStdDevModulus;

typedef enum {
  GYRO_NONE,
  GYRO_DEFAULT,
  GYRO_MPU6050,
  GYRO_L3G4200D,
  GYRO_MPU3050,
  GYRO_L3GD20,
  GYRO_MPU6000,
  GYRO_MPU6500,
  GYRO_MPU9250,
  GYRO_ICM20601,
  GYRO_ICM20602,
  GYRO_ICM20608G,
  GYRO_ICM20649,
  GYRO_ICM20689,
  GYRO_BMI160,
  GYRO_IMUF9001,
  GYRO_FAKE
} gyroSensor_e;

typedef struct gyro_s {
  uint32_t targetLooptime;
  float gyroADCf[XYZ_AXIS_COUNT];
} gyro_t;

extern gyro_t gyro;

typedef enum {
  GYRO_OVERFLOW_CHECK_NONE = 0,
  GYRO_OVERFLOW_CHECK_YAW,
  GYRO_OVERFLOW_CHECK_ALL_AXES
} gyroOverflowCheck_e;

#define GYRO_CONFIG_USE_GYRO_1      0
#define GYRO_CONFIG_USE_GYRO_2      1
#define GYRO_CONFIG_USE_GYRO_BOTH   2

typedef enum {
  FILTER_LOWPASS = 0,
  FILTER_LOWPASS2
} filterSlots;

#if defined(USE_GYRO_IMUF9001)
  typedef enum {
    IMUF_RATE_32K = 0,
    IMUF_RATE_16K = 1,
    IMUF_RATE_8K = 2,
    IMUF_RATE_4K = 3,
    IMUF_RATE_2K = 4,
    IMUF_RATE_1K = 5
  } imufRate_e;
#endif

typedef struct gyroConfig_s {
  uint8_t  gyro_align;                       // gyro alignment
  uint8_t  gyroMovementCalibrationThreshold; // people keep forgetting that moving model while init results in wrong gyro offsets. and then they never reset gyro. so this is now on by default.
  uint8_t  gyro_sync_denom;                  // Gyro sample divider
  uint8_t  gyro_hardware_lpf;                // gyro DLPF setting
  uint8_t  gyro_32khz_hardware_lpf;          // gyro 32khz DLPF setting

  uint8_t  gyro_high_fsr;
  uint8_t  gyro_use_32khz;
  uint8_t  gyro_to_use;

  uint16_t gyro_lowpass_hz;
  uint16_t gyro_lowpass2_hz;

  uint16_t gyro_soft_notch_hz_1;
  uint16_t gyro_soft_notch_cutoff_1;
  uint16_t gyro_soft_notch_hz_2;
  uint16_t gyro_soft_notch_cutoff_2;
  uint8_t  checkOverflow;
  uint16_t gyro_kalman_q;
  uint16_t gyro_kalman_w;

  // Lowpass primary/secondary
  uint8_t  gyro_lowpass_type;
  uint8_t  gyro_lowpass2_type;

  uint8_t  yaw_spin_recovery;
  int16_t  yaw_spin_threshold;

  uint16_t gyroCalibrationDuration;  // Gyro calibration duration in 1/100 second
  uint8_t dyn_notch_quality; // bandpass quality factor, 100 for steep sided bandpass
  uint8_t dyn_notch_width_percent;
  #if defined(USE_GYRO_IMUF9001)
    uint16_t imuf_mode;
    uint16_t imuf_rate;
    uint16_t imuf_pitch_q;
    uint16_t imuf_roll_q;
    uint16_t imuf_yaw_q;
    uint16_t imuf_w;
    uint16_t imuf_pitch_lpf_cutoff_hz;
    uint16_t imuf_roll_lpf_cutoff_hz;
    uint16_t imuf_yaw_lpf_cutoff_hz;
  #endif
} gyroConfig_t;

PG_DECLARE(gyroConfig_t, gyroConfig);

bool gyroInit(void);

void gyroInitFilters(void);
#ifdef USE_DMA_SPI_DEVICE
  void gyroDmaSpiFinishRead(void);
  void gyroDmaSpiStartRead(void);
#endif
void gyroUpdate(timeUs_t currentTimeUs);
bool gyroGetVector(quaternion *vAverage);
const busDevice_t *gyroSensorBus(void);
struct mpuConfiguration_s;
const struct mpuConfiguration_s *gyroMpuConfiguration(void);
struct mpuDetectionResult_s;
const struct mpuDetectionResult_s *gyroMpuDetectionResult(void);
void gyroStartCalibration(bool isFirstArmingCalibration);
bool isFirstArmingGyroCalibrationRunning(void);
bool gyroCalibrationComplete(void);
void gyroReadTemperature(void);
int16_t gyroGetTemperature(void);
int16_t gyroRateDps(int axis);
bool gyroOverflowDetected(void);
bool gyroYawSpinDetected(void);
uint16_t gyroAbsRateDps(int axis);
uint8_t gyroReadRegister(uint8_t whichSensor, uint8_t reg);

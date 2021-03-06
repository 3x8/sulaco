#pragma once

#define DEBUG16_VALUE_COUNT 4
extern int16_t debug[DEBUG16_VALUE_COUNT];
extern uint8_t debugMode;

#define DEBUG_SET(mode, index, value) {if (debugMode == (mode)) {debug[(index)] = (value);}}
#define DEBUG_SECTION_TIMES

#ifdef DEBUG_SECTION_TIMES
  extern uint32_t sectionTimes[2][4];

  #define TIME_SECTION_BEGIN(index) { \
    extern uint32_t sectionTimes[2][4]; \
    sectionTimes[0][index] = micros(); \
  }

  #define TIME_SECTION_END(index) { \
    extern uint32_t sectionTimes[2][4]; \
    sectionTimes[1][index] = micros(); \
    debug[index] = sectionTimes[1][index] - sectionTimes[0][index]; \
  }
#else
  #define TIME_SECTION_BEGIN(index) {}
  #define TIME_SECTION_END(index) {}
#endif

typedef enum {
  DEBUG_NONE,
  DEBUG_CYCLETIME,
  DEBUG_BATTERY,
  DEBUG_GYRO_FILTER,
  DEBUG_GYRO_FILTER_DIFF,
  DEBUG_ACC,
  DEBUG_ACC_FILTER,
  DEBUG_PIDLOOP,
  DEBUG_GYRO_SCALED,
  DEBUG_RC_INTERPOLATION,
  DEBUG_ANGLERATE,
  DEBUG_ESC_SENSOR,
  DEBUG_SCHEDULER,
  DEBUG_STACK,
  DEBUG_ESC_SENSOR_RPM,
  DEBUG_ESC_SENSOR_TMP,
  DEBUG_ALTITUDE,
  DEBUG_DYNAMIC_NOTCH,
  DEBUG_DYNAMIC_NOTCH_TIME,
  DEBUG_DYNAMIC_NOTCH_FREQ,
  DEBUG_RX_FRSKY_SPI,
  DEBUG_GYRO_RAW,
  DEBUG_DUAL_GYRO,
  DEBUG_DUAL_GYRO_RAW,
  DEBUG_DUAL_GYRO_COMBINE,
  DEBUG_DUAL_GYRO_DIFF,
  DEBUG_MAX7456_SIGNAL,
  DEBUG_MAX7456_SPICLOCK,
  DEBUG_SBUS,
  DEBUG_FPORT,
  DEBUG_RANGEFINDER,
  DEBUG_RANGEFINDER_QUALITY,
  DEBUG_LIDAR_TF,
  DEBUG_CORE_TEMP,
  DEBUG_RUNAWAY_TAKEOFF,
  DEBUG_SDIO,
  DEBUG_CURRENT,
  DEBUG_USB,
  DEBUG_SMARTAUDIO,
  DEBUG_RTH,
  DEBUG_ITERM_RELAX,
  DEBUG_ACRO_TRAINER,
  DEBUG_RC_SMOOTHING,
  DEBUG_RX_SIGNAL_LOSS,
  DEBUG_RC_SMOOTHING_RATE,
  DEBUG_ANTI_GRAVITY,
  DEBUG_IMU,
  DEBUG_PID_FILTER,
  DEBUG_PID_FILTER_DIFF,
  DEBUG_KALMAN,
  DEBUG_COUNT
} debugType_e;

extern const char * const debugModeNames[DEBUG_COUNT];

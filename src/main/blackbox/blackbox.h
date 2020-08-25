#pragma once

#include "platform.h"
#include "build/build_config.h"
#include "common/time.h"
#include "pg/pg.h"

typedef enum BlackboxDevice {
  BLACKBOX_DEVICE_NONE = 0,
  #ifdef USE_FLASHFS
    BLACKBOX_DEVICE_FLASH = 1,
  #endif
  #ifdef USE_SDCARD
    BLACKBOX_DEVICE_SDCARD = 2,
  #endif
    BLACKBOX_DEVICE_SERIAL = 3
} BlackboxDevice_e;

typedef enum BlackboxMode {
  BLACKBOX_MODE_NORMAL = 0,
  BLACKBOX_MODE_MOTOR_TEST,
  BLACKBOX_MODE_ALWAYS_ON
} BlackboxMode;

typedef enum FlightLogEvent {
  FLIGHT_LOG_EVENT_SYNC_BEEP = 0,
  FLIGHT_LOG_EVENT_INFLIGHT_ADJUSTMENT = 13,
  FLIGHT_LOG_EVENT_LOGGING_RESUME = 14,
  FLIGHT_LOG_EVENT_FLIGHTMODE = 30, // Add new event type for flight mode status.
  FLIGHT_LOG_EVENT_LOG_END = 255
} FlightLogEvent;

typedef struct blackboxConfig_s {
  uint16_t p_ratio; // I-frame interval / P-frame interval
  uint8_t device;
  uint8_t record_acc;
  uint8_t mode;
} blackboxConfig_t;

PG_DECLARE(blackboxConfig_t, blackboxConfig);

union flightLogEventData_u;
void blackboxLogEvent(FlightLogEvent event, union flightLogEventData_u *data);

void blackboxInit(void);
void blackboxUpdate(timeUs_t currentTimeUs);
void blackboxSetStartDateTime(const char *dateTime, timeMs_t timeNowMs);
int blackboxCalculatePDenom(int rateNum, int rateDenom);
uint8_t blackboxGetRateDenom(void);
void blackboxValidateConfig(void);
void blackboxFinish(void);
bool blackboxMayEditConfig(void);

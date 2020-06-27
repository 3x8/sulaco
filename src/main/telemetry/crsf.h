#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "common/time.h"
#include "interface/crsf_protocol.h"

#define CRSF_MSP_RX_BUF_SIZE 128
#define CRSF_MSP_TX_BUF_SIZE 128

void initCrsfTelemetry(void);
bool checkCrsfTelemetryState(void);
void handleCrsfTelemetry(timeUs_t currentTimeUs);
void crsfScheduleDeviceInfoResponse(void);
void crsfScheduleMspResponse(void);
int getCrsfFrame(uint8_t *frame, crsfFrameType_e frameType);
#if defined(USE_CRSF_CMS_TELEMETRY)
  void crsfProcessDisplayPortCmd(uint8_t *frameStart);
#endif
#if defined(USE_MSP_OVER_TELEMETRY)
  void initCrsfMspBuffer(void);
  bool bufferCrsfMspFrame(uint8_t *frameStart, int frameLength);
#endif

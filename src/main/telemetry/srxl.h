#pragma once

#include "common/time.h"

void srxlCollectTelemetryNow(void);
void initSrxlTelemetry(void);
bool checkSrxlTelemetryState(void);
void handleSrxlTelemetry(timeUs_t currentTimeUs);

#define SPEKTRUM_SRXL_TEXTGEN_BUFFER_ROWS 9
#define SPEKTRUM_SRXL_TEXTGEN_BUFFER_COLS 12 // Airware 1.20
//#define SPEKTRUM_SRXL_TEXTGEN_BUFFER_COLS 13 // Airware 1.21
#define SPEKTRUM_SRXL_TEXTGEN_CLEAR_SCREEN 255

int spektrumTmTextGenPutChar(uint8_t col, uint8_t row, char c);

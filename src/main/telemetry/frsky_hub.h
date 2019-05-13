#pragma once

#include "common/time.h"

typedef enum {
    FRSKY_VFAS_PRECISION_LOW = 0,
    FRSKY_VFAS_PRECISION_HIGH
} frskyVFasPrecision_e;

typedef void frSkyHubWriteByteFn(const char data);

void handleFrSkyHubTelemetry(timeUs_t currentTimeUs);
void checkFrSkyHubTelemetryState(void);

bool initFrSkyHubTelemetry(void);
bool initFrSkyHubTelemetryExternal(frSkyHubWriteByteFn *frSkyWriteFrameExternal);

void processFrSkyHubTelemetry(timeUs_t currentTimeUs);

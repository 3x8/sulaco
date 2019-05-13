#pragma once

#include <stdint.h>

#include "drivers/rangefinder/rangefinder.h"

#include "pg/pg.h"

typedef enum {
    RANGEFINDER_NONE        = 0,
    RANGEFINDER_HCSR04      = 1,
    RANGEFINDER_TFMINI      = 2,
    RANGEFINDER_TF02        = 3,
    // Following sensors are to be ported from iNav
    RANGEFINDER_SRF10       = 4,
    RANGEFINDER_HCSR04I2C   = 5,
    RANGEFINDER_VL53L0X     = 6,
    RANGEFINDER_UIB         = 7,
} rangefinderType_e;

typedef struct rangefinderConfig_s {
    uint8_t rangefinder_hardware;
} rangefinderConfig_t;

PG_DECLARE(rangefinderConfig_t, rangefinderConfig);

typedef struct rangefinder_s {
    rangefinderDev_t dev;
    float maxTiltCos;
    int32_t rawAltitude;
    int32_t calculatedAltitude;
    timeMs_t lastValidResponseTimeMs;

    bool snrThresholdReached;
    int32_t dynamicDistanceThreshold;
    int16_t snr;
} rangefinder_t;

extern rangefinder_t rangefinder;

void rangefinderResetDynamicThreshold(void);
bool rangefinderInit(void);

int32_t rangefinderGetLatestAltitude(void);
int32_t rangefinderGetLatestRawAltitude(void);

void rangefinderUpdate(timeUs_t currentTimeUs);
bool rangefinderProcess(float cosTiltAngle);
bool rangefinderIsHealthy(void);

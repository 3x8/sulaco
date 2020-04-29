#pragma once

#include <stdint.h>

#include "pg/pg.h"

#define CONTROL_RATE_PROFILE_COUNT  6

#if defined(USE_TPA_CURVES)
  #define ATTENUATION_CURVE_SIZE 9
#endif //USE_TPA_CURVES

typedef enum {
  RATES_TYPE_BETAFLIGHT = 0,
  RATES_TYPE_RACEFLIGHT,
} ratesType_e;

typedef enum {
  THROTTLE_LIMIT_TYPE_OFF = 0,
  THROTTLE_LIMIT_TYPE_SCALE,
  THROTTLE_LIMIT_TYPE_CLIP,
} throttleLimitType_e;

typedef struct controlRateConfig_s {
  uint8_t thrMid8;
  uint8_t thrExpo8;
  uint8_t rates_type;
  uint8_t rcRates[3];
  uint8_t rcExpo[3];
  uint8_t rates[3];
  uint8_t dynThrPID;
  uint16_t tpa_breakpoint;                // Breakpoint where TPA is activated
  uint8_t throttle_limit_type;            // Sets the throttle limiting type - off, scale or clip
  uint8_t throttle_limit_percent;         // Sets the maximum pilot commanded throttle limit
  #if defined(USE_TPA_CURVES)
    uint8_t    tpaKpCurve[ATTENUATION_CURVE_SIZE];
    uint8_t    tpaKiCurve[ATTENUATION_CURVE_SIZE];
    uint8_t    tpaKdCurve[ATTENUATION_CURVE_SIZE];
    uint8_t    tpaCurveType;
  #endif //USE_TPA_CURVES
} controlRateConfig_t;

PG_DECLARE_ARRAY(controlRateConfig_t, CONTROL_RATE_PROFILE_COUNT, controlRateProfiles);

extern controlRateConfig_t *currentControlRateProfile;

void loadControlRateProfile(void);
void changeControlRateProfile(uint8_t controlRateProfileIndex);

void copyControlRateProfile(const uint8_t dstControlRateProfileIndex, const uint8_t srcControlRateProfileIndex);

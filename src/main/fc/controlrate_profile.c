#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "platform.h"

#include "common/axis.h"

#include "config/config_reset.h"
#include "pg/pg.h"
#include "pg/pg_ids.h"

#include "fc/config.h"
#include "fc/controlrate_profile.h"
#include "fc/fc_rc.h"

#if defined(USE_TPA_CURVES)
  // rf1 defaults
  static uint8_t kpAttenuationCurveDefault[ATTENUATION_CURVE_SIZE] = {100, 100, 95, 95, 95, 95, 95, 100, 100};
  static uint8_t kiAttenuationCurveDefault[ATTENUATION_CURVE_SIZE] = {100, 100, 100, 100, 100, 100, 100, 100, 100};
  static uint8_t kdAttenuationCurveDefault[ATTENUATION_CURVE_SIZE] = {100, 95, 90, 85, 85, 85, 85, 100, 100};
#endif //USE_TPA_CURVES

controlRateConfig_t *currentControlRateProfile;

PG_REGISTER_ARRAY_WITH_RESET_FN(controlRateConfig_t, CONTROL_RATE_PROFILE_COUNT, controlRateProfiles, PG_CONTROL_RATE_PROFILES, 1);

void pgResetFn_controlRateProfiles(controlRateConfig_t *controlRateConfig) {
  for (int i = 0; i < CONTROL_RATE_PROFILE_COUNT; i++) {
    RESET_CONFIG(controlRateConfig_t, &controlRateConfig[i],
      .thrMid8 = 50,
      .thrExpo8 = 0,
      .dynThrPID = 10,
      .tpa_breakpoint = 1650,
      .rates_type = RATES_TYPE_BETAFLIGHT,
      .rcRates[FD_ROLL] = 100,
      .rcRates[FD_PITCH] = 100,
      .rcRates[FD_YAW] = 100,
      .rcExpo[FD_ROLL] = 0,
      .rcExpo[FD_PITCH] = 0,
      .rcExpo[FD_YAW] = 0,
      .rates[FD_ROLL] = 70,
      .rates[FD_PITCH] = 70,
      .rates[FD_YAW] = 70,
      .throttle_limit_type = THROTTLE_LIMIT_TYPE_OFF,
      .throttle_limit_percent = 100
    );
    #ifdef USE_TPA_CURVES
    controlRateConfig[i].tpaCurveType = 1;
    memcpy(controlRateConfig[i].tpaKpCurve, kpAttenuationCurveDefault, sizeof(kpAttenuationCurveDefault));
    memcpy(controlRateConfig[i].tpaKiCurve, kiAttenuationCurveDefault, sizeof(kiAttenuationCurveDefault));
    memcpy(controlRateConfig[i].tpaKdCurve, kdAttenuationCurveDefault, sizeof(kdAttenuationCurveDefault));
    #endif
  }
}

void loadControlRateProfile(void) {
  currentControlRateProfile = controlRateProfilesMutable(systemConfig()->activeRateProfile);
}

void changeControlRateProfile(uint8_t controlRateProfileIndex) {
  if (controlRateProfileIndex < CONTROL_RATE_PROFILE_COUNT) {
    systemConfigMutable()->activeRateProfile = controlRateProfileIndex;
  }

  loadControlRateProfile();
  initRcProcessing();
}

void copyControlRateProfile(const uint8_t dstControlRateProfileIndex, const uint8_t srcControlRateProfileIndex) {
  if ((dstControlRateProfileIndex < CONTROL_RATE_PROFILE_COUNT && srcControlRateProfileIndex < CONTROL_RATE_PROFILE_COUNT)
    && dstControlRateProfileIndex != srcControlRateProfileIndex
  ) {
    memcpy(controlRateProfilesMutable(dstControlRateProfileIndex), controlRateProfilesMutable(srcControlRateProfileIndex), sizeof(controlRateConfig_t));
  }
}

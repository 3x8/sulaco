#include <stdint.h>

#include <platform.h>

#include "config/feature.h"
#include "config/config_eeprom.h"
#include "drivers/pwm_output.h"
#include "common/filter.h"
#include "sensors/acceleration.h"
#include "sensors/gyro.h"
#include "sensors/battery.h"
#include "telemetry/telemetry.h"
#include "flight/imu.h"
#include "flight/mixer.h"
#include "flight/pid.h"
#include "fc/config.h"
#include "fc/fc_rc.h"
#include "fc/rc_controls.h"
#include "rx/rx.h"

void targetConfiguration(void) {
  // ERROR in timer initialization (prescaler wrong) when not cpu_overclock
  systemConfigMutable()->cpu_overclock  = 1;

  gyroConfigMutable()->gyro_sync_denom = 4;
  gyroConfigMutable()->gyro_use_32khz = 1;
  gyroConfigMutable()->gyro_32khz_hardware_lpf = 1;
  gyroConfigMutable()->gyro_lowpass_hz = 0;

  imuConfigMutable()->small_angle = 180;

  pidConfigMutable()->pid_process_denom = 1;

  motorConfigMutable()->dev.motorPwmProtocol = PWM_TYPE_PROSHOT1000;

  rxConfigMutable()->rcInterpolation = RC_SMOOTHING_MANUAL;
  rxConfigMutable()->rc_smoothing_type = RC_SMOOTHING_TYPE_FILTER;
  rxConfigMutable()->rc_smoothing_input_type = RC_SMOOTHING_INPUT_PT1;
  rxConfigMutable()->rc_smoothing_input_cutoff = 113;
  rxConfigMutable()->rc_smoothing_derivative_cutoff = 127;
  rxConfigMutable()->rcInterpolationChannels = INTERPOLATION_CHANNELS_RPYT;
  rxConfigMutable()->mincheck = 1000;
  rxConfigMutable()->maxcheck = 2000;

  rcControlsConfigMutable()->deadband = 7;
  rcControlsConfigMutable()->yaw_deadband = 11;

  featureClear(FEATURE_DYNAMIC_FILTER);
  featureSet(FEATURE_AIRMODE | FEATURE_TELEMETRY);

  for (uint8_t pidProfileIndex = 0; pidProfileIndex < MAX_PROFILE_COUNT; pidProfileIndex++) {
    pidProfile_t *pidProfile = pidProfilesMutable(pidProfileIndex);
    pidProfile->dterm_notch_cutoff = 0;
  }
}

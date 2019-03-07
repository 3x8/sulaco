/*
#include <stdint.h>

#include <platform.h>

#include "config/config_eeprom.h"
#include "drivers/pwm_output.h"
#include "common/filter.h"
#include "sensors/acceleration.h"
#include "sensors/gyro.h"
#include "sensors/battery.h"
#include "telemetry/telemetry.h"
#include "flight/mixer.h"
#include "flight/pid.h"
#include "fc/config.h"
#include "fc/fc_rc.h"
#include "fc/rc_controls.h"
#include "rx/rx.h"


void targetConfiguration(void) {
    gyroConfigMutable()->gyro_sync_denom  = 4;
    gyroConfigMutable()->gyro_use_32khz = 1;
    gyroConfigMutable()->gyro_32khz_hardware_lpf = 1;

    pidConfigMutable()->pid_process_denom = 1;

    motorConfigMutable()->dev.motorPwmProtocol = PWM_TYPE_DSHOT600;

    rxConfigMutable()->rcInterpolation = RC_SMOOTHING_MANUAL;
    rxConfigMutable()->rc_smoothing_type = RC_SMOOTHING_TYPE_FILTER;
    rxConfigMutable()->rc_smoothing_input_cutoff = 61;
    rxConfigMutable()->rc_smoothing_derivative_cutoff = 61;
    rxConfigMutable()->rcInterpolationChannels = INTERPOLATION_CHANNELS_RPYT;
    rxConfigMutable()->rcInterpolationInterval = 9;

    rcControlsConfigMutable()->deadband = 7;
    rcControlsConfigMutable()->yaw_deadband = 11;

    for (uint8_t pidProfileIndex = 0; pidProfileIndex < MAX_PROFILE_COUNT; pidProfileIndex++) {
        pidProfile_t *pidProfile = pidProfilesMutable(pidProfileIndex);
        pidProfile->dterm_notch_cutoff = 0;
    }
} */

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
#include "flight/mixer.h"
#include "flight/pid.h"
#include "fc/config.h"
#include "fc/fc_rc.h"
#include "fc/rc_controls.h"
#include "rx/rx.h"

void targetConfiguration(void) {
    telemetryConfigMutable()->halfDuplex = false;
    voltageSensorADCConfigMutable(VOLTAGE_SENSOR_ADC_VBAT)->vbatscale = VBAT_SCALE;
    rxConfigMutable()->rcInterpolation         = RC_SMOOTHING_MANUAL;
    rxConfigMutable()->rcInterpolationInterval = 14;
    rxConfigMutable()->rcInterpolationChannels = INTERPOLATION_CHANNELS_RPYT;
    motorConfigMutable()->dev.motorPwmProtocol = PWM_TYPE_MULTISHOT;
    gyroConfigMutable()->gyro_sync_denom  = 4;
    pidConfigMutable()->pid_process_denom = 1;
    //systemConfigMutable()->cpu_overclock  = 1;
    accelerometerConfigMutable()->acc_lpf_hz  = 10;

    featureClear(FEATURE_DYNAMIC_FILTER);

    for (uint8_t pidProfileIndex = 0; pidProfileIndex < MAX_PROFILE_COUNT; pidProfileIndex++) {
        pidProfile_t *pidProfile = pidProfilesMutable(pidProfileIndex);
        pidProfile->dterm_notch_cutoff = 0;
        pidProfile->dterm_filter_type = FILTER_BIQUAD;
    }
}

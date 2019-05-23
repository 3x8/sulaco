#include "platform.h"

#if defined(USE_PWM) || defined(USE_PPM) || defined(USE_SERIAL_RX) || defined(USE_RX_MSP)

#include "pg/pg.h"
#include "pg/pg_ids.h"
#include "rx.h"

#include "config/config_reset.h"

#include "drivers/io.h"
#include "fc/fc_rc.h"
#include "fc/rc_controls.h"
#include "rx/rx.h"
#include "rx/rx_spi.h"

PG_REGISTER_WITH_RESET_FN(rxConfig_t, rxConfig, PG_RX_CONFIG, 2);
void pgResetFn_rxConfig(rxConfig_t *rxConfig)
{
    RESET_CONFIG_2(rxConfig_t, rxConfig,
        .halfDuplex = 0,
        .serialrx_provider = SERIALRX_PROVIDER,
        .serialrx_inverted = 0,
        .spektrum_bind_pin_override_ioTag = IO_TAG(SPEKTRUM_BIND_PIN),
        .spektrum_bind_plug_ioTag = IO_TAG(BINDPLUG_PIN),
        .spektrum_sat_bind = 0,
        .spektrum_sat_bind_autoreset = 1,
        .midrc = RX_MID_USEC,
        .mincheck = 1050,
        .maxcheck = 1900,
        .rx_min_usec = RX_MIN_USEC,          // any of first 4 channels below this value will trigger rx loss detection
        .rx_max_usec = RX_MAX_USEC,         // any of first 4 channels above this value will trigger rx loss detection
        .rssi_src_frame_errors = false,
        .rssi_channel = 0,
        .rssi_scale = RSSI_SCALE_DEFAULT,
        .rssi_offset = 0,
        .rssi_invert = 0,
        .rcInterpolation = RC_SMOOTHING_AUTO,
        .rcInterpolationChannels = INTERPOLATION_CHANNELS_RPYT,
        .rcInterpolationInterval = 19,
        .fpvCamAngleDegrees = 0,
        .airModeActivateThreshold = 32,
        .max_aux_channel = DEFAULT_AUX_CHANNEL_COUNT,
        .rc_smoothing_type = RC_SMOOTHING_TYPE_INTERPOLATION,
        .rc_smoothing_input_cutoff = 0,      // automatically calculate the cutoff by default
        .rc_smoothing_derivative_cutoff = 0, // automatically calculate the cutoff by default
        .rc_smoothing_debug_axis = ROLL,     // default to debug logging for the roll axis
        .rc_smoothing_input_type = RC_SMOOTHING_INPUT_BIQUAD,
        .rc_smoothing_derivative_type = RC_SMOOTHING_DERIVATIVE_BIQUAD,
    );

#ifdef RX_CHANNELS_TAER
    parseRcChannels("TAER1234", rxConfig);
#else
    parseRcChannels("AETR1234", rxConfig);
#endif
}

#endif

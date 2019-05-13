#include <stdbool.h>
#include <stdint.h>

#include "platform.h"

#ifdef USE_TARGET_CONFIG

#include "fc/config.h"

#include "pg/rx.h"

#include "rx/rx.h"

void targetConfiguration(void)
{
    rxConfigMutable()->serialrx_inverted = true;
    rxConfigMutable()->rssi_scale = 19;
    rxConfigMutable()->serialrx_provider = SERIALRX_SBUS;
}
#endif

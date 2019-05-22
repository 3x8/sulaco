#include <stdbool.h>
#include <stdint.h>

#include "platform.h"

#ifdef USE_TARGET_CONFIG

#include "telemetry/telemetry.h"

#include "pg/piniobox.h"

void targetConfiguration(void)
{
    telemetryConfigMutable()->halfDuplex = false;

    pinioBoxConfigMutable()->permanentId[0] = 40;
}
#endif

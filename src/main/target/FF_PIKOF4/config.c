#include <stdbool.h>
#include <stdint.h>

#include "platform.h"

#ifdef USE_TARGET_CONFIG
#include "telemetry/telemetry.h"

void targetConfiguration(void)
{
    telemetryConfigMutable()->halfDuplex = false;
}
#endif

#include <stdbool.h>
#include <stdint.h>

#include "platform.h"

#ifdef USE_TARGET_CONFIG

#include "fc/config.h"

#include "telemetry/telemetry.h"

void targetConfiguration(void)
{
	telemetryConfigMutable()->halfDuplex = 0;
}
#endif

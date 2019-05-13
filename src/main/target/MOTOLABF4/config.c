#include <stdint.h>
#include <stdbool.h>

#include "platform.h"

#ifdef USE_TARGET_CONFIG

#include "pg/sdcard.h"

#include "telemetry/telemetry.h"

void targetConfiguration(void)
{
    sdcardConfigMutable()->useDma = true;
    telemetryConfigMutable()->halfDuplex = 0;
}
#endif

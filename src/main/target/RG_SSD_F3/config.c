#include <stdint.h>

#include "platform.h"

#ifdef USE_TARGET_CONFIG

#include "fc/config.h"

#include "sensors/battery.h"

void targetConfiguration(void)
{
    batteryConfigMutable()->vbatmaxcellvoltage = 45;
}
#endif

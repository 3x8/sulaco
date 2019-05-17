#include <stdbool.h>
#include <stdint.h>

#include "platform.h"

#ifdef USE_TARGET_CONFIG
#include "fc/config.h"

#include "config/feature.h"

#include "telemetry/telemetry.h"

#include "hardware_revision.h"

void targetConfiguration(void)
{
    if (hardwareRevision >= FORTINIF4_REV_2) {
        featureSet(FEATURE_OSD);
    }

    telemetryConfigMutable()->halfDuplex = false;
}
#endif

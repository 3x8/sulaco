#include <stdint.h>
#include <stdbool.h>

#include "platform.h"

#ifdef USE_TARGET_CONFIG

#include "blackbox/blackbox.h"

#include "config/feature.h"

#include "drivers/adc.h"
#include "drivers/io.h"

#include "sensors/acceleration.h"
#include "sensors/gyro.h"

#include "pg/adc.h"
#include "pg/beeper_dev.h"

#include "hardware_revision.h"

// alternative defaults settings for BlueJayF4 targets
void targetConfiguration(void)
{
    if (hardwareRevision == BJF4_REV1 || hardwareRevision == BJF4_REV2) {
        gyroConfigMutable()->gyro_align = CW180_DEG;
        accelerometerConfigMutable()->acc_align  = CW180_DEG;
        beeperDevConfigMutable()->ioTag = IO_TAG(BEEPER_OPT);
    }

    if (hardwareRevision == BJF4_MINI_REV3A || hardwareRevision == BJF4_REV1) {
        blackboxConfigMutable()->device = BLACKBOX_DEVICE_NONE;
    }

    if (hardwareRevision == BJF4_MINI_REV3A) {
        adcConfigMutable()->vbat.ioTag = IO_TAG(PA4);
    }
}

void targetValidateConfiguration(void)
{
    /* make sure the SDCARD cannot be turned on */
    if (hardwareRevision == BJF4_MINI_REV3A || hardwareRevision == BJF4_REV1) {
        if (blackboxConfig()->device == BLACKBOX_DEVICE_SDCARD) {
            blackboxConfigMutable()->device = BLACKBOX_DEVICE_NONE;
        }
    }
}
#endif

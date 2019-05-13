#include <stdbool.h>
#include <stdint.h>

#include "platform.h"

#ifdef USE_TARGET_CONFIG
#include "blackbox/blackbox.h"

#include "flight/pid.h"

#include "pg/adc.h"
#include "pg/beeper_dev.h"

#include "telemetry/telemetry.h"

#include "hardware_revision.h"



// alternative defaults settings for YuPiF4 targets
void targetConfiguration(void)
{
    /* Changes depending on versions */
    if (hardwareRevision == YUPIF4_RACE3) {
            beeperDevConfigMutable()->ioTag = IO_TAG(BEEPER_OPT);
            telemetryConfigMutable()->halfDuplex = false;

    } else if (hardwareRevision == YUPIF4_RACE2) {
        beeperDevConfigMutable()->ioTag = IO_TAG(BEEPER_OPT);

    } else if (hardwareRevision == YUPIF4_MINI) {
        beeperDevConfigMutable()->frequency = 0;
        blackboxConfigMutable()->device = BLACKBOX_DEVICE_NONE;
        adcConfigMutable()->current.enabled = 0;

    } else if (hardwareRevision == YUPIF4_NAV) {
        beeperDevConfigMutable()->ioTag = IO_TAG(BEEPER_OPT);

    } else {
        adcConfigMutable()->current.enabled = 0;
    }

    /* Specific PID values for YupiF4 */
    for (uint8_t pidProfileIndex = 0; pidProfileIndex < MAX_PROFILE_COUNT; pidProfileIndex++) {
        pidProfile_t *pidProfile = pidProfilesMutable(pidProfileIndex);

        pidProfile->pid[PID_ROLL].P = 30;
        pidProfile->pid[PID_ROLL].I = 45;
        pidProfile->pid[PID_ROLL].D = 20;
        pidProfile->pid[PID_PITCH].P = 30;
        pidProfile->pid[PID_PITCH].I = 50;
        pidProfile->pid[PID_PITCH].D = 20;
        pidProfile->pid[PID_YAW].P = 40;
        pidProfile->pid[PID_YAW].I = 50;
    }
}
#endif

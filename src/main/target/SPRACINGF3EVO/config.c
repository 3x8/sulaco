#include "platform.h"

#ifdef USE_TARGET_CONFIG

#include "common/axis.h"

#include "flight/mixer.h"
#include "flight/pid.h"

#include "pg/sdcard.h"


#if defined(SPRACINGF3MQ)
#ifdef BRUSHED_MOTORS_PWM_RATE
#undef BRUSHED_MOTORS_PWM_RATE
#endif

#define BRUSHED_MOTORS_PWM_RATE 32000           // 32kHz
#endif

void targetConfiguration(void)
{
    // Temporary workaround: Disable SDCard DMA by default since it causes errors on this target
    sdcardConfigMutable()->useDma = false;

#if defined(SPRACINGF3MQ)

    motorConfigMutable()->dev.motorPwmRate = BRUSHED_MOTORS_PWM_RATE;

    for (uint8_t pidProfileIndex = 0; pidProfileIndex < MAX_PROFILE_COUNT; pidProfileIndex++) {
        pidProfile_t *pidProfile = pidProfilesMutable(pidProfileIndex);

        pidProfile->pid[FD_ROLL].P = 90;
        pidProfile->pid[FD_ROLL].I = 44;
        pidProfile->pid[FD_ROLL].D = 60;
        pidProfile->pid[FD_PITCH].P = 90;
        pidProfile->pid[FD_PITCH].I = 44;
        pidProfile->pid[FD_PITCH].D = 60;
    }
#endif
}
#endif

#include <stdbool.h>
#include <stdint.h>
#include <math.h>

#include "platform.h"

#include "common/axis.h"
#include "common/maths.h"

#include "drivers/audio.h"

#include "fc/rc_modes.h"

#include "flight/pid.h"

#include "io/pidaudio.h"

static bool pidAudioEnabled = false;

static pidAudioModes_e pidAudioMode = PID_AUDIO_PIDSUM_XY;

void pidAudioInit(void)
{
    audioSetupIO();
}

void pidAudioStart(void)
{
    audioGenerateWhiteNoise();
}

void pidAudioStop(void)
{
    audioSilence();
}

pidAudioModes_e pidAudioGetMode(void)
{
    return pidAudioMode;
}

void pidAudioSetMode(pidAudioModes_e mode)
{
    pidAudioMode = mode;
}

void FAST_CODE_NOINLINE pidAudioUpdate(void)
{
    bool newState = IS_RC_MODE_ACTIVE(BOXPIDAUDIO);

    if (pidAudioEnabled != newState) {
        if (newState) {
            pidAudioStart();
        } else {
            pidAudioStop();
        }
        pidAudioEnabled = newState;
    }

    if (!pidAudioEnabled) {
        return;
    }

    uint8_t tone = TONE_MID;

    switch (pidAudioMode) {
    case PID_AUDIO_PIDSUM_X:
        {
            const uint32_t pidSumX = MIN(ABS(pidData[FD_ROLL].Sum), PIDSUM_LIMIT);
            tone = scaleRange(pidSumX, 0, PIDSUM_LIMIT, TONE_MAX, TONE_MIN);
            break;
        }
    case PID_AUDIO_PIDSUM_Y:
        {
            const uint32_t pidSumY = MIN(ABS(pidData[FD_PITCH].Sum), PIDSUM_LIMIT);
            tone = scaleRange(pidSumY, 0, PIDSUM_LIMIT, TONE_MAX, TONE_MIN);
            break;
        }
    case PID_AUDIO_PIDSUM_XY:
        {
            const uint32_t pidSumXY = MIN((ABS(pidData[FD_ROLL].Sum) + ABS(pidData[FD_PITCH].Sum)) / 2, PIDSUM_LIMIT);
            tone = scaleRange(pidSumXY, 0, PIDSUM_LIMIT, TONE_MAX, TONE_MIN);
            break;
        }
    default:
        break;
    }

    audioPlayTone(tone);
}

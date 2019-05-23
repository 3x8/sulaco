#include <stdbool.h>
#include <stdint.h>

#include "platform.h"

#include "drivers/io.h"
#include "drivers/pwm_output.h"

#include "pg/beeper_dev.h"

#include "sound_beeper.h"

#ifdef USE_BEEPER
static IO_t beeperIO = DEFIO_IO(NONE);
static bool beeperInverted = false;
static uint16_t beeperFrequency = 0;
#endif

void systemBeep(bool onoff)
{
#ifdef USE_BEEPER
    if (beeperFrequency == 0) {
        IOWrite(beeperIO, beeperInverted ? onoff : !onoff);
    } else {
        pwmWriteBeeper(onoff);
    }
#else
    UNUSED(onoff);
#endif
}

void systemBeepToggle(void)
{
#ifdef USE_BEEPER
    if (beeperFrequency == 0) {
        IOToggle(beeperIO);
    } else {
        pwmToggleBeeper();
    }
#endif
}

void beeperInit(const beeperDevConfig_t *config)
{
#ifdef USE_BEEPER
    beeperFrequency = config->frequency;
    if (beeperFrequency == 0) {
        beeperIO = IOGetByTag(config->ioTag);
        beeperInverted = config->isInverted;
        if (beeperIO) {
            IOInit(beeperIO, OWNER_BEEPER, 0);
            IOConfigGPIO(beeperIO, config->isOpenDrain ? IOCFG_OUT_OD : IOCFG_OUT_PP);
        }
        systemBeep(false);
    } else {
        const ioTag_t beeperTag = config->ioTag;
        beeperPwmInit(beeperTag, beeperFrequency);
    }
#else
    UNUSED(config);
#endif
}

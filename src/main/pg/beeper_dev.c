#include "platform.h"

#ifdef USE_BEEPER

#include "drivers/io.h"
#include "pg/pg.h"
#include "pg/pg_ids.h"

#include "beeper_dev.h"

PG_REGISTER_WITH_RESET_TEMPLATE(beeperDevConfig_t, beeperDevConfig, PG_BEEPER_DEV_CONFIG, 0);

#ifdef BEEPER_INVERTED
#define IS_OPEN_DRAIN   false
#define IS_INVERTED     true
#else
#define IS_OPEN_DRAIN   true
#define IS_INVERTED     false
#endif

#ifndef BEEPER_PWM_HZ
#define BEEPER_PWM_HZ   0
#endif

#ifndef BEEPER_PIN
#define BEEPER_PIN      NONE
#endif

PG_RESET_TEMPLATE(beeperDevConfig_t, beeperDevConfig,
    .isOpenDrain = IS_OPEN_DRAIN,
    .isInverted = IS_INVERTED,
    .ioTag = IO_TAG(BEEPER_PIN),
    .frequency = BEEPER_PWM_HZ
);
#endif

#include "platform.h"

#ifdef USE_BEEPER

#include "io/beeper.h"

#include "pg/pg.h"
#include "pg/pg_ids.h"

#include "beeper.h"

PG_REGISTER_WITH_RESET_TEMPLATE(beeperConfig_t, beeperConfig, PG_BEEPER_CONFIG, 2);

PG_RESET_TEMPLATE(beeperConfig_t, beeperConfig,
    .dshotBeaconTone = 1,
    .dshotBeaconOffFlags = DSHOT_BEACON_ALLOWED_MODES,
);
#endif

#include "platform.h"

#if defined(USE_SDCARD_SDIO)

#include "pg/pg_ids.h"
#include "pg/sdio.h"

PG_REGISTER_WITH_RESET_TEMPLATE(sdioConfig_t, sdioConfig, PG_SDIO_CONFIG, 0);

PG_RESET_TEMPLATE(sdioConfig_t, sdioConfig,
    .clockBypass = 0,
    .useCache = 0,
);

#endif

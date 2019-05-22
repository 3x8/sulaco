#include "platform.h"

#ifdef USE_DASHBOARD

#include "pg/pg.h"
#include "pg/pg_ids.h"

#include "io/dashboard.h"

#include "dashboard.h"

PG_REGISTER_WITH_RESET_TEMPLATE(dashboardConfig_t, dashboardConfig, PG_DASHBOARD_CONFIG, 0);

PG_RESET_TEMPLATE(dashboardConfig_t, dashboardConfig,
    .device = I2C_DEV_TO_CFG(DASHBOARD_I2C_INSTANCE),
    .address = DASHBOARD_I2C_ADDRESS,
);
#endif

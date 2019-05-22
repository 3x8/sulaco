#include "platform.h"

#ifdef USE_PINIOBOX

#include "pg/pg_ids.h"
#include "piniobox.h"
#include "drivers/io.h"
#include "interface/msp_box.h"

PG_REGISTER_WITH_RESET_TEMPLATE(pinioBoxConfig_t, pinioBoxConfig, PG_PINIOBOX_CONFIG, 1);

PG_RESET_TEMPLATE(pinioBoxConfig_t, pinioBoxConfig,
    { PERMANENT_ID_NONE, PERMANENT_ID_NONE, PERMANENT_ID_NONE, PERMANENT_ID_NONE }
);
#endif

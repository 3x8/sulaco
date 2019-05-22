#include "platform.h"

#include "pg/pg.h"
#include "pg/pg_ids.h"

#include "vcd.h"

// no template required since defaults are zero
PG_REGISTER(vcdProfile_t, vcdProfile, PG_VCD_CONFIG, 0);

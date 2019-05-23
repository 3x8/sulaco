#include "platform.h"

#ifdef USE_PINIO

#include "pg/pg_ids.h"
#include "pinio.h"
#include "drivers/io.h"

#ifndef PINIO1_PIN
#define PINIO1_PIN NONE
#endif
#ifndef PINIO2_PIN
#define PINIO2_PIN NONE
#endif
#ifndef PINIO3_PIN
#define PINIO3_PIN NONE
#endif
#ifndef PINIO4_PIN
#define PINIO4_PIN NONE
#endif

PG_REGISTER_WITH_RESET_TEMPLATE(pinioConfig_t, pinioConfig, PG_PINIO_CONFIG, 0);

PG_RESET_TEMPLATE(pinioConfig_t, pinioConfig,
    .ioTag = {
        IO_TAG(PINIO1_PIN),
        IO_TAG(PINIO2_PIN),
        IO_TAG(PINIO3_PIN),
        IO_TAG(PINIO4_PIN),
    },
    .config = {
        PINIO_CONFIG_MODE_OUT_PP,
        PINIO_CONFIG_MODE_OUT_PP,
        PINIO_CONFIG_MODE_OUT_PP,
        PINIO_CONFIG_MODE_OUT_PP
    },
);
#endif

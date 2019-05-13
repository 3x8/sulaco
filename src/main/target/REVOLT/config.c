#include <stdbool.h>
#include <stdint.h>

#include "platform.h"

#include "drivers/serial.h"
#include "pg/rx.h"
#include "rx/rx.h"

#include "telemetry/telemetry.h"

#include "fc/config.h"


#ifdef USE_TARGET_CONFIG

#include "pg/pg.h"


void targetConfiguration(void)
{
    rxConfigMutable()->halfDuplex = true;
}
#endif

#include <stdint.h>

#include "platform.h"
#include "io/serial.h"
#include "pg/piniobox.h"
#include "target.h"

#ifdef USE_TARGET_CONFIG

void targetConfiguration(void)
{
    pinioBoxConfigMutable()->permanentId[0] = 40;
    pinioBoxConfigMutable()->permanentId[1] = 41;
}

#endif

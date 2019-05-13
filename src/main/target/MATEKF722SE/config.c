#include <stdint.h>

#include "platform.h"
#include "io/serial.h"
//#include "pg/pinio.h"
#include "pg/piniobox.h"
#include "target.h"

#define  USE_TARGET_CONFIG

void targetConfiguration(void)
{
    pinioBoxConfigMutable()->permanentId[0] = 40;
    pinioBoxConfigMutable()->permanentId[1] = 41;

}

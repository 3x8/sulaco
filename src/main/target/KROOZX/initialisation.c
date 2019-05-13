#include <stdbool.h>
#include <stdint.h>
#include "drivers/io.h"
#include "drivers/bus_i2c.h"
#include "drivers/bus_spi.h"

void targetPreInit(void)
{
    IO_t osdChSwitch = IOGetByTag(IO_TAG(OSD_CH_SWITCH));
    IOInit(osdChSwitch, OWNER_SYSTEM, 0);
    IOConfigGPIO(osdChSwitch, IOCFG_OUT_PP);
    IOLo(osdChSwitch);
}

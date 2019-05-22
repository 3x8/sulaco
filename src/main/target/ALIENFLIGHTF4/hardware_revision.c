#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "platform.h"

#include "build/build_config.h"

#include "drivers/io.h"
#include "drivers/time.h"
#include "hardware_revision.h"

uint8_t hardwareRevision = AFF4_UNKNOWN;

static IO_t HWDetectPin = IO_NONE;

void detectHardwareRevision(void)
{
    HWDetectPin = IOGetByTag(IO_TAG(HW_PIN));
    IOInit(HWDetectPin, OWNER_SYSTEM, 0);
    IOConfigGPIO(HWDetectPin, IOCFG_IPU);

    delayMicroseconds(40);  // allow configuration to settle

    // Check hardware revision
    if (IORead(HWDetectPin)) {
        hardwareRevision = AFF4_REV_1;
    } else {
        hardwareRevision = AFF4_REV_2;
    }
}

void updateHardwareRevision(void)
{
}

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "platform.h"

#include "build/build_config.h"

#include "drivers/io.h"
#include "drivers/time.h"

#include "hardware_revision.h"

uint8_t hardwareRevision = FORTINIF4_UNKNOWN;

static IO_t HWDetectPinA = IO_NONE;
static IO_t HWDetectPinB = IO_NONE;

void detectHardwareRevision(void)
{
    HWDetectPinA = IOGetByTag(IO_TAG(HW_PIN_A));
    IOInit(HWDetectPinA, OWNER_SYSTEM, 0);
    IOConfigGPIO(HWDetectPinA, IOCFG_IPU);
    HWDetectPinB = IOGetByTag(IO_TAG(HW_PIN_B));
    IOInit(HWDetectPinB, OWNER_SYSTEM, 0);
    IOConfigGPIO(HWDetectPinB, IOCFG_IPU);

    delayMicroseconds(10);  // allow configuration to settle

    // Check hardware revision
    if (IORead(HWDetectPinB)) {
        if (IORead(HWDetectPinA)) {
            hardwareRevision = FORTINIF4_REV_1;
        } else {
            hardwareRevision = FORTINIF4_REV_2;
        }
    } else {
        if (IORead(HWDetectPinA)) {
            hardwareRevision = FORTINIF4_REV_4;
        } else {
            hardwareRevision = FORTINIF4_REV_3;
        }
    }
}

void updateHardwareRevision(void)
{
}

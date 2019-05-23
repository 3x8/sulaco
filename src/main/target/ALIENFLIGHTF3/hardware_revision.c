#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "platform.h"

#include "build/build_config.h"

#include "drivers/io.h"
#include "drivers/time.h"

#include "hardware_revision.h"

uint8_t hardwareRevision = AFF3_UNKNOWN;
bool haveFrSkyRX = true;

static IO_t HWDetectPin = IO_NONE;
static IO_t RXDetectPin = IO_NONE;

void detectHardwareRevision(void)
{
    HWDetectPin = IOGetByTag(IO_TAG(HW_PIN));
    IOInit(HWDetectPin, OWNER_SYSTEM, 0);
    IOConfigGPIO(HWDetectPin, IOCFG_IPU);

    RXDetectPin = IOGetByTag(IO_TAG(BEEPER_PIN));
    IOInit(RXDetectPin, OWNER_SYSTEM, 0);
    IOConfigGPIO(RXDetectPin, IOCFG_IPU);

    delayMicroseconds(40);  // allow configuration to settle

    // Check hardware revision
    if (IORead(HWDetectPin)) {
        hardwareRevision = AFF3_REV_1;
    } else {
        hardwareRevision = AFF3_REV_2;
    }

    // Check for integrated OpenSky reciever
    if (IORead(RXDetectPin)) {
        haveFrSkyRX = false;
    }
}

void updateHardwareRevision(void)
{
}

ioTag_t selectMPUIntExtiConfigByHardwareRevision(void)
{
    if (hardwareRevision == AFF3_REV_1) {
        // MPU_INT output on V1 PA15
        return IO_TAG(PA15);
    } else {
        // MPU_INT output on V2 PB13
        return IO_TAG(PB13);
    }
}

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "platform.h"

#include "build/build_config.h"

#include "drivers/io_types.h"

#include "hardware_revision.h"

uint8_t hardwareRevision = UNKNOWN;

void detectHardwareRevision(void)
{
    if (GPIOC->IDR & GPIO_Pin_15) {
        hardwareRevision = REV_2;
    } else {
        hardwareRevision = REV_1;
    }
}

void updateHardwareRevision(void)
{
}

ioTag_t selectMPUIntExtiConfigByHardwareRevision(void)
{
    return IO_TAG_NONE;
}

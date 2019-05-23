#include "drivers/io.h"
#include "timer.h"
#ifdef USE_TIMER_MGMT
#include "pg/timerio.h"
#endif

uint8_t timerIndexByTag(ioTag_t ioTag)
{
#ifdef USE_TIMER_MGMT
    for (unsigned i = 0; i < MAX_TIMER_PINMAP_COUNT; i++) {
        if (timerIOConfig(i)->ioTag == ioTag) {
            return timerIOConfig(i)->index;
        }
    }
#else
    UNUSED(ioTag);
#endif
    return 0;
}

const timerHardware_t *timerGetByTag(ioTag_t ioTag)
{
    if (!ioTag) {
        return NULL;
    }

    uint8_t timerIndex = timerIndexByTag(ioTag);
    uint8_t index = 1;

    for (int i = 0; i < (int)USABLE_TIMER_CHANNEL_COUNT; i++) {
        if (timerHardware[i].tag == ioTag) {
            if (index == timerIndex || timerIndex == 0) {
                return &timerHardware[i];
            }
            index++;
        }
    }
    return NULL;
}

ioTag_t timerioTagGetByUsage(timerUsageFlag_e usageFlag, uint8_t index)
{
    uint8_t currentIndex = 0;
    for (int i = 0; i < (int)USABLE_TIMER_CHANNEL_COUNT; i++) {
        if ((timerHardware[i].usageFlags & usageFlag) == usageFlag) {
            if (currentIndex == index) {
                return timerHardware[i].tag;
            }
            currentIndex++;
        }
    }
    return IO_TAG_NONE;
}

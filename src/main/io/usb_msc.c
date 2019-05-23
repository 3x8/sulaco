#include <stdbool.h>

#include "platform.h"

#include "blackbox/blackbox.h"

#include "drivers/sdcard.h"

#include "io/flashfs.h"

#if defined(USE_USB_MSC)

bool mscCheckFilesystemReady(void)
{
    return false
#if defined(USE_SDCARD)
        || (blackboxConfig()->device == BLACKBOX_DEVICE_SDCARD && sdcard_isFunctional())
#endif
#if defined(USE_FLASHFS)
        || (blackboxConfig()->device == BLACKBOX_DEVICE_FLASH && flashfsGetSize() > 0)
#endif
        ;
}
#endif

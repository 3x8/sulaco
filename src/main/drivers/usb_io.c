#include <stdbool.h>
#include <stdint.h>

#include "platform.h"

#ifdef USE_VCP

#include "drivers/io.h"
#include "drivers/time.h"
#include "usb_io.h"
#include "sdcard.h"


#ifdef USE_USB_DETECT
static IO_t usbDetectPin = IO_NONE;
#endif

void usbCableDetectDeinit(void)
{
#ifdef USE_USB_DETECT
    IOInit(usbDetectPin, OWNER_FREE, 0);
    IOConfigGPIO(usbDetectPin, IOCFG_IN_FLOATING);
    usbDetectPin = IO_NONE;
#endif
}

void usbCableDetectInit(void)
{
#ifdef USE_USB_DETECT
#ifndef USB_DETECT_PIN
#define USB_DETECT_PIN NONE
#endif
    usbDetectPin = IOGetByTag(IO_TAG(USB_DETECT_PIN));

    IOInit(usbDetectPin, OWNER_USB_DETECT, 0);
    IOConfigGPIO(usbDetectPin, IOCFG_OUT_PP);
#endif
}

bool usbCableIsInserted(void)
{
    bool result = false;

#ifdef USE_USB_DETECT
    if (usbDetectPin) {
        result = IORead(usbDetectPin) != 0;
    }
#endif

    return result;
}

void usbGenerateDisconnectPulse(void)
{
    /* Pull down PA12 to create USB disconnect pulse */
    IO_t usbPin = IOGetByTag(IO_TAG(PA12));
    IOConfigGPIO(usbPin, IOCFG_OUT_OD);

    IOLo(usbPin);

    delay(200);

    IOHi(usbPin);
}
#endif

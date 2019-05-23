#include "platform.h"

#if defined(USE_USB_ADVANCED_PROFILES)
#include "drivers/io.h"

#include "pg/pg_ids.h"

#include "usb.h"

#if !defined(USB_MSC_BUTTON_PIN)
#define USB_MSC_BUTTON_PIN NONE
#endif

#if defined(USE_USB_MSC_BUTTON_IPU)
#define MSC_BUTTON_IPU true
#else
#define MSC_BUTTON_IPU false
#endif

PG_REGISTER_WITH_RESET_TEMPLATE(usbDev_t, usbDevConfig, PG_USB_CONFIG, 0);

PG_RESET_TEMPLATE(usbDev_t, usbDevConfig,
    .type = DEFAULT,
    .mscButtonPin = IO_TAG(USB_MSC_BUTTON_PIN),
    .mscButtonUsePullup = MSC_BUTTON_IPU,
);
#endif

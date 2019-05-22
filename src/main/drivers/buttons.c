#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "platform.h"

#if defined(USE_BUTTONS)

#include "drivers/io.h"

#include "drivers/buttons.h"

#ifdef BUTTON_A_PIN
static IO_t buttonAPin = IO_NONE;
#endif

#ifdef BUTTON_B_PIN
static IO_t buttonBPin = IO_NONE;
#endif

#ifdef BUTTON_A_PIN_INVERTED
#define BUTTON_A_PIN_GPIO_MODE IOCFG_IPD
#else
#define BUTTON_A_PIN_GPIO_MODE IOCFG_IPU
#endif

#ifdef BUTTON_B_PIN_INVERTED
#define BUTTON_B_PIN_GPIO_MODE IOCFG_IPD
#else
#define BUTTON_B_PIN_GPIO_MODE IOCFG_IPU
#endif

void buttonsInit(void)
{
#ifdef BUTTON_A_PIN
    buttonAPin = IOGetByTag(IO_TAG(BUTTON_A_PIN));
    IOInit(buttonAPin, OWNER_SYSTEM, 0);
    IOConfigGPIO(buttonAPin, BUTTON_A_PIN_GPIO_MODE);
#endif

#ifdef BUTTON_B_PIN
    buttonBPin = IOGetByTag(IO_TAG(BUTTON_B_PIN));
    IOInit(buttonBPin, OWNER_SYSTEM, 0);
    IOConfigGPIO(buttonBPin, BUTTON_B_PIN_GPIO_MODE);
#endif
}

#ifdef BUTTON_A_PIN
bool buttonAPressed(void)
{
#ifdef BUTTON_A_PIN_INVERTED
    return IORead(buttonAPin);
#else
    return !IORead(buttonAPin);
#endif
}
#endif

#ifdef BUTTON_B_PIN
bool buttonBPressed(void)
{
#ifdef BUTTON_B_PIN_INVERTED
    return IORead(buttonBPin);
#else
    return !IORead(buttonBPin);
#endif
}
#endif

#endif

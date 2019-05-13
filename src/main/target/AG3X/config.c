#include <stdbool.h>
#include <stdint.h>

#include "platform.h"

#ifdef USE_TARGET_CONFIG

#include "io/serial.h"

#include "config_helper.h"

static targetSerialPortFunction_t targetSerialPortFunction[] = {
    { SERIAL_PORT_USART1,      FUNCTION_RX_SERIAL },
    { SERIAL_PORT_UART4,       FUNCTION_ESC_SENSOR },
    // { SERIAL_PORT_SOFTSERIAL1, FUNCTION_VTX_SMARTAUDIO },
};

void targetConfiguration(void)
{
    targetSerialPortFunctionConfig(targetSerialPortFunction, ARRAYLEN(targetSerialPortFunction));
}
#endif

#include <stdbool.h>
#include <stdint.h>

#include "platform.h"

#ifdef USE_TARGET_CONFIG

#include "pg/pg.h"
#include "drivers/max7456.h"
#include "io/serial.h"

#include "config_helper.h"

static targetSerialPortFunction_t targetSerialPortFunction[] = {
#ifdef OMNIBUSF4V6
    { SERIAL_PORT_USART6, FUNCTION_RX_SERIAL },
#else
    { SERIAL_PORT_USART1, FUNCTION_RX_SERIAL },
    { SERIAL_PORT_UART4,  FUNCTION_ESC_SENSOR },
#endif
};

void targetConfiguration(void)
{
    targetSerialPortFunctionConfig(targetSerialPortFunction, ARRAYLEN(targetSerialPortFunction));
}
#endif

#include <stdbool.h>
#include <stdint.h>

#include "platform.h"

#ifdef USE_TARGET_CONFIG

#include "config_helper.h"

#include "io/serial.h"

#include "pg/max7456.h"
#include "pg/pg.h"

#ifdef EXUAVF4PRO
static targetSerialPortFunction_t targetSerialPortFunction[] = {
    { SERIAL_PORT_USART1, FUNCTION_TELEMETRY_SMARTPORT },
    { SERIAL_PORT_USART3, FUNCTION_VTX_TRAMP },
    { SERIAL_PORT_UART4,  FUNCTION_RCDEVICE },
    { SERIAL_PORT_USART6, FUNCTION_RX_SERIAL },
};
#endif

void targetConfiguration(void)
{
#ifdef OMNIBUSF4BASE
    // OMNIBUS F4 AIO (1st gen) has a AB7456 chip that is detected as MAX7456
    max7456ConfigMutable()->clockConfig = MAX7456_CLOCK_CONFIG_FULL;
#endif

#ifdef EXUAVF4PRO
    targetSerialPortFunctionConfig(targetSerialPortFunction, ARRAYLEN(targetSerialPortFunction));
#endif
}
#endif

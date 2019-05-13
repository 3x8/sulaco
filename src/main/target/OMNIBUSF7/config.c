#include <stdbool.h>
#include <stdint.h>

#include "platform.h"

#ifdef USE_TARGET_CONFIG

#include "config_helper.h"

#include "io/serial.h"

static targetSerialPortFunction_t targetSerialPortFunction[] = {
#if defined(OMNIBUSF7V2) && defined(ESC_SENSOR_UART)
    // OMNIBUS F7 V2 has an option to connect UART7_RX to ESC telemetry
    { ESC_SENSOR_UART, FUNCTION_ESC_SENSOR },
#else
    { SERIAL_PORT_NONE, FUNCTION_NONE },
#endif
};

void targetConfiguration(void)
{
    targetSerialPortFunctionConfig(targetSerialPortFunction, ARRAYLEN(targetSerialPortFunction));
}
#endif

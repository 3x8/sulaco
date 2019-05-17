#include <stdint.h>
#include "platform.h"

#ifdef USE_TARGET_CONFIG
#include "drivers/io.h"
#include "pg/rx.h"
#include "rx/rx.h"
#include "io/serial.h"

#include "config_helper.h"

#define TELEMETRY_UART          SERIAL_PORT_USART3

static targetSerialPortFunction_t targetSerialPortFunction[] = {
    { TELEMETRY_UART, FUNCTION_TELEMETRY_SMARTPORT },
};

void targetConfiguration(void)
{
    targetSerialPortFunctionConfig(targetSerialPortFunction, ARRAYLEN(targetSerialPortFunction));
    rxConfigMutable()->rssi_channel = 8;
}
#endif

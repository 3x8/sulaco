#include <stdbool.h>
#include <stdint.h>

#include "platform.h"

#include "drivers/serial.h"

#include "telemetry/telemetry.h"

#include "fc/config.h"

#include "config_helper.h"

#define GPS_UART                            SERIAL_PORT_USART3
#define TELEMETRY_UART                      SERIAL_PORT_UART5
#define TELEMETRY_PROVIDER_DEFAULT          FUNCTION_TELEMETRY_SMARTPORT

static targetSerialPortFunction_t targetSerialPortFunction[] = {
    { GPS_UART,           FUNCTION_GPS },
    { TELEMETRY_UART,     TELEMETRY_PROVIDER_DEFAULT },
};

#ifdef USE_TARGET_CONFIG
void targetConfiguration(void)
{
    targetSerialPortFunctionConfig(targetSerialPortFunction, ARRAYLEN(targetSerialPortFunction));
    telemetryConfigMutable()->halfDuplex = false;
}
#endif

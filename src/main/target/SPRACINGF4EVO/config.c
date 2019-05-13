#include <stdbool.h>
#include <stdint.h>

#include "platform.h"

#ifdef USE_TARGET_CONFIG

#include "io/serial.h"

#include "pg/rx.h"

#include "rx/rx.h"

#include "sensors/barometer.h"

#include "telemetry/telemetry.h"

#include "config_helper.h"

#define TELEMETRY_UART                      SERIAL_PORT_UART5

static targetSerialPortFunction_t targetSerialPortFunction[] = {
    { SERIAL_PORT_USART1, FUNCTION_MSP                 },  // So SPRacingF3OSD users don't have to change anything.
    { TELEMETRY_UART,     FUNCTION_TELEMETRY_SMARTPORT },
};

void targetConfiguration(void)
{
    barometerConfigMutable()->baro_hardware = BARO_DEFAULT;
    targetSerialPortFunctionConfig(targetSerialPortFunction, ARRAYLEN(targetSerialPortFunction));
    telemetryConfigMutable()->halfDuplex = 0;
    telemetryConfigMutable()->telemetry_inverted = true;
}
#endif

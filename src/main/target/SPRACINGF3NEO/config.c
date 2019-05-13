#include <stdbool.h>
#include <stdint.h>

#include "platform.h"

#include "common/axis.h"

#include "drivers/sensor.h"
#include "drivers/compass/compass.h"
#include "drivers/serial.h"

#include "fc/rc_controls.h"

#include "flight/failsafe.h"
#include "flight/mixer.h"
#include "flight/pid.h"

#include "pg/rx.h"

#include "rx/rx.h"

#include "io/serial.h"

#include "telemetry/telemetry.h"

#include "sensors/sensors.h"
#include "sensors/compass.h"
#include "sensors/barometer.h"

#include "config/feature.h"

#include "fc/config.h"

#ifdef USE_TARGET_CONFIG

#include "config_helper.h"

#define GPS_UART                            SERIAL_PORT_USART3

#define TELEMETRY_UART                      SERIAL_PORT_UART5
#define TELEMETRY_PROVIDER_DEFAULT          FUNCTION_TELEMETRY_SMARTPORT

static targetSerialPortFunction_t targetSerialPortFunction[] = {
    { SERIAL_PORT_USART1, FUNCTION_MSP },
    { TELEMETRY_UART,     TELEMETRY_PROVIDER_DEFAULT },
    { GPS_UART,           FUNCTION_GPS },
};

void targetConfiguration(void)
{
    barometerConfigMutable()->baro_hardware = BARO_DEFAULT;
    compassConfigMutable()->mag_hardware = MAG_DEFAULT;
    targetSerialPortFunctionConfig(targetSerialPortFunction, ARRAYLEN(targetSerialPortFunction));
    telemetryConfigMutable()->halfDuplex = true;
}
#endif

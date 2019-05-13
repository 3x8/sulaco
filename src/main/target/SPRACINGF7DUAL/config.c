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

#define TELEMETRY_UART                      SERIAL_PORT_UART5

#ifdef USE_TELEMETRY
static targetSerialPortFunction_t targetSerialPortFunction[] = {
    { TELEMETRY_UART, FUNCTION_TELEMETRY_SMARTPORT },
};
#endif

void targetConfiguration(void)
{
    barometerConfigMutable()->baro_hardware = BARO_DEFAULT;

#ifdef USE_TELEMETRY
    targetSerialPortFunctionConfig(targetSerialPortFunction, ARRAYLEN(targetSerialPortFunction));
    // change telemetry settings
    telemetryConfigMutable()->telemetry_inverted = 1;
    telemetryConfigMutable()->halfDuplex = 1;
#endif
}
#endif

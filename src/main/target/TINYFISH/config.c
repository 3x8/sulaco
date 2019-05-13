#include <stdint.h>

#include "platform.h"

#ifdef USE_TARGET_CONFIG
#include "drivers/dma.h"
#include "drivers/io.h"
#include "drivers/timer.h"

#include "config/feature.h"

#include "fc/config.h"

#include "io/serial.h"

#include "pg/rx.h"

#include "rx/rx.h"

#include "sensors/battery.h"

#include "telemetry/telemetry.h"

// set default settings to match our target
void targetConfiguration(void)
{
    // use the same uart for frsky telemetry and SBUS, both non inverted
    const int index = findSerialPortIndexByIdentifier(SBUS_TELEMETRY_UART);
    serialConfigMutable()->portConfigs[index].functionMask = FUNCTION_TELEMETRY_FRSKY_HUB | FUNCTION_RX_SERIAL;

    rxConfigMutable()->serialrx_provider = SERIALRX_SBUS;
    rxConfigMutable()->serialrx_inverted = true;
    telemetryConfigMutable()->telemetry_inverted = true;
}
#endif

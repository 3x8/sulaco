#include <stdbool.h>
#include <stdint.h>

#include "platform.h"

#ifdef USE_TARGET_CONFIG

#include "io/serial.h"

#include "build/debug.h"

void targetConfiguration(void)
{
    // SOFTSERIAL1 is ESC telemetry input
    const int index = findSerialPortIndexByIdentifier(SERIAL_PORT_SOFTSERIAL1);
    if (index >= 0) {
        serialConfigMutable()->portConfigs[index].functionMask = FUNCTION_ESC_SENSOR;
    }
}
#endif

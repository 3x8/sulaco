#include <stdbool.h>
#include <stdint.h>

#include "platform.h"

#ifdef USE_TARGET_CONFIG

#include "config_helper.h"
#include "io/serial.h"
#include "pg/bus_spi.h"
#include "rx/rx.h"
#include "telemetry/telemetry.h"

#define TELEMETRY_UART          SERIAL_PORT_USART1

static targetSerialPortFunction_t targetSerialPortFunction[] = {
    { TELEMETRY_UART, FUNCTION_TELEMETRY_SMARTPORT },
};

void targetConfiguration(void)
{
    targetSerialPortFunctionConfig(targetSerialPortFunction, ARRAYLEN(targetSerialPortFunction));
    telemetryConfigMutable()->halfDuplex = 0;
    telemetryConfigMutable()->telemetry_inverted = true;

    // Register MAX7456 CS pin as OPU

    // Invalidate IPU entry first
    for (int i = 0 ; i < SPI_PREINIT_IPU_COUNT ; i++) {
        if (spiPreinitIPUConfig(i)->csnTag == IO_TAG(MAX7456_SPI_CS_PIN)) {
            spiPreinitIPUConfigMutable(i)->csnTag = IO_TAG(NONE);
            break;
        }
    }

    // Add as OPU entry
    for (int i = 0 ; i < SPI_PREINIT_OPU_COUNT ; i++) {
        if (spiPreinitOPUConfig(i)->csnTag == IO_TAG(NONE)) {
            spiPreinitOPUConfigMutable(i)->csnTag = IO_TAG(MAX7456_SPI_CS_PIN);
            break;
        }
    }
}
#endif

#include "platform.h"

#ifdef USE_TARGET_CONFIG

#include "io/serial.h"

#include "config_helper.h"

static targetSerialPortFunction_t targetSerialPortFunction[] = {
    { SERIAL_PORT_USART1, FUNCTION_MSP },
    { SERIAL_PORT_USART2, FUNCTION_MSP },
};

void targetConfiguration(void)
{
    targetSerialPortFunctionConfig(targetSerialPortFunction, ARRAYLEN(targetSerialPortFunction));
}
#endif

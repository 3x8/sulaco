#pragma once

#include "io/serial.h"

typedef struct targetSerialPortFunction_s {
    serialPortIdentifier_e identifier;
    serialPortFunction_e   function;
} targetSerialPortFunction_t;

void targetSerialPortFunctionConfig(targetSerialPortFunction_t *config, size_t count);

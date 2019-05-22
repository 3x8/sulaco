#pragma once

#define ESCSERIAL_BUFFER_SIZE 1024

typedef enum {
    ESCSERIAL1 = 0,
    ESCSERIAL2
} escSerialPortIndex_e;

typedef enum {
    PROTOCOL_SIMONK = 0,
    PROTOCOL_BLHELI = 1,
    PROTOCOL_KISS = 2,
    PROTOCOL_KISSALL = 3,
    PROTOCOL_CASTLE = 4,
    PROTOCOL_COUNT
} escProtocol_e;

// serialPort API
void escEnablePassthrough(serialPort_t *escPassthroughPort, uint16_t output, uint8_t mode);

typedef struct escSerialConfig_s {
    ioTag_t ioTag;
} escSerialConfig_t;

PG_DECLARE(escSerialConfig_t, escSerialConfig);

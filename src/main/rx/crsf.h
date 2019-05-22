#pragma once

#include "interface/crsf_protocol.h"


#define CRSF_PORT_OPTIONS       (SERIAL_STOPBITS_1 | SERIAL_PARITY_NO)
#define CRSF_PORT_MODE          MODE_RXTX

#define CRSF_MAX_CHANNEL        16

typedef struct crsfFrameDef_s {
    uint8_t deviceAddress;
    uint8_t frameLength;
    uint8_t type;
    uint8_t payload[CRSF_PAYLOAD_SIZE_MAX + 1]; // +1 for CRC at end of payload
} crsfFrameDef_t;

typedef union crsfFrame_u {
    uint8_t bytes[CRSF_FRAME_SIZE_MAX];
    crsfFrameDef_t frame;
} crsfFrame_t;

void crsfRxWriteTelemetryData(const void *data, int len);
void crsfRxSendTelemetryData(void);

struct rxConfig_s;
struct rxRuntimeConfig_s;
bool crsfRxInit(const struct rxConfig_s *initialRxConfig, struct rxRuntimeConfig_s *rxRuntimeConfig);
bool crsfRxIsActive(void);

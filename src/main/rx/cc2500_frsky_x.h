#pragma once

#include "rx/rx.h"
#include "rx/rx_spi.h"

#define RC_CHANNEL_COUNT_FRSKY_X 16

void frSkyXSetRcData(uint16_t *rcData, const uint8_t *payload);

void frSkyXInit(void);
rx_spi_received_e frSkyXHandlePacket(uint8_t * const packet, uint8_t * const protocolState);

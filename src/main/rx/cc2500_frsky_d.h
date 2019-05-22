#pragma once

#include "rx/rx.h"
#include "rx/rx_spi.h"

#define RC_CHANNEL_COUNT_FRSKY_D 8

void frSkyDSetRcData(uint16_t *rcData, const uint8_t *payload);

void frSkyDInit(void);
rx_spi_received_e frSkyDHandlePacket(uint8_t * const packet, uint8_t * const protocolState);

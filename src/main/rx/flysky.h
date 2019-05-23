#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef struct flySkyConfig_s {
    uint32_t txId;
    uint8_t rfChannelMap[16];
    rx_spi_protocol_e protocol;
} flySkyConfig_t;

PG_DECLARE(flySkyConfig_t, flySkyConfig);

struct rxSpiConfig_s;
struct rxRuntimeConfig_s;
bool flySkyInit(const struct rxSpiConfig_s *rxConfig, struct rxRuntimeConfig_s *rxRuntimeConfig);
void flySkySetRcDataFromPayload(uint16_t *rcData, const uint8_t *payload);
rx_spi_received_e flySkyDataReceived(uint8_t *payload);

#pragma once

#include <stdbool.h>
#include <stdint.h>

struct rxSpiConfig_s;
struct rxRuntimeConfig_s;
bool cx10Nrf24Init(const struct rxSpiConfig_s *rxSpiConfig, struct rxRuntimeConfig_s *rxRuntimeConfig);
void cx10Nrf24SetRcDataFromPayload(uint16_t *rcData, const uint8_t *payload);
rx_spi_received_e cx10Nrf24DataReceived(uint8_t *payload);

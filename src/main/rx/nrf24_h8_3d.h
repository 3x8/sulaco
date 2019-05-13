#pragma once

#include <stdbool.h>
#include <stdint.h>

struct rxSpiConfig_s;
struct rxRuntimeConfig_s;
bool h8_3dNrf24Init(const struct rxSpiConfig_s *rxSpiConfig, struct rxRuntimeConfig_s *rxRuntimeConfig);
void h8_3dNrf24SetRcDataFromPayload(uint16_t *rcData, const uint8_t *payload);
rx_spi_received_e h8_3dNrf24DataReceived(uint8_t *payload);

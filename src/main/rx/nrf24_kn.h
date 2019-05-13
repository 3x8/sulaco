#pragma once

#include <stdbool.h>
#include <stdint.h>

struct rxConfig_s;
struct rxRuntimeConfig_s;
bool knNrf24Init(const struct rxConfig_s *rxConfig, struct rxRuntimeConfig_s *rxRuntimeConfig);
void knNrf24SetRcDataFromPayload(uint16_t *rcData, const uint8_t *payload);
rx_spi_received_e knNrf24DataReceived(uint8_t *payload);

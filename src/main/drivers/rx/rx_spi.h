#pragma once

#include <stdint.h>

#define RX_SPI_MAX_PAYLOAD_SIZE 32

struct rxSpiConfig_s;

bool rxSpiDeviceInit(const struct rxSpiConfig_s *rxSpiConfig);
uint8_t rxSpiTransferByte(uint8_t data);
uint8_t rxSpiWriteByte(uint8_t data);
uint8_t rxSpiWriteCommand(uint8_t command, uint8_t data);
uint8_t rxSpiWriteCommandMulti(uint8_t command, const uint8_t *data, uint8_t length);
uint8_t rxSpiReadCommand(uint8_t command, uint8_t commandData);
uint8_t rxSpiReadCommandMulti(uint8_t command, uint8_t commandData, uint8_t *retData, uint8_t length);

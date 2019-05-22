#pragma once

#include "pg/pg.h"

#include "rx/rx_spi.h"

typedef struct rxFrSkySpiConfig_s {
    uint8_t autoBind;
    uint8_t bindTxId[2];
    int8_t  bindOffset;
    uint8_t bindHopData[50];
    uint8_t rxNum;
    uint8_t useExternalAdc;
} rxFrSkySpiConfig_t;

PG_DECLARE(rxFrSkySpiConfig_t, rxFrSkySpiConfig);

bool frSkySpiInit(const rxSpiConfig_t *rxSpiConfig, rxRuntimeConfig_t *rxRuntimeConfig);
rx_spi_received_e frSkySpiDataReceived(uint8_t *packet);
void frSkySpiSetRcData(uint16_t *rcData, const uint8_t *payload);

void frSkySpiBind(void);

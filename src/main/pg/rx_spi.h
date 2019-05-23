#pragma once

#include "drivers/io_types.h"

#include "pg/pg.h"

typedef struct rxSpiConfig_s {
    // RX protocol
    uint8_t rx_spi_protocol;                // type of SPI RX protocol
                                            // nrf24: 0 = v202 250kbps. (Must be enabled by FEATURE_RX_NRF24 first.)
    uint32_t rx_spi_id;
    uint8_t rx_spi_rf_channel_count;

    // SPI Bus
    ioTag_t csnTag;
    uint8_t spibus;

} rxSpiConfig_t;

PG_DECLARE(rxSpiConfig_t, rxSpiConfig);

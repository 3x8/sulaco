#include "platform.h"

#ifdef USE_RX_SPI

#include "drivers/io.h"
#include "drivers/bus_spi.h"

#include "pg/pg.h"
#include "pg/pg_ids.h"
#include "pg/rx_spi.h"

#include "rx/rx_spi.h"

PG_REGISTER_WITH_RESET_FN(rxSpiConfig_t, rxSpiConfig, PG_RX_SPI_CONFIG, 0);

void pgResetFn_rxSpiConfig(rxSpiConfig_t *rxSpiConfig)
{
    rxSpiConfig->rx_spi_protocol = RX_SPI_DEFAULT_PROTOCOL;

    // Basic SPI
    rxSpiConfig->csnTag = IO_TAG(RX_NSS_PIN);
    rxSpiConfig->spibus = SPI_DEV_TO_CFG(spiDeviceByInstance(RX_SPI_INSTANCE));
}
#endif

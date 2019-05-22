#include "platform.h"

#ifdef USE_MAX7456

#include "pg/pg.h"
#include "pg/pg_ids.h"

#include "drivers/io.h"
#include "drivers/bus_spi.h"

#include "max7456.h"

PG_REGISTER_WITH_RESET_FN(max7456Config_t, max7456Config, PG_MAX7456_CONFIG, 0);

void pgResetFn_max7456Config(max7456Config_t *config)
{
    config->clockConfig = MAX7456_CLOCK_CONFIG_DEFAULT;
    config->csTag = IO_TAG(MAX7456_SPI_CS_PIN);
    config->spiDevice = SPI_DEV_TO_CFG(spiDeviceByInstance(MAX7456_SPI_INSTANCE));
}
#endif // USE_MAX7456

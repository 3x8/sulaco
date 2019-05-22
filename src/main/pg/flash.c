#include <stdbool.h>
#include <stdint.h>

#include "platform.h"

#ifdef USE_FLASHFS

#include "drivers/bus_spi.h"
#include "drivers/io.h"

#include "pg/pg.h"
#include "pg/pg_ids.h"

#include "flash.h"

PG_REGISTER_WITH_RESET_FN(flashConfig_t, flashConfig, PG_FLASH_CONFIG, 0);

void pgResetFn_flashConfig(flashConfig_t *flashConfig)
{
#ifdef FLASH_CS_PIN
    flashConfig->csTag = IO_TAG(FLASH_CS_PIN);
#else
    flashConfig->csTag = IO_TAG_NONE;
#endif
    flashConfig->spiDevice = SPI_DEV_TO_CFG(spiDeviceByInstance(FLASH_SPI_INSTANCE));
}
#endif

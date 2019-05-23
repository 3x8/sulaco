#include <stdbool.h>
#include <stdint.h>

#include "platform.h"

#ifdef USE_SDCARD

#include "pg/pg.h"
#include "pg/pg_ids.h"

#include "sdcard.h"
#include "drivers/bus_spi.h"
#include "drivers/io.h"
#include "drivers/dma.h"

PG_REGISTER_WITH_RESET_FN(sdcardConfig_t, sdcardConfig, PG_SDCARD_CONFIG, 0);

void pgResetFn_sdcardConfig(sdcardConfig_t *config)
{
    config->useDma = false;
#ifdef SDCARD_SPI_INSTANCE
    config->enabled = 1;
    config->device = spiDeviceByInstance(SDCARD_SPI_INSTANCE);
#elif defined(USE_SDCARD_SDIO)
    config->enabled = 1;
#else
    config->enabled = 0;
    config->device = 0;
#endif
#ifdef SDCARD_DETECT_PIN
    config->cardDetectTag = IO_TAG(SDCARD_DETECT_PIN);
#else
    config->cardDetectTag = IO_TAG_NONE;
#endif
#ifdef SDCARD_SPI_CS_PIN
    config->chipSelectTag = IO_TAG(SDCARD_SPI_CS_PIN);
#else
    config->chipSelectTag = IO_TAG_NONE;
#endif

#ifdef SDCARD_DETECT_INVERTED
    config->cardDetectInverted = 1;
#else
    config->cardDetectInverted = 0;
#endif

#if defined(SDCARD_DMA_STREAM_TX_FULL)
    config->dmaIdentifier = (uint8_t)dmaGetIdentifier(SDCARD_DMA_STREAM_TX_FULL);
#elif defined(SDCARD_DMA_CHANNEL_TX)
    config->dmaIdentifier = (uint8_t)dmaGetIdentifier(SDCARD_DMA_CHANNEL_TX);
#elif defined(SDIO_DMA)
    config->dmaIdentifier = (uint8_t)dmaGetIdentifier(SDIO_DMA);
    config->useDma = true;
#endif

#if defined(SDCARD_DMA_CHANNEL)
    config->dmaChannel = SDCARD_DMA_CHANNEL;
#endif
}
#endif

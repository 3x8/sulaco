#include <stdbool.h>
#include <stdint.h>

#include "platform.h"

#include "build/debug.h"

#ifdef USE_FLASH

#include "flash.h"
#include "flash_impl.h"
#include "flash_m25p16.h"
#include "flash_w25n01g.h"
#include "flash_w25m.h"
#include "drivers/bus_spi.h"
#include "drivers/io.h"
#include "drivers/time.h"

static busDevice_t busInstance;
static busDevice_t *busdev;

static flashDevice_t flashDevice;

// Read chip identification and send it to device detect

bool flashInit(const flashConfig_t *flashConfig)
{
    busdev = &busInstance;

    if (flashConfig->csTag) {
        busdev->busdev_u.spi.csnPin = IOGetByTag(flashConfig->csTag);
    } else {
        return false;
    }

    if (!IOIsFreeOrPreinit(busdev->busdev_u.spi.csnPin)) {
        return false;
    }

    busdev->bustype = BUSTYPE_SPI;

    SPI_TypeDef *instance = spiInstanceByDevice(SPI_CFG_TO_DEV(flashConfig->spiDevice));
    if (!instance) {
        return false;
    }

    spiBusSetInstance(busdev, instance);

    IOInit(busdev->busdev_u.spi.csnPin, OWNER_FLASH_CS, 0);
    IOConfigGPIO(busdev->busdev_u.spi.csnPin, SPI_IO_CS_CFG);
    IOHi(busdev->busdev_u.spi.csnPin);

#ifndef FLASH_SPI_SHARED
    //Maximum speed for standard READ command is 20mHz, other commands tolerate 25mHz
    //spiSetDivisor(busdev->busdev_u.spi.instance, SPI_CLOCK_FAST);
    spiSetDivisor(busdev->busdev_u.spi.instance, SPI_CLOCK_STANDARD*2);
#endif

    flashDevice.busdev = busdev;

#define SPIFLASH_INSTRUCTION_RDID 0x9F

    const uint8_t out[] = { SPIFLASH_INSTRUCTION_RDID, 0, 0, 0, 0 };

    delay(50); // short delay required after initialisation of SPI device instance.

    /*
     * Some newer chips require one dummy byte to be read; we can read
     * 4 bytes for these chips while retaining backward compatibility.
     */
    uint8_t in[5];
    in[1] = in[2] = 0;

    // Clearing the CS bit terminates the command early so we don't have to read the chip UID:
    spiBusTransfer(busdev, out, in, sizeof(out));

    // Manufacturer, memory type, and capacity
    uint32_t chipID = (in[1] << 16) | (in[2] << 8) | (in[3]);

#ifdef USE_FLASH_M25P16
    if (m25p16_detect(&flashDevice, chipID)) {
        return true;
    }
#endif

#ifdef USE_FLASH_W25M512
    if (w25m_detect(&flashDevice, chipID)) {
        return true;
    }
#endif

    // Newer chips
    chipID = (in[2] << 16) | (in[3] << 8) | (in[4]);

#ifdef USE_FLASH_W25N01G
    if (w25n01g_detect(&flashDevice, chipID)) {
        return true;
    }
#endif

#ifdef USE_FLASH_W25M02G
    if (w25m_detect(&flashDevice, chipID)) {
        return true;
    }
#endif

    spiPreinitCsByTag(flashConfig->csTag);

    return false;
}

#ifdef USE_FLASH_W25N01G
void flashResetInit(void){
    flashDevice.vTable->init(&flashDevice);
}
#endif

bool flashIsReady(void)
{
    return flashDevice.vTable->isReady(&flashDevice);
}

bool flashWaitForReady(uint32_t timeoutMillis)
{
    return flashDevice.vTable->waitForReady(&flashDevice, timeoutMillis);
}

void flashEraseSector(uint32_t address)
{
    flashDevice.vTable->eraseSector(&flashDevice, address);
}

void flashEraseCompletely(void)
{
    flashDevice.vTable->eraseCompletely(&flashDevice);
}

void flashPageProgramBegin(uint32_t address)
{
    flashDevice.vTable->pageProgramBegin(&flashDevice, address);
}

void flashPageProgramContinue(const uint8_t *data, int length)
{
    flashDevice.vTable->pageProgramContinue(&flashDevice, data, length);
}

void flashPageProgramFinish(void)
{
    flashDevice.vTable->pageProgramFinish(&flashDevice);
}

void flashPageProgram(uint32_t address, const uint8_t *data, int length)
{
    flashDevice.vTable->pageProgram(&flashDevice, address, data, length);
}

int flashReadBytes(uint32_t address, uint8_t *buffer, int length)
{
    return flashDevice.vTable->readBytes(&flashDevice, address, buffer, length);
}

void flashFlush(void)
{
    flashDevice.vTable->flush(&flashDevice);
}

static const flashGeometry_t noFlashGeometry = {
    .totalSize = 0,
};

const flashGeometry_t *flashGetGeometry(void)
{
    if (flashDevice.vTable && flashDevice.vTable->getGeometry) {
        return flashDevice.vTable->getGeometry(&flashDevice);
    }

    return &noFlashGeometry;
}
#endif // USE_FLASH

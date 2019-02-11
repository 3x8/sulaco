#include <stdbool.h>
#include <stdint.h>

#include "platform.h"

#include "build/debug.h"

#ifdef USE_FLASH_W25N01G

#include "flash.h"
#include "flash_impl.h"
#include "flash_w25n01g.h"
#include "drivers/bus_spi.h"
#include "drivers/io.h"
#include "drivers/time.h"

//debug
//#define FLASH_W25N01G_DPRINTF

#ifdef FLASH_W25N01G_DPRINTF
#include "common/printf.h"
#include "common/utils.h"
#include "io/serial.h"
serialPort_t *debugSerialPort = NULL;
#define DPRINTF_SERIAL_PORT SERIAL_PORT_USART3
#define DPRINTF(x) tfp_printf x
#else
#define DPRINTF(x)
#endif

// JEDEC ID
#define JEDEC_ID_WINBOND_W25N01GV    0xEFAA21
#define JEDEC_ID_WINBOND_W25M02GV    0xEFAB21

// device size parameters
#define W25N01G_PAGE_SIZE         2048
#define W25N01G_PAGES_PER_BLOCK   64
#define W25N01G_BLOCKS_PER_DIE    1024

// instructions
#define W25N01G_INSTRUCTION_RDID                      0x9F
#define W25N01G_INSTRUCTION_DEVICE_RESET              0xFF
#define W25N01G_INSTRUCTION_READ_STATUS_REG           0x05
#define W25N01G_INSTRUCTION_WRITE_STATUS_REG          0x01
#define W25N01G_INSTRUCTION_WRITE_ENABLE              0x06
#define W25N01G_INSTRUCTION_DIE_SELECT                0xC2
#define W25N01G_INSTRUCTION_BLOCK_ERASE               0xD8
#define W25N01G_INSTRUCTION_READ_BBM_LUT              0xA5
#define W25N01G_INSTRUCTION_BB_MANAGEMENT             0xA1
#define W25N01G_INSTRUCTION_PROGRAM_DATA_LOAD         0x02
#define W25N01G_INSTRUCTION_RANDOM_PROGRAM_DATA_LOAD  0x84
#define W25N01G_INSTRUCTION_PROGRAM_EXECUTE           0x10
#define W25N01G_INSTRUCTION_PAGE_DATA_READ            0x13
#define W25N01G_INSTRUCTION_READ_DATA                 0x03
#define W25N01G_INSTRUCTION_FAST_READ                 0x1B

// config/status register addresses
#define W25N01G_PROT_REG  0xA0
#define W25N01G_CONF_REG  0xB0
#define W25N01G_STAT_REG  0xC0

// bits in config/status register 2 (W25N01G_CONF_REG)
#define W25N01G_CONFIG_ECC_ENABLE         (1 << 4)
#define W25N01G_CONFIG_BUFFER_READ_MODE   (1 << 3)

// bits in config/status register 3 (W25N01G_STATREG)
#define W25N01G_STATUS_BBM_LUT_FULL       (1 << 6)
#define W25N01G_STATUS_FLAG_ECC_POS       4
#define W25N01G_STATUS_FLAG_ECC_MASK      ((1 << 5)|(1 << 4))
#define W25N01G_STATUS_FLAG_ECC(status)   (((status) & W25N01G_STATUS_FLAG_ECC_MASK) >> 4)
#define W25N01G_STATUS_PROGRAM_FAIL       (1 << 3)
#define W25N01G_STATUS_ERASE_FAIL         (1 << 2)
#define W25N01G_STATUS_FLAG_WRITE_ENABLED (1 << 1)
#define W25N01G_STATUS_FLAG_BUSY          (1 << 0)

// bits in LBA for BB LUT
#define W25N01G_BBLUT_STATUS_ENABLED (1 << 15)
#define W25N01G_BBLUT_STATUS_INVALID (1 << 14)
#define W25N01G_BBLUT_STATUS_MASK    (W25N01G_BBLUT_STATUS_ENABLED | W25N01G_BBLUT_STATUS_INVALID)

// defs and macros
#define W25N01G_LINEAR_TO_COLUMN(laddr) ((laddr) % W25N01G_PAGE_SIZE)
#define W25N01G_LINEAR_TO_PAGE(laddr)   ((laddr) / W25N01G_PAGE_SIZE)
#define W25N01G_LINEAR_TO_BLOCK(laddr)  (W25N01G_LINEAR_TO_PAGE(laddr) / W25N01G_PAGES_PER_BLOCK)
#define W25N01G_BLOCK_TO_PAGE(block)    ((block) * W25N01G_PAGES_PER_BLOCK)
#define W25N01G_BLOCK_TO_LINEAR(block)  (W25N01G_BLOCK_TO_PAGE(block) * W25N01G_PAGE_SIZE)

// BB replacement area
#define W25N01G_BB_MARKER_BLOCKS           1
#define W25N01G_BB_REPLACEMENT_BLOCKS      21
#define W25N01G_BB_REPLACEMENT_START_BLOCK (W25N01G_BLOCKS_PER_DIE - W25N01G_BB_REPLACEMENT_BLOCKS)
#define W25N01G_BB_MARKER_BLOCK            (W25N01G_BB_REPLACEMENT_START_BLOCK - W25N01G_BB_MARKER_BLOCKS)

// timeout values (2ms minimum to avoid 1 tick advance in consecutive calls to millis).
#define W25N01G_TIMEOUT_PAGE_READ_MS      2   // tREmax = 60us (ECC enabled)
#define W25N01G_TIMEOUT_PAGE_PROGRAM_MS   2   // tPPmax = 700us
#define W25N01G_TIMEOUT_BLOCK_ERASE_MS   15   // tBEmax = 10ms


static void w25n01g_disable(busDevice_t *bus) {
    IOHi(bus->busdev_u.spi.csnPin);
    __NOP();
}

static void w25n01g_enable(busDevice_t *bus){
    __NOP();
    IOLo(bus->busdev_u.spi.csnPin);
}

static void w25n01g_performOneByteCommand(busDevice_t *busdev, uint8_t command) {
    w25n01g_enable(busdev);
    spiTransferByte(busdev->busdev_u.spi.instance, command);
    w25n01g_disable(busdev);
}

static uint8_t w25n01g_readRegister(busDevice_t *busdev, uint8_t reg) {
    const uint8_t cmd[3] = { W25N01G_INSTRUCTION_READ_STATUS_REG, reg, 0 };
    uint8_t in[3];

    w25n01g_enable(busdev);
    spiTransfer(busdev->busdev_u.spi.instance, cmd, in, sizeof(cmd));
    w25n01g_disable(busdev);

    return (in[2]);
}

static void w25n01g_writeRegister(busDevice_t *busdev, uint8_t reg, uint8_t data) {
    const uint8_t cmd[3] = { W25N01G_INSTRUCTION_WRITE_STATUS_REG, reg, data };

    w25n01g_enable(busdev);
    spiTransfer(busdev->busdev_u.spi.instance, cmd, NULL, sizeof(cmd));
    w25n01g_disable(busdev);
}

static void w25n01g_deviceReset(busDevice_t *busdev) {
    w25n01g_performOneByteCommand(busdev, W25N01G_INSTRUCTION_DEVICE_RESET);

    // no protection, WP-E on
    w25n01g_writeRegister(busdev, W25N01G_PROT_REG, (0 << 3)|(0 << 2)|(1 << 1));

    // buffered read mode (BUF = 1), ECC enabled (ECC = 1)
    w25n01g_writeRegister(busdev, W25N01G_CONF_REG, W25N01G_CONFIG_ECC_ENABLE|W25N01G_CONFIG_BUFFER_READ_MODE);
}

bool w25n01g_isReady(flashDevice_t *fdevice) {
    uint8_t status = w25n01g_readRegister(fdevice->busdev, W25N01G_STAT_REG);

#ifdef FLASH_W25N01G_DPRINTF
    if (status & W25N01G_STATUS_PROGRAM_FAIL) {
        DPRINTF(("*** PROGRAM_FAIL\r\n"));
    }

    if (status & W25N01G_STATUS_ERASE_FAIL) {
        DPRINTF(("*** ERASE_FAIL\r\n"));
    }

    uint8_t eccCode;
    if ((eccCode = W25N01G_STATUS_FLAG_ECC(status))) {
        DPRINTF(("*** ECC %x\r\n", eccCode));
    }
#endif

    return ((status & W25N01G_STATUS_FLAG_BUSY) == 0);
}

bool w25n01g_waitForReady(flashDevice_t *fdevice, uint32_t timeoutMillis) {
    uint32_t time = millis();
    while (!w25n01g_isReady(fdevice)) {
        if (millis() - time > timeoutMillis) {
            DPRINTF(("*** TIMEOUT %d\r\n", timeoutMillis));
            return (false);
        }
    }

    return (true);
}

// the flash requires WRITE_ENABLE to be sent before commands that would cause a flash data change
static void w25n01g_writeEnable(flashDevice_t *fdevice) {
    w25n01g_performOneByteCommand(fdevice->busdev, W25N01G_INSTRUCTION_WRITE_ENABLE);
    fdevice->couldBeBusy = true;
}

const flashVTable_t w25n01g_vTable;
//read chip id and geometry  (into global `geometry`).
bool w25n01g_detect(flashDevice_t *fdevice, uint32_t chipID) {

#ifdef FLASH_W25N01G_DPRINTF
    debugSerialPort = openSerialPort(DPRINTF_SERIAL_PORT, FUNCTION_NONE, NULL, NULL, 115200, MODE_RXTX, 0);

    if (debugSerialPort) {
        setPrintfSerialPort(debugSerialPort);
        DPRINTF(("debug print init: OK\r\n"));
    }
#endif

    switch (chipID) {
    case JEDEC_ID_WINBOND_W25N01GV:
    case JEDEC_ID_WINBOND_W25M02GV: // XXX Treat this as 1G part atm, as stacked W25N01G is not tested at all (yet).
        fdevice->geometry.sectors = 1024;
        fdevice->geometry.pagesPerSector = 64;
        fdevice->geometry.pageSize = 2048;
        break;

    default:
        fdevice->geometry.sectors = 0;
        fdevice->geometry.pagesPerSector = 0;

        fdevice->geometry.sectorSize = 0;
        fdevice->geometry.totalSize = 0;
        return (false);
    }

    fdevice->geometry.flashType = FLASH_TYPE_NAND;
    fdevice->geometry.sectors -= W25N01G_BB_REPLACEMENT_BLOCKS;
    fdevice->geometry.sectorSize = fdevice->geometry.pagesPerSector * fdevice->geometry.pageSize;
    fdevice->geometry.totalSize = fdevice->geometry.sectorSize * fdevice->geometry.sectors;

    fdevice->vTable = &w25n01g_vTable;

    w25n01g_deviceReset(fdevice->busdev);

    return (true);
}

void w25n01g_eraseSector(flashDevice_t *fdevice, uint32_t address) {
    const uint8_t cmd[] = { W25N01G_INSTRUCTION_BLOCK_ERASE, 0, W25N01G_LINEAR_TO_PAGE(address) >> 8, W25N01G_LINEAR_TO_PAGE(address) & 0xff };

    w25n01g_waitForReady(fdevice, W25N01G_TIMEOUT_BLOCK_ERASE_MS);

    w25n01g_writeEnable(fdevice);

    w25n01g_enable(fdevice->busdev);
    spiTransfer(fdevice->busdev->busdev_u.spi.instance, cmd, NULL, sizeof(cmd));
    w25n01g_disable(fdevice->busdev);
}

void w25n01g_eraseCompletely(flashDevice_t *fdevice) {
#ifdef FLASH_W25N01G_DPRINTF
    uint32_t beginTime = micros();
#endif

    //debug (lost logging data)
    w25n01g_deviceReset(fdevice->busdev);

    for (uint32_t block = 0; block < fdevice->geometry.sectors; block++) {
        w25n01g_eraseSector(fdevice, W25N01G_BLOCK_TO_LINEAR(block));
    }

    DPRINTF(("w25n01g_eraseCompletely runtime(%d)us\r\n", (micros() - beginTime) ));
}

static void w25n01g_programDataLoad(flashDevice_t *fdevice, uint16_t columnAddress, const uint8_t *data, int length) {
#ifdef FLASH_W25N01G_DPRINTF
    uint32_t beginTime = micros();
#endif
    const uint8_t cmd[] = { W25N01G_INSTRUCTION_PROGRAM_DATA_LOAD, columnAddress >> 8, columnAddress& 0xff };

    w25n01g_waitForReady(fdevice, W25N01G_TIMEOUT_PAGE_PROGRAM_MS);

    w25n01g_enable(fdevice->busdev);
    spiTransfer(fdevice->busdev->busdev_u.spi.instance, cmd, NULL, sizeof(cmd));
    spiTransfer(fdevice->busdev->busdev_u.spi.instance, data, NULL, length);
    w25n01g_disable(fdevice->busdev);

    DPRINTF(("w25n01g_programDataLoad runtime(%d)us\r\n", (micros() - beginTime) ));
}

static void w25n01g_randomProgramDataLoad(flashDevice_t *fdevice, uint16_t columnAddress, const uint8_t *data, int length) {
#ifdef FLASH_W25N01G_DPRINTF
    uint32_t beginTime = micros();
#endif
    const uint8_t cmd[] = { W25N01G_INSTRUCTION_RANDOM_PROGRAM_DATA_LOAD, columnAddress >> 8, columnAddress& 0xff };

    w25n01g_waitForReady(fdevice, W25N01G_TIMEOUT_PAGE_PROGRAM_MS);

    w25n01g_enable(fdevice->busdev);
    spiTransfer(fdevice->busdev->busdev_u.spi.instance, cmd, NULL, sizeof(cmd));
    spiTransfer(fdevice->busdev->busdev_u.spi.instance, data, NULL, length);
    w25n01g_disable(fdevice->busdev);

    DPRINTF(("w25n01g_randomProgramDataLoad runtime(%d)us\r\n", (micros() - beginTime) ));
}

static void w25n01g_programExecute(flashDevice_t *fdevice, uint32_t pageAddress) {
#ifdef FLASH_W25N01G_DPRINTF
    uint32_t beginTime = micros();
#endif
    const uint8_t cmd[] = { W25N01G_INSTRUCTION_PROGRAM_EXECUTE, 0, pageAddress >> 8, pageAddress & 0xff };

    w25n01g_waitForReady(fdevice, W25N01G_TIMEOUT_PAGE_PROGRAM_MS);

    w25n01g_enable(fdevice->busdev);
    spiTransfer(fdevice->busdev->busdev_u.spi.instance, cmd, NULL, sizeof(cmd));
    w25n01g_disable(fdevice->busdev);

    DPRINTF(("w25n01g_programExecute runtime(%d)us\r\n", (micros() - beginTime) ));
}


static uint32_t programStartAddress;
static uint32_t programLoadAddress;
bool bufferDirty = false;
bool isProgramming = false;

//#define PAGEPROG_DPRINTF(x) DPRINTF(x)
#define PAGEPROG_DPRINTF(x)

void w25n01g_pageProgramBegin(flashDevice_t *fdevice, uint32_t address) {
    PAGEPROG_DPRINTF(("pageProgramBegin: address 0x%x\r\n", address));

    if (bufferDirty) {
        if (address != programLoadAddress) {
            PAGEPROG_DPRINTF(("    Buffer dirty and address != programLoadAddress (0x%x), flushing\r\n", programLoadAddress));
            PAGEPROG_DPRINTF(("    Wait for ready\r\n"));
            w25n01g_waitForReady(fdevice, W25N01G_TIMEOUT_PAGE_PROGRAM_MS);

            isProgramming = false;

            PAGEPROG_DPRINTF(("    Write enable\r\n"));
            w25n01g_writeEnable(fdevice);

            PAGEPROG_DPRINTF(("    PROGRAM_EXECUTE PA 0x%x\r\n", W25N01G_LINEAR_TO_PAGE(programStartAddress)));
            w25n01g_programExecute(fdevice, W25N01G_LINEAR_TO_PAGE(programStartAddress));

            bufferDirty = false;
            isProgramming = true;
        } else {
            PAGEPROG_DPRINTF(("    Continuation\r\n"));
        }
    } else {
        PAGEPROG_DPRINTF(("    Fresh page\r\n"));
        programStartAddress = programLoadAddress = address;
    }
}

void w25n01g_pageProgramContinue(flashDevice_t *fdevice, const uint8_t *data, int length) {
    PAGEPROG_DPRINTF(("pageProgramContinue: length 0x%x (programLoadAddress 0x%x)\r\n", length, programLoadAddress));

    // Check for page boundary overrun
    if (W25N01G_LINEAR_TO_PAGE(programLoadAddress + length - 1) != W25N01G_LINEAR_TO_PAGE(programStartAddress)) {
        PAGEPROG_DPRINTF(("    **** PAGE BOUNDARY OVERRUN **** (page 0x%x)\r\n", W25N01G_LINEAR_TO_PAGE(programLoadAddress)));
    }

    PAGEPROG_DPRINTF(("    Wait for ready\r\n"));
    w25n01g_waitForReady(fdevice, W25N01G_TIMEOUT_PAGE_PROGRAM_MS);

    PAGEPROG_DPRINTF(("    Write enable\r\n"));
    w25n01g_writeEnable(fdevice);

    isProgramming = false;

    if (!bufferDirty) {
        PAGEPROG_DPRINTF(("    DATA_LOAD CA 0x%x length 0x%x\r\n", W25N01G_LINEAR_TO_COLUMN(programLoadAddress), length));
        w25n01g_programDataLoad(fdevice, W25N01G_LINEAR_TO_COLUMN(programLoadAddress), data, length);
    } else {
        PAGEPROG_DPRINTF(("    RANDOM_DATA_LOAD CA 0x%x length 0x%x\r\n", W25N01G_LINEAR_TO_COLUMN(programLoadAddress), length));
        w25n01g_randomProgramDataLoad(fdevice, W25N01G_LINEAR_TO_COLUMN(programLoadAddress), data, length);
    }

    bufferDirty = true;
    programLoadAddress += length;
}

void w25n01g_pageProgramFinish(flashDevice_t *fdevice) {
    PAGEPROG_DPRINTF(("pageProgramFinish: (loaded 0x%x bytes)\r\n", programLoadAddress - programStartAddress));

    if (bufferDirty && W25N01G_LINEAR_TO_COLUMN(programLoadAddress) == 0) {
        PAGEPROG_DPRINTF(("    PROGRAM_EXECUTE PA 0x%x\r\n", W25N01G_LINEAR_TO_PAGE(programStartAddress)));
        w25n01g_programExecute(fdevice, W25N01G_LINEAR_TO_PAGE(programStartAddress));

        bufferDirty = false;
        isProgramming = true;

        programStartAddress = programLoadAddress;
    } else {
        PAGEPROG_DPRINTF(("    Ignoring\r\n"));
    }
}


void w25n01g_pageProgram(flashDevice_t *fdevice, uint32_t address, const uint8_t *data, int length) {
    w25n01g_pageProgramBegin(fdevice, address);
    w25n01g_pageProgramContinue(fdevice, data, length);
    w25n01g_pageProgramFinish(fdevice);
}

void w25n01g_flush(flashDevice_t *fdevice) {
    PAGEPROG_DPRINTF(("close:\r\n"));

    if (bufferDirty) {
        PAGEPROG_DPRINTF(("    Buffer is partially loaded (0x%x bytes)\r\n", programLoadAddress - programStartAddress));
        PAGEPROG_DPRINTF(("    PROGRAM_EXECUTE PA 0x%x\r\n", W25N01G_LINEAR_TO_PAGE(programStartAddress)));

        w25n01g_programExecute(fdevice, W25N01G_LINEAR_TO_PAGE(programStartAddress));

        bufferDirty = false;
        isProgramming = true;
    } else {
        PAGEPROG_DPRINTF(("    Buffer is clean\r\n"));
        isProgramming = false;
    }
}

void w25n01g_addError(uint32_t address, uint8_t code) {
    UNUSED(address);
    UNUSED(code);
    DPRINTF(("addError: PA %x BA %x code %d\r\n", W25N01G_LINEAR_TO_PAGE(address), W25N01G_LINEAR_TO_BLOCK(address), code));
}

//#define READBYTES_DPRINTF DPRINTF
#define READBYTES_DPRINTF(x)

int w25n01g_readBytes(flashDevice_t *fdevice, uint32_t address, uint8_t *buffer, int length) {
    static uint32_t currentPage = UINT32_MAX;
    uint8_t cmd[4];

    READBYTES_DPRINTF(("readBytes: address 0x%x length %d\r\n", address, length));

    uint32_t targetPage = W25N01G_LINEAR_TO_PAGE(address);

    if (currentPage != targetPage) {
        READBYTES_DPRINTF(("readBytes: PAGE_DATA_READ page 0x%x\r\n", targetPage));

        cmd[0] = W25N01G_INSTRUCTION_PAGE_DATA_READ;
        cmd[1] = 0;
        cmd[2] = targetPage >> 8;
        cmd[3] = targetPage;

        if (!w25n01g_waitForReady(fdevice, W25N01G_TIMEOUT_PAGE_READ_MS)) {
            return (0);
        }

        currentPage = UINT32_MAX;

        w25n01g_enable(fdevice->busdev);
        spiTransfer(fdevice->busdev->busdev_u.spi.instance, cmd, NULL, 4);
        w25n01g_disable(fdevice->busdev);

        if (!w25n01g_waitForReady(fdevice, W25N01G_TIMEOUT_PAGE_READ_MS)) {
            return (0);
        }

        currentPage = targetPage;
    }

    uint16_t column = W25N01G_LINEAR_TO_COLUMN(address);
    uint16_t transferLength;

    if (length > W25N01G_PAGE_SIZE - column) {
        transferLength = W25N01G_PAGE_SIZE - column;
    } else {
        transferLength = length;
    }

    cmd[0] = W25N01G_INSTRUCTION_READ_DATA;
    cmd[1] = column >> 8;
    cmd[2] = column;
    cmd[3] = 0;

    READBYTES_DPRINTF(("readBytes: READ_DATA column 0x%x transferLength 0x%x\r\n", column, transferLength));

    w25n01g_enable(fdevice->busdev);
    spiTransfer(fdevice->busdev->busdev_u.spi.instance, cmd, NULL, 4);
    spiTransfer(fdevice->busdev->busdev_u.spi.instance, NULL, buffer, length);
    w25n01g_disable(fdevice->busdev);

    // Check ECC
    uint8_t statReg = w25n01g_readRegister(fdevice->busdev, W25N01G_STAT_REG);
    uint8_t eccCode = W25N01G_STATUS_FLAG_ECC(statReg);

    switch (eccCode) {
    case 0: // Successful read, no ECC correction
        break;
    case 1: // Successful read with ECC correction
    case 2: // Uncorrectable ECC in a single page
    case 3: // Uncorrectable ECC in multiple pages
        w25n01g_addError(address, eccCode);
        w25n01g_deviceReset(fdevice->busdev);
        break;
    }

    READBYTES_DPRINTF(("readBytes: transfered 0x%x bytes\r\n", transferLength));

    return (transferLength);
}

int w25n01g_readExtensionBytes(flashDevice_t *fdevice, uint32_t address, uint8_t *buffer, int length) {
    uint8_t cmd[4];

    cmd[0] = W25N01G_INSTRUCTION_PAGE_DATA_READ;
    cmd[1] = 0;
    cmd[2] = W25N01G_LINEAR_TO_PAGE(address) >> 8;
    cmd[3] = W25N01G_LINEAR_TO_PAGE(address);

    w25n01g_enable(fdevice->busdev);
    spiTransfer(fdevice->busdev->busdev_u.spi.instance, cmd, NULL, 4);
    w25n01g_disable(fdevice->busdev);

    if (!w25n01g_waitForReady(fdevice, W25N01G_TIMEOUT_PAGE_READ_MS)) {
        return (0);
    }

    cmd[0] = W25N01G_INSTRUCTION_READ_DATA;
    cmd[1] = 0;
    cmd[2] = (2048 >> 8) & 0xff;
    cmd[3] = 2048 & 0xff;

    w25n01g_enable(fdevice->busdev);
    spiTransfer(fdevice->busdev->busdev_u.spi.instance, cmd, NULL, 4);
    spiTransfer(fdevice->busdev->busdev_u.spi.instance, NULL, buffer, length);
    w25n01g_disable(fdevice->busdev);

    return (length);
}

const flashGeometry_t* w25n01g_getGeometry(flashDevice_t *fdevice) {
    return (&fdevice->geometry);
}

void w25n01g_init(flashDevice_t *fdevice) {
    w25n01g_deviceReset(fdevice->busdev);
}

const flashVTable_t w25n01g_vTable = {
    .init = w25n01g_init,
    .isReady = w25n01g_isReady,
    .waitForReady = w25n01g_waitForReady,
    .eraseSector = w25n01g_eraseSector,
    .eraseCompletely = w25n01g_eraseCompletely,
    .pageProgramBegin = w25n01g_pageProgramBegin,
    .pageProgramContinue = w25n01g_pageProgramContinue,
    .pageProgramFinish = w25n01g_pageProgramFinish,
    .pageProgram = w25n01g_pageProgram,
    .flush = w25n01g_flush,
    .readBytes = w25n01g_readBytes,
    .getGeometry = w25n01g_getGeometry,
};

void w25n01g_readBBLUT(flashDevice_t *fdevice, bblut_t *bblut, int lutsize) {
    uint8_t cmd[4];
    uint8_t in[4];

    cmd[0] = W25N01G_INSTRUCTION_READ_BBM_LUT;
    cmd[1] = 0;

    w25n01g_enable(fdevice->busdev);

    spiTransfer(fdevice->busdev->busdev_u.spi.instance, cmd, NULL, 2);

    for (int i = 0 ; i < lutsize ; i++) {
        spiTransfer(fdevice->busdev->busdev_u.spi.instance, NULL, in, 4);
        bblut[i].pba = (in[0] << 16)|in[1];
        bblut[i].lba = (in[2] << 16)|in[3];
    }

    w25n01g_disable(fdevice->busdev);
}

void w25n01g_writeBBLUT(flashDevice_t *fdevice, uint16_t lba, uint16_t pba) {
    uint8_t cmd[5] = { W25N01G_INSTRUCTION_BB_MANAGEMENT, lba >> 8, lba, pba >> 8, pba };

    w25n01g_enable(fdevice->busdev);
    spiTransfer(fdevice->busdev->busdev_u.spi.instance, cmd, NULL, sizeof(cmd));
    w25n01g_disable(fdevice->busdev);

    w25n01g_waitForReady(fdevice, W25N01G_TIMEOUT_PAGE_PROGRAM_MS);
}

#endif

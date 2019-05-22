#include <stdbool.h>
#include <stdint.h>

#include "platform.h"

#include "common/utils.h"

#include "drivers/display.h"
#include "drivers/display_ug2864hsweg01.h"

static displayPort_t oledDisplayPort;

static int oledGrab(displayPort_t *displayPort)
{
    UNUSED(displayPort);
    return 0;
}

static int oledRelease(displayPort_t *displayPort)
{
    UNUSED(displayPort);
    return 0;
}

static int oledClearScreen(displayPort_t *displayPort)
{
    i2c_OLED_clear_display_quick(displayPort->device);
    return 0;
}

static int oledDrawScreen(displayPort_t *displayPort)
{
    UNUSED(displayPort);
    return 0;
}

static int oledScreenSize(const displayPort_t *displayPort)
{
    return displayPort->rows * displayPort->cols;
}

static int oledWriteString(displayPort_t *displayPort, uint8_t x, uint8_t y, const char *s)
{
    i2c_OLED_set_xy(displayPort->device, x, y);
    i2c_OLED_send_string(displayPort->device, s);
    return 0;
}

static int oledWriteChar(displayPort_t *displayPort, uint8_t x, uint8_t y, uint8_t c)
{
    i2c_OLED_set_xy(displayPort->device, x, y);
    i2c_OLED_send_char(displayPort->device, c);
    return 0;
}

static bool oledIsTransferInProgress(const displayPort_t *displayPort)
{
    UNUSED(displayPort);
    return false;
}

static bool oledIsSynced(const displayPort_t *displayPort)
{
    UNUSED(displayPort);
    return true;
}

static int oledHeartbeat(displayPort_t *displayPort)
{
    UNUSED(displayPort);
    return 0;
}

static void oledResync(displayPort_t *displayPort)
{
    UNUSED(displayPort);
}

static uint32_t oledTxBytesFree(const displayPort_t *displayPort)
{
    UNUSED(displayPort);
    return UINT32_MAX;
}

static const displayPortVTable_t oledVTable = {
    .grab = oledGrab,
    .release = oledRelease,
    .clearScreen = oledClearScreen,
    .drawScreen = oledDrawScreen,
    .screenSize = oledScreenSize,
    .writeString = oledWriteString,
    .writeChar = oledWriteChar,
    .isTransferInProgress = oledIsTransferInProgress,
    .heartbeat = oledHeartbeat,
    .resync = oledResync,
    .isSynced = oledIsSynced,
    .txBytesFree = oledTxBytesFree
};

displayPort_t *displayPortOledInit(void *device)
{
    oledDisplayPort.device = device;
    displayInit(&oledDisplayPort, &oledVTable);
    oledDisplayPort.rows = SCREEN_CHARACTER_ROW_COUNT;
    oledDisplayPort.cols = SCREEN_CHARACTER_COLUMN_COUNT;
    return &oledDisplayPort;
}

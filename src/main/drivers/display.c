#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "platform.h"

#include "common/utils.h"

#include "display.h"

void displayClearScreen(displayPort_t *instance)
{
    instance->vTable->clearScreen(instance);
    instance->cleared = true;
    instance->cursorRow = -1;
}

void displayDrawScreen(displayPort_t *instance)
{
    instance->vTable->drawScreen(instance);
}

int displayScreenSize(const displayPort_t *instance)
{
    return instance->vTable->screenSize(instance);
}

void displayGrab(displayPort_t *instance)
{
    instance->vTable->grab(instance);
    instance->vTable->clearScreen(instance);
    ++instance->grabCount;
}

void displayRelease(displayPort_t *instance)
{
    instance->vTable->release(instance);
    --instance->grabCount;
}

void displayReleaseAll(displayPort_t *instance)
{
    instance->vTable->release(instance);
    instance->grabCount = 0;
}

bool displayIsGrabbed(const displayPort_t *instance)
{
    // can be called before initialised
    return (instance && instance->grabCount > 0);
}

void displaySetXY(displayPort_t *instance, uint8_t x, uint8_t y)
{
    instance->posX = x;
    instance->posY = y;
}

int displayWrite(displayPort_t *instance, uint8_t x, uint8_t y, const char *s)
{
    instance->posX = x + strlen(s);
    instance->posY = y;
    return instance->vTable->writeString(instance, x, y, s);
}

int displayWriteChar(displayPort_t *instance, uint8_t x, uint8_t y, uint8_t c)
{
    instance->posX = x + 1;
    instance->posY = y;
    return instance->vTable->writeChar(instance, x, y, c);
}

bool displayIsTransferInProgress(const displayPort_t *instance)
{
    return instance->vTable->isTransferInProgress(instance);
}

bool displayIsSynced(const displayPort_t *instance)
{
    return instance->vTable->isSynced(instance);
}

void displayHeartbeat(displayPort_t *instance)
{
    instance->vTable->heartbeat(instance);
}

void displayResync(displayPort_t *instance)
{
    instance->vTable->resync(instance);
}

uint16_t displayTxBytesFree(const displayPort_t *instance)
{
    return instance->vTable->txBytesFree(instance);
}

void displayInit(displayPort_t *instance, const displayPortVTable_t *vTable)
{
    instance->vTable = vTable;
    instance->vTable->clearScreen(instance);
    instance->cleared = true;
    instance->grabCount = 0;
    instance->cursorRow = -1;
}

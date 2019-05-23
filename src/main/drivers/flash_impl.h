#pragma once

#include "drivers/bus.h"

struct flashVTable_s;

typedef struct flashDevice_s {
    busDevice_t *busdev;
    const struct flashVTable_s *vTable;
    flashGeometry_t geometry;
    uint32_t currentWriteAddress;
    bool isLargeFlash;
    // Whether we've performed an action that could have made the device busy
    // for writes. This allows us to avoid polling for writable status
    // when it is definitely ready already.
    bool couldBeBusy;
} flashDevice_t;

typedef struct flashVTable_s {
#ifdef USE_FLASH_W25N01G
    void (*init)(flashDevice_t *fdevice);
#endif
    bool (*isReady)(flashDevice_t *fdevice);
    bool (*waitForReady)(flashDevice_t *fdevice, uint32_t timeoutMillis);
    void (*eraseSector)(flashDevice_t *fdevice, uint32_t address);
    void (*eraseCompletely)(flashDevice_t *fdevice);
    void (*pageProgramBegin)(flashDevice_t *fdevice, uint32_t address);
    void (*pageProgramContinue)(flashDevice_t *fdevice, const uint8_t *data, int length);
    void (*pageProgramFinish)(flashDevice_t *fdevice);
    void (*pageProgram)(flashDevice_t *fdevice, uint32_t address, const uint8_t *data, int length);
    void (*flush)(flashDevice_t *fdevice);
    int (*readBytes)(flashDevice_t *fdevice, uint32_t address, uint8_t *buffer, int length);
    const flashGeometry_t *(*getGeometry)(flashDevice_t *fdevice);
} flashVTable_t;

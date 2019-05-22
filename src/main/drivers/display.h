#pragma once

struct displayPortVTable_s;

typedef struct displayPort_s {
    const struct displayPortVTable_s *vTable;
    void *device;
    uint8_t rows;
    uint8_t cols;
    uint8_t posX;
    uint8_t posY;

    // CMS state
    bool cleared;
    int8_t cursorRow;
    int8_t grabCount;
} displayPort_t;

// displayPort_t is used as a parameter group in 'displayport_msp.h' and 'displayport_max7456`.h'. Treat accordingly!

typedef struct displayPortVTable_s {
    int (*grab)(displayPort_t *displayPort);
    int (*release)(displayPort_t *displayPort);
    int (*clearScreen)(displayPort_t *displayPort);
    int (*drawScreen)(displayPort_t *displayPort);
    int (*screenSize)(const displayPort_t *displayPort);
    int (*writeString)(displayPort_t *displayPort, uint8_t x, uint8_t y, const char *text);
    int (*writeChar)(displayPort_t *displayPort, uint8_t x, uint8_t y, uint8_t c);
    bool (*isTransferInProgress)(const displayPort_t *displayPort);
    int (*heartbeat)(displayPort_t *displayPort);
    void (*resync)(displayPort_t *displayPort);
    bool (*isSynced)(const displayPort_t *displayPort);
    uint32_t (*txBytesFree)(const displayPort_t *displayPort);
} displayPortVTable_t;

typedef struct displayPortProfile_s {
    int8_t colAdjust;
    int8_t rowAdjust;
    bool invert;
    uint8_t blackBrightness;
    uint8_t whiteBrightness;
} displayPortProfile_t;

// Note: displayPortProfile_t used as a parameter group for CMS over CRSF (io/displayport_crsf)

void displayGrab(displayPort_t *instance);
void displayRelease(displayPort_t *instance);
void displayReleaseAll(displayPort_t *instance);
bool displayIsGrabbed(const displayPort_t *instance);
void displayClearScreen(displayPort_t *instance);
void displayDrawScreen(displayPort_t *instance);
int displayScreenSize(const displayPort_t *instance);
void displaySetXY(displayPort_t *instance, uint8_t x, uint8_t y);
int displayWrite(displayPort_t *instance, uint8_t x, uint8_t y, const char *s);
int displayWriteChar(displayPort_t *instance, uint8_t x, uint8_t y, uint8_t c);
bool displayIsTransferInProgress(const displayPort_t *instance);
void displayHeartbeat(displayPort_t *instance);
void displayResync(displayPort_t *instance);
bool displayIsSynced(const displayPort_t *instance);
uint16_t displayTxBytesFree(const displayPort_t *instance);
void displayInit(displayPort_t *instance, const displayPortVTable_t *vTable);

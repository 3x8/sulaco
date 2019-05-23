#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "pg/sdcard.h"

typedef struct sdcardMetadata_s {
    uint32_t numBlocks; /* Card capacity in 512-byte blocks*/
    uint16_t oemID;
    uint8_t manufacturerID;

    char productName[5];

    uint32_t productSerial;
    uint8_t productRevisionMajor;
    uint8_t productRevisionMinor;

    uint16_t productionYear;
    uint8_t productionMonth;
} sdcardMetadata_t;

typedef enum {
    SDCARD_BLOCK_OPERATION_READ,
    SDCARD_BLOCK_OPERATION_WRITE,
    SDCARD_BLOCK_OPERATION_ERASE
} sdcardBlockOperation_e;

typedef enum {
    SDCARD_OPERATION_IN_PROGRESS,
    SDCARD_OPERATION_BUSY,
    SDCARD_OPERATION_SUCCESS,
    SDCARD_OPERATION_FAILURE
} sdcardOperationStatus_e;

typedef void(*sdcard_operationCompleteCallback_c)(sdcardBlockOperation_e operation, uint32_t blockIndex, uint8_t *buffer, uint32_t callbackData);

typedef void(*sdcard_profilerCallback_c)(sdcardBlockOperation_e operation, uint32_t blockIndex, uint32_t duration);

void sdcard_init(const sdcardConfig_t *config);

bool sdcard_readBlock(uint32_t blockIndex, uint8_t *buffer, sdcard_operationCompleteCallback_c callback, uint32_t callbackData);

sdcardOperationStatus_e sdcard_beginWriteBlocks(uint32_t blockIndex, uint32_t blockCount);
sdcardOperationStatus_e sdcard_writeBlock(uint32_t blockIndex, uint8_t *buffer, sdcard_operationCompleteCallback_c callback, uint32_t callbackData);

void sdcardInsertionDetectDeinit(void);
void sdcardInsertionDetectInit(void);

bool sdcard_isInserted(void);
bool sdcard_isInitialized(void);
bool sdcard_isFunctional(void);

bool sdcard_poll(void);
const sdcardMetadata_t* sdcard_getMetadata(void);

void sdcard_setProfilerCallback(sdcard_profilerCallback_c callback);

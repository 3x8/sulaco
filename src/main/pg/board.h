#pragma once

#include "pg/pg.h"

#define MAX_MANUFACTURER_ID_LENGTH 4
#define MAX_BOARD_NAME_LENGTH 20
#define SIGNATURE_LENGTH 32

// Warning: This configuration is meant to be applied when loading the initial
// configuration for a generic board, and stay fixed after this, to enable
// identification of the hardware that this is running on.
// Do not modify this parameter group directly, use 'fc/board_info.h' instead.

typedef struct boardConfig_s {
    uint8_t signature[SIGNATURE_LENGTH];
    char manufacturerId[MAX_MANUFACTURER_ID_LENGTH + 1];
    char boardName[MAX_BOARD_NAME_LENGTH + 1];
    uint8_t boardInformationSet;
    uint8_t signatureSet;
} boardConfig_t;

PG_DECLARE(boardConfig_t, boardConfig);

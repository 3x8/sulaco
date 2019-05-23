#include <stdbool.h>
#include <string.h>

#include "platform.h"

#if defined(USE_BOARD_INFO)
#include "build/version.h"

#include "fc/board_info.h"

#include "pg/pg.h"
#include "pg/pg_ids.h"

#include "board.h"

PG_REGISTER_WITH_RESET_FN(boardConfig_t, boardConfig, PG_BOARD_CONFIG, 0);

void pgResetFn_boardConfig(boardConfig_t *boardConfig)
{
    if (boardInformationIsSet()) {
        strncpy(boardConfig->manufacturerId, getManufacturerId(), MAX_MANUFACTURER_ID_LENGTH);
        strncpy(boardConfig->boardName, getBoardName(), MAX_BOARD_NAME_LENGTH);
        boardConfig->boardInformationSet = true;
    } else {
#if !defined(GENERIC_TARGET)
        strncpy(boardConfig->boardName, targetName, MAX_BOARD_NAME_LENGTH);

#if defined(TARGET_MANUFACTURER_IDENTIFIER)
        strncpy(boardConfig->manufacturerId, TARGET_MANUFACTURER_IDENTIFIER, MAX_MANUFACTURER_ID_LENGTH);
#endif
        boardConfig->boardInformationSet = true;
#else
        boardConfig->boardInformationSet = false;
#endif // GENERIC_TARGET
    }

#if defined(USE_SIGNATURE)
    if (signatureIsSet()) {
        memcpy(boardConfig->signature, getSignature(), SIGNATURE_LENGTH);
        boardConfig->signatureSet = true;
    } else {
        boardConfig->signatureSet = false;
    }
#endif
}
#endif // USE_BOARD_INFO:

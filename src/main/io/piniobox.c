#include <stdint.h>

#include "platform.h"

#ifdef USE_PINIOBOX

#include "build/debug.h"

#include "common/utils.h"
#include "common/time.h"

#include "interface/msp_box.h"

#include "pg/pinio.h"
#include "pg/piniobox.h"

#include "piniobox.h"

typedef struct pinioBoxRuntimeConfig_s {
    uint8_t boxId[PINIO_COUNT];
} pinioBoxRuntimeConfig_t;

static pinioBoxRuntimeConfig_t pinioBoxRuntimeConfig;

void pinioBoxInit(const pinioBoxConfig_t *pinioBoxConfig)
{
    // Convert permanentId to boxId_e

    for (int i = 0; i < PINIO_COUNT; i++) {
        const box_t *box = findBoxByPermanentId(pinioBoxConfig->permanentId[i]);

        pinioBoxRuntimeConfig.boxId[i] = box ? box->boxId : BOXID_NONE;
    }
}

void pinioBoxUpdate(timeUs_t currentTimeUs)
{
    UNUSED(currentTimeUs);

    for (int i = 0; i < PINIO_COUNT; i++) {
        if (pinioBoxRuntimeConfig.boxId[i] != BOXID_NONE) {
            pinioSet(i, getBoxIdState(pinioBoxRuntimeConfig.boxId[i]));
        }
    }
}

#endif

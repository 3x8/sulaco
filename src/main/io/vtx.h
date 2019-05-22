#pragma once

#include <stdint.h>

#include "platform.h"
#include "common/time.h"
#include "pg/pg.h"

typedef struct vtxSettingsConfig_s {
    uint8_t band;           // 1=A, 2=B, 3=E, 4=F(Airwaves/Fatshark), 5=Raceband
    uint8_t channel;        // 1-8
    uint8_t power;          // 0 = lowest
    uint16_t freq;          // sets freq in MHz if band=0
    uint16_t pitModeFreq;   // sets out-of-range pitmode frequency
    uint8_t lowPowerDisarm; // min power while disarmed
} vtxSettingsConfig_t;

PG_DECLARE(vtxSettingsConfig_t, vtxSettingsConfig);

void vtxInit(void);
void vtxUpdate(timeUs_t currentTimeUs);

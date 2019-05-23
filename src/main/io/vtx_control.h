#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "platform.h"

#include "pg/pg.h"
#include "fc/rc_modes.h"

#define MAX_CHANNEL_ACTIVATION_CONDITION_COUNT  10

typedef struct vtxChannelActivationCondition_s {
    uint8_t auxChannelIndex;
    uint8_t band;
    uint8_t channel;
    channelRange_t range;
} vtxChannelActivationCondition_t;

typedef struct vtxConfig_s {
    vtxChannelActivationCondition_t vtxChannelActivationConditions[MAX_CHANNEL_ACTIVATION_CONDITION_COUNT];
    uint8_t halfDuplex;
} vtxConfig_t;

PG_DECLARE(vtxConfig_t, vtxConfig);

void vtxControlInit(void);
void vtxControlInputPoll(void);

void vtxIncrementBand(void);
void vtxDecrementBand(void);
void vtxIncrementChannel(void);
void vtxDecrementChannel(void);

void vtxCyclePower(const uint8_t powerStep);
void vtxCycleBandOrChannel(const uint8_t bandStep, const uint8_t channelStep);

void vtxUpdateActivatedChannel(void);

void handleVTXControlButton(void);

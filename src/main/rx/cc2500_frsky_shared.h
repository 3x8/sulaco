#pragma once

#include "rx/rx_spi.h"

#define MAX_MISSING_PKT 100

#define DEBUG_DATA_ERROR_COUNT 0
#define DEBUG_DATA_MISSING_PACKETS 1
#define DEBUG_DATA_BAD_FRAME 2


#define SYNC_DELAY_MAX 9000

#define MAX_MISSING_PKT 100

enum {
    STATE_INIT = 0,
    STATE_BIND,
    STATE_BIND_TUNING,
    STATE_BIND_BINDING1,
    STATE_BIND_BINDING2,
    STATE_BIND_COMPLETE,
    STATE_STARTING,
    STATE_UPDATE,
    STATE_DATA,
    STATE_TELEMETRY,
    STATE_RESUME,
};

extern uint8_t listLength;
extern uint32_t missingPackets;
extern timeDelta_t timeoutUs;
extern int16_t rssiDbm;

extern IO_t gdoPin;

void setRssiDbm(uint8_t value);

void TxEnable(void);
void TxDisable(void);

void LedOn(void);
void LedOff(void);

void switchAntennae(void);

void initialiseData(uint8_t adr);

bool checkBindRequested(bool reset);

void nextChannel(uint8_t skip);

#pragma once

#include "common/time.h"
#include "pg/pg.h"

typedef struct transponderConfig_s {
    transponderProvider_e provider;
    uint8_t reserved;
    uint8_t data[9];
    ioTag_t ioTag;
} transponderConfig_t;

typedef struct transponderRequirement_s {
    uint8_t provider; // See transponderProvider_e
    uint8_t dataLength;
    uint16_t transmitDelay;
    uint16_t transmitJitter;
} transponderRequirement_t;

PG_DECLARE(transponderConfig_t, transponderConfig);

extern const transponderRequirement_t transponderRequirements[TRANSPONDER_PROVIDER_COUNT];

void transponderInit(void);

void transponderUpdate(timeUs_t currentTimeUs);
void transponderUpdateData(void);
void transponderTransmitOnce(void);
void transponderStartRepeating(void);
void transponderStopRepeating(void);

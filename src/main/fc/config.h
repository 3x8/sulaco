#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "pg/pg.h"

#define MAX_NAME_LENGTH 16u

typedef struct pilotConfig_s {
    char name[MAX_NAME_LENGTH + 1];
} pilotConfig_t;

PG_DECLARE(pilotConfig_t, pilotConfig);

typedef struct systemConfig_s {
    uint8_t pidProfileIndex;
    uint8_t activeRateProfile;
    uint8_t debug_mode;
    uint8_t task_statistics;
    uint8_t rateProfile6PosSwitch;
    uint8_t cpu_overclock;
    uint8_t powerOnArmingGraceTime; // in seconds
    char boardIdentifier[sizeof(TARGET_BOARD_IDENTIFIER) + 1];
} systemConfig_t;

PG_DECLARE(systemConfig_t, systemConfig);

struct pidProfile_s;
extern struct pidProfile_s *currentPidProfile;

void initEEPROM(void);
void resetEEPROM(void);
bool readEEPROM(void);
void writeEEPROM(void);
void ensureEEPROMStructureIsValid(void);

void saveConfigAndNotify(void);
void validateAndFixGyroConfig(void);

uint8_t getCurrentPidProfileIndex(void);
void changePidProfile(uint8_t pidProfileIndex);
struct pidProfile_s;
void resetPidProfile(struct pidProfile_s *profile);

uint8_t getCurrentControlRateProfileIndex(void);
void changeControlRateProfile(uint8_t profileIndex);

bool canSoftwareSerialBeUsed(void);

uint16_t getCurrentMinthrottle(void);

void resetConfigs(void);
void targetConfiguration(void);
void targetValidateConfiguration(void);

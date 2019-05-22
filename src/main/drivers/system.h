#pragma once

#include <stdint.h>
#include <stdbool.h>

void systemInit(void);

typedef enum {
    FAILURE_DEVELOPER = 0,
    FAILURE_MISSING_ACC,
    FAILURE_ACC_INIT,
    FAILURE_ACC_INCOMPATIBLE,
    FAILURE_INVALID_EEPROM_CONTENTS,
    FAILURE_FLASH_WRITE_FAILED,
    FAILURE_GYRO_INIT_FAILED
} failureMode_e;

#define WARNING_FLASH_DURATION_MS 50
#define WARNING_FLASH_COUNT 5
#define WARNING_PAUSE_DURATION_MS 500
#define WARNING_CODE_DURATION_LONG_MS 250
#define WARNING_CODE_DURATION_SHORT_MS 50

// failure
void indicateFailure(failureMode_e mode, int repeatCount);
void failureMode(failureMode_e mode);

// bootloader/IAP
void systemReset(void);
void systemResetToBootloader(void);
void checkForBootLoaderRequest(void);
bool isMPUSoftReset(void);
void cycleCounterInit(void);

void enableGPIOPowerUsageAndNoiseReductions(void);
// current crystal frequency - 8 or 12MHz

extern uint32_t hse_value;
extern uint32_t cachedRccCsrValue;

typedef void extiCallbackHandlerFunc(void);

void registerExtiCallbackHandler(IRQn_Type irqn, extiCallbackHandlerFunc *fn);void unregisterExtiCallbackHandler(IRQn_Type irqn, extiCallbackHandlerFunc *fn);

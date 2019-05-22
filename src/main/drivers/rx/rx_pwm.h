#pragma once

typedef enum {
    INPUT_FILTERING_DISABLED = 0,
    INPUT_FILTERING_ENABLED
} inputFilteringMode_e;

#define PPM_RCVR_TIMEOUT            0
#define PWM_INPUT_PORT_COUNT        8

struct ppmConfig_s;
void ppmRxInit(const struct ppmConfig_s *ppmConfig);
struct pwmConfig_s;
void pwmRxInit(const struct pwmConfig_s *pwmConfig);

uint16_t pwmRead(uint8_t channel);
uint16_t ppmRead(uint8_t channel);

bool isPPMDataBeingReceived(void);
void resetPPMDataReceivedState(void);

bool isPWMDataBeingReceived(void);

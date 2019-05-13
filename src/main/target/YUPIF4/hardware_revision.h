#pragma once

typedef enum yupif4HardwareRevision_t {
    UNKNOWN = 0,
    YUPIF4_RACE1,       // Race V1
    YUPIF4_RACE2,       // Race V2
    YUPIF4_RACE3,       // Race V3
    YUPIF4_MINI,        // Mini
    YUPIF4_NAV          // Navigation
} yupif4HardwareRevision_e;

extern uint8_t hardwareRevision;

void detectHardwareRevision(void);
void updateHardwareRevision(void);

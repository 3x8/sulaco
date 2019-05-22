#pragma once

 typedef enum cjmcuHardwareRevision_t {
    UNKNOWN = 0,
    REV_1, // Blue LED3
    REV_2  // Green LED3
} cjmcuHardwareRevision_e;

extern uint8_t hardwareRevision;

void updateHardwareRevision(void);
void detectHardwareRevision(void);

void spiBusInit(void);

ioTag_t selectMPUIntExtiConfigByHardwareRevision(void);

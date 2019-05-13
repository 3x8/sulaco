#pragma once

typedef enum nazeHardwareRevision_t {
    UNKNOWN = 0,
    NAZE32, // Naze32 and compatible with 8MHz HSE
    NAZE32_REV5, // Naze32 and compatible with 12MHz HSE
    NAZE32_SP // Naze32 w/Sensor Platforms
} nazeHardwareRevision_e;

extern uint8_t hardwareRevision;

void updateHardwareRevision(void);
void detectHardwareRevision(void);

void spiBusInit(void);

ioTag_t selectMPUIntExtiConfigByHardwareRevision(void);

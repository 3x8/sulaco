#pragma once

typedef enum ftf4HardwareRevision_t {
    FORTINIF4_UNKNOWN = 0,
    FORTINIF4_REV_1, // SPI Flash
    FORTINIF4_REV_2, // OSD
    FORTINIF4_REV_3, // OSD Rev3
    FORTINIF4_REV_4  // actually not used
} ftf4HardwareRevision_e;

extern uint8_t hardwareRevision;

void updateHardwareRevision(void);
void detectHardwareRevision(void);

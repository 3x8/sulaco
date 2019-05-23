#pragma once

typedef enum bjf4HardwareRevision_t {
    UNKNOWN = 0,
    BJF4_REV1,       // Flash
    BJF4_REV2,       // SDCard
    BJF4_REV3,       // SDCard + Flash
    BJF4_MINI_REV3A, // Flash (20x20 mini format)
    BJF4_REV4        // SDCard only - improved UART1 inversion
} bjf4HardwareRevision_e;

extern uint8_t hardwareRevision;

void updateHardwareRevision(void);
void detectHardwareRevision(void);

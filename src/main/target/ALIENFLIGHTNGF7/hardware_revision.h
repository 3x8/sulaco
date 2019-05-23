#pragma once

typedef enum awf7HardwareRevision_t {
    AFF7_UNKNOWN = 0,
    AFF7_REV_1, // ICM-20602 (SPI), Current Sensor (ACS712), SDCard Reader
    AFF7_REV_2  // ICM-20602 (SPI), OpenSky RX (CC2510), Current Sensor (ACS712), SDCard Reader
} awf7HardwareRevision_e;

extern uint8_t hardwareRevision;

void updateHardwareRevision(void);
void detectHardwareRevision(void);

#pragma once

typedef enum awf4HardwareRevision_t {
    AFF4_UNKNOWN = 0,
    AFF4_REV_1, // MPU6500 / MPU9250 (SPI), (V1.1 Current Sensor (ACS712), SDCard Reader)
    AFF4_REV_2  // ICM-20602 (SPI), OpenSky RX (CC2510), Current Sensor (ACS712), SDCard Reader
} awf4HardwareRevision_e;

extern uint8_t hardwareRevision;

void updateHardwareRevision(void);
void detectHardwareRevision(void);

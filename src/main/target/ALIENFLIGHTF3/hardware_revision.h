#pragma once

typedef enum awf3HardwareRevision_t {
    AFF3_UNKNOWN = 0,
    AFF3_REV_1, // MPU6050 (I2C)
    AFF3_REV_2  // MPU6500 / MPU9250 (SPI)
} awf3HardwareRevision_e;

extern uint8_t hardwareRevision;
extern bool haveFrSkyRX;

void updateHardwareRevision(void);
void detectHardwareRevision(void);

ioTag_t selectMPUIntExtiConfigByHardwareRevision(void);

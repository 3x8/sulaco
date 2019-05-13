#pragma once

#include "common/time.h"

typedef struct escSensorConfig_s {
    uint8_t halfDuplex;             // Set to false to listen on the TX pin for telemetry data
    uint16_t offset;                // offset consumed by the flight controller / VTX / cam / ... in milliampere

} escSensorConfig_t;

PG_DECLARE(escSensorConfig_t, escSensorConfig);

typedef struct {
    uint8_t dataAge;
    int8_t temperature;  // C degrees
    int16_t voltage;     // 0.01V
    int32_t current;     // 0.01A
    int32_t consumption; // mAh
    int16_t rpm;         // 0.01erpm
} escSensorData_t;

#define ESC_DATA_INVALID 255

#define ESC_BATTERY_AGE_MAX 10

bool escSensorInit(void);
void escSensorProcess(timeUs_t currentTime);

#define ESC_SENSOR_COMBINED 255

escSensorData_t *getEscSensorData(uint8_t motorNumber);

void startEscDataRead(uint8_t *frameBuffer, uint8_t frameLength);
uint8_t getNumberEscBytesRead(void);

uint8_t calculateCrc8(const uint8_t *Buf, const uint8_t BufLen);

int calcEscRpm(int erpm);

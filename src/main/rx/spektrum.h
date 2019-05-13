#pragma once

#define SPEKTRUM_MAX_SUPPORTED_CHANNEL_COUNT 12
#define SPEKTRUM_2048_CHANNEL_COUNT          12
#define SPEKTRUM_1024_CHANNEL_COUNT           7

#define SPEKTRUM_SAT_BIND_DISABLED            0
#define SPEKTRUM_SAT_BIND_MAX                10

#define SPEK_FRAME_SIZE                      16
#define SRXL_FRAME_OVERHEAD                   5
#define SRXL_FRAME_SIZE_MAX (SPEK_FRAME_SIZE + SRXL_FRAME_OVERHEAD)

#define SPEKTRUM_NEEDED_FRAME_INTERVAL     5000

#define SPEKTRUM_BAUDRATE                115200


// Spektrum system type values
#define SPEKTRUM_DSM2_22                   0x01
#define SPEKTRUM_DSM2_11                   0x12
#define SPEKTRUM_DSMX_22                   0xa2
#define SPEKTRUM_DSMX_11                   0xb2

extern uint32_t spekChannelData[SPEKTRUM_MAX_SUPPORTED_CHANNEL_COUNT];

extern bool srxlEnabled;
extern int32_t resolution;
extern uint8_t rssi_channel; // Stores the RX RSSI channel.

void spektrumBind(rxConfig_t *rxConfig);
bool spektrumInit(const rxConfig_t *rxConfig, rxRuntimeConfig_t *rxRuntimeConfig);

bool srxlTelemetryBufferEmpty();
void srxlRxWriteTelemetryData(const void *data, int len);
bool srxlRxIsActive(void);

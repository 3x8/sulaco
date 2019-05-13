#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "platform.h"

#ifdef USE_SERIALRX_SUMH

#include "common/utils.h"

#include "drivers/time.h"

#include "io/serial.h"

#ifdef USE_TELEMETRY
#include "telemetry/telemetry.h"
#endif

#include "pg/rx.h"

#include "rx/rx.h"
#include "rx/sumh.h"

#define SUMH_BAUDRATE 115200

#define SUMH_MAX_CHANNEL_COUNT 8
#define SUMH_FRAME_SIZE 21

static bool sumhFrameDone = false;

static uint8_t sumhFrame[SUMH_FRAME_SIZE];
static uint32_t sumhChannels[SUMH_MAX_CHANNEL_COUNT];

static serialPort_t *sumhPort;


// Receive ISR callback
static void sumhDataReceive(uint16_t c, void *data)
{
    UNUSED(data);

    uint32_t sumhTime;
    static uint32_t sumhTimeLast, sumhTimeInterval;
    static uint8_t sumhFramePosition;

    sumhTime = micros();
    sumhTimeInterval = sumhTime - sumhTimeLast;
    sumhTimeLast = sumhTime;
    if (sumhTimeInterval > 5000) {
        sumhFramePosition = 0;
    }

    sumhFrame[sumhFramePosition] = (uint8_t) c;
    if (sumhFramePosition == SUMH_FRAME_SIZE - 1) {
        // FIXME at this point the value of 'c' is unused and un tested, what should it be, is it important?
        sumhFrameDone = true;
    } else {
        sumhFramePosition++;
    }
}

static uint8_t sumhFrameStatus(rxRuntimeConfig_t *rxRuntimeConfig)
{
    UNUSED(rxRuntimeConfig);

    uint8_t channelIndex;

    if (!sumhFrameDone) {
        return RX_FRAME_PENDING;
    }

    sumhFrameDone = false;

    if (!((sumhFrame[0] == 0xA8) && (sumhFrame[SUMH_FRAME_SIZE - 2] == 0))) {
        return RX_FRAME_PENDING;
    }

    for (channelIndex = 0; channelIndex < SUMH_MAX_CHANNEL_COUNT; channelIndex++) {
        sumhChannels[channelIndex] = (((uint32_t)(sumhFrame[(channelIndex << 1) + 3]) << 8)
                + sumhFrame[(channelIndex << 1) + 4]) / 6.4f - 375;
    }
    return RX_FRAME_COMPLETE;
}

static uint16_t sumhReadRawRC(const rxRuntimeConfig_t *rxRuntimeConfig, uint8_t chan)
{
    UNUSED(rxRuntimeConfig);

    if (chan >= SUMH_MAX_CHANNEL_COUNT) {
        return 0;
    }

    return sumhChannels[chan];
}

bool sumhInit(const rxConfig_t *rxConfig, rxRuntimeConfig_t *rxRuntimeConfig)
{
    UNUSED(rxConfig);

    rxRuntimeConfig->channelCount = SUMH_MAX_CHANNEL_COUNT;
    rxRuntimeConfig->rxRefreshRate = 11000;

    rxRuntimeConfig->rcReadRawFn = sumhReadRawRC;
    rxRuntimeConfig->rcFrameStatusFn = sumhFrameStatus;

    const serialPortConfig_t *portConfig = findSerialPortConfig(FUNCTION_RX_SERIAL);
    if (!portConfig) {
        return false;
    }

#ifdef USE_TELEMETRY
    bool portShared = telemetryCheckRxPortShared(portConfig);
#else
    bool portShared = false;
#endif

    sumhPort = openSerialPort(portConfig->identifier, FUNCTION_RX_SERIAL, sumhDataReceive, NULL, SUMH_BAUDRATE, portShared ? MODE_RXTX : MODE_RX, (rxConfig->serialrx_inverted ? SERIAL_INVERTED : 0));

#ifdef USE_TELEMETRY
    if (portShared) {
        telemetrySharedPort = sumhPort;
    }
#endif

    return sumhPort != NULL;
}
#endif

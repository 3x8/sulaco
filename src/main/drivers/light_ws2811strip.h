#pragma once

#include "drivers/io_types.h"
#include "io/ledstrip.h"

#define WS2811_LED_STRIP_LENGTH    32
#define WS2811_BITS_PER_LED        24
// for 50us delay
#define WS2811_DELAY_BUFFER_LENGTH 42

#define WS2811_DATA_BUFFER_SIZE    (WS2811_BITS_PER_LED * WS2811_LED_STRIP_LENGTH)
// number of bytes needed is #LEDs * 24 bytes + 42 trailing bytes)
#define WS2811_DMA_BUFFER_SIZE     (WS2811_DATA_BUFFER_SIZE + WS2811_DELAY_BUFFER_LENGTH)

#define WS2811_TIMER_MHZ           48
#define WS2811_CARRIER_HZ          800000

void ws2811LedStripInit(ioTag_t ioTag);

void ws2811LedStripHardwareInit(ioTag_t ioTag);
void ws2811LedStripDMAEnable(void);

void ws2811UpdateStrip(ledStripFormatRGB_e ledFormat);

void setLedHsv(uint16_t index, const hsvColor_t *color);
void getLedHsv(uint16_t index, hsvColor_t *color);

void scaleLedValue(uint16_t index, const uint8_t scalePercent);
void setLedValue(uint16_t index, const uint8_t value);

void setStripColor(const hsvColor_t *color);
void setStripColors(const hsvColor_t *colors);

bool isWS2811LedStripReady(void);

#if defined(STM32F1) || defined(STM32F3)
extern uint8_t ledStripDMABuffer[WS2811_DMA_BUFFER_SIZE];
#else
extern uint32_t ledStripDMABuffer[WS2811_DMA_BUFFER_SIZE];
#endif
extern volatile uint8_t ws2811LedDataTransferInProgress;

extern uint16_t BIT_COMPARE_1;
extern uint16_t BIT_COMPARE_0;

/*
 * Author: Giles Burgess (giles@multiflite.co.uk)
 *
 * This source code is provided as is and can be used/modified so long
 * as this header is maintained with the file at all times.
 */

#pragma once

#include <stdint.h>

#define VTX_RTC6705_BAND_COUNT      5
#define VTX_RTC6705_CHANNEL_COUNT   8
#define VTX_RTC6705_POWER_COUNT     3
#define VTX_RTC6705_DEFAULT_POWER   1

#if defined(RTC6705_POWER_PIN)
#define VTX_RTC6705_MIN_POWER   0
#else
#define VTX_RTC6705_MIN_POWER   1
#endif

#define VTX_RTC6705_FREQ_MIN    5600
#define VTX_RTC6705_FREQ_MAX    5950

#define VTX_RTC6705_BOOT_DELAY  350 // milliseconds

void rtc6705IOInit(void);
void rtc6705SetFrequency(uint16_t freq);
void rtc6705SetRFPower(uint8_t rf_power);
void rtc6705Disable(void);
void rtc6705Enable(void);

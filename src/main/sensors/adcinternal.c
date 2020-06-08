#include <stdbool.h>
#include <stdint.h>

#include "platform.h"

#if defined(USE_ADC) && defined(USE_ADC_INTERNAL)

  #include "build/debug.h"
  #include "common/utils.h"
  #include "drivers/adc.h"

  typedef struct movingAverageStateUint16_s {
    uint32_t sum;
    uint16_t *values;
    uint8_t size;
    uint8_t pos;
  } movingAverageStateUint16_t;

  uint16_t updateMovingAverageUint16(movingAverageStateUint16_t *state, uint16_t newValue) {
    state->sum -= state->values[state->pos];
    state->values[state->pos] = newValue;
    state->sum += newValue;
    state->pos = (state->pos + 1) % state->size;

    return (state->sum / state->size);
  }

  static uint16_t adcVrefintValue;
  static uint16_t adcVrefintValues[8];
  movingAverageStateUint16_t adcVrefintAverageState = { 0, adcVrefintValues, 8, 0 } ;

  static uint16_t adcTempsensorValue;
  static uint16_t adcTempsensorValues[8];
  movingAverageStateUint16_t adcTempsensorAverageState = { 0, adcTempsensorValues, 8, 0 } ;

  static int16_t coreTemperature;

  uint16_t getVrefMv(void) {
    #ifdef ADC_VOLTAGE_REFERENCE_MV
      return ADC_VOLTAGE_REFERENCE_MV;
    #else
      return (3300 * adcVrefintValue / adcVREFINTCAL);
    #endif
  }

  int16_t getCoreTemperatureCelsius(void) {
    return coreTemperature;
  }

  void adcInternalProcess(timeUs_t currentTimeUs) {
      UNUSED(currentTimeUs);

      if (adcInternalIsBusy()) {
        return;
      }

      uint16_t vrefintSample = adcInternalReadVrefint();
      uint16_t tempsensorSample = adcInternalReadTempsensor();

      adcVrefintValue = updateMovingAverageUint16(&adcVrefintAverageState, vrefintSample);
      adcTempsensorValue = updateMovingAverageUint16(&adcTempsensorAverageState, tempsensorSample);

      int32_t adcTempsensorAdjusted = (int32_t)adcTempsensorValue * 3300 / getVrefMv();
      coreTemperature = ((adcTempsensorAdjusted - adcTSCAL1) * adcTSSlopeK + 30 * 1000 + 500) / 1000;

      DEBUG_SET(DEBUG_CORE_TEMP, 0, coreTemperature);

      adcInternalStartConversion(); // Start next conversion
  }

  void adcInternalInit(void) {
    // Call adcInternalProcess repeatedly to fill moving average array
    for (int i = 0 ; i < 9 ; i++) {
      while (adcInternalIsBusy()) {
        // empty
      }
      adcInternalProcess(0);
    }
  }
#else
  uint16_t getVrefMv(void) {
  #ifdef ADC_VOLTAGE_REFERENCE_MV
    return ADC_VOLTAGE_REFERENCE_MV;
  #else
    return 3300;
  #endif
  }
#endif

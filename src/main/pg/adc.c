#include <stdbool.h>
#include <stdint.h>

#include "platform.h"

#ifdef USE_ADC

#include "pg/pg.h"
#include "pg/pg_ids.h"

#include "drivers/adc_impl.h"
#include "drivers/io.h"

#include "pg/adc.h"


PG_REGISTER_WITH_RESET_FN(adcConfig_t, adcConfig, PG_ADC_CONFIG, 0);

void pgResetFn_adcConfig(adcConfig_t *adcConfig)
{
    adcConfig->device = ADC_DEV_TO_CFG(adcDeviceByInstance(ADC_INSTANCE));

#ifdef VBAT_ADC_PIN
    adcConfig->vbat.enabled = true;
    adcConfig->vbat.ioTag = IO_TAG(VBAT_ADC_PIN);
#endif

#ifdef EXTERNAL1_ADC_PIN
    adcConfig->external1.enabled = true;
    adcConfig->external1.ioTag = IO_TAG(EXTERNAL1_ADC_PIN);
#endif

#ifdef CURRENT_METER_ADC_PIN
    adcConfig->current.enabled = true;
    adcConfig->current.ioTag = IO_TAG(CURRENT_METER_ADC_PIN);
#endif

#ifdef RSSI_ADC_PIN
    adcConfig->rssi.enabled = true;
    adcConfig->rssi.ioTag = IO_TAG(RSSI_ADC_PIN);
#endif

}
#endif // USE_ADC

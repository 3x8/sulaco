#include <stdbool.h>
#include <stdint.h>

#include "platform.h"

#include "common/axis.h"

#include "sensors/battery.h"
#include "sensors/barometer.h"
#include "sensors/compass.h"

#include "io/osd.h"

#define VBAT_SCALE       113

#ifdef USE_TARGET_CONFIG
void targetConfiguration(void)
{
    voltageSensorADCConfigMutable(VOLTAGE_SENSOR_ADC_VBAT)->vbatscale = VBAT_SCALE;
    barometerConfigMutable()->baro_hardware = 0;
    compassConfigMutable()->mag_hardware = 0;
    osdConfigMutable()->item_pos[OSD_MAIN_BATT_VOLTAGE] = OSD_POS(12, 1) | VISIBLE_FLAG;
}
#endif

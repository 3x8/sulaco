#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "platform.h"

#include "common/utils.h"

#include "config/feature.h"
#include "pg/pg.h"
#include "pg/pg_ids.h"

#include "fc/config.h"
#include "fc/runtime_config.h"

#include "sensors/sensors.h"
#include "sensors/adcinternal.h"
#include "sensors/acceleration.h"
#include "sensors/barometer.h"
#include "sensors/gyro.h"
#include "sensors/compass.h"
#include "sensors/rangefinder.h"
#include "sensors/initialisation.h"

// requestedSensors is not actually used
uint8_t requestedSensors[SENSOR_INDEX_COUNT] = { GYRO_NONE, ACC_NONE, BARO_NONE, MAG_NONE, RANGEFINDER_NONE };
uint8_t detectedSensors[SENSOR_INDEX_COUNT] = { GYRO_NONE, ACC_NONE, BARO_NONE, MAG_NONE, RANGEFINDER_NONE };

bool sensorsAutodetect(void)
{

    // gyro must be initialised before accelerometer

    bool gyroDetected = gyroInit();

    if (gyroDetected) {
        accInit();
    }

#ifdef USE_MAG
    compassInit();
#endif

#ifdef USE_BARO
    baroDetect(&baro.dev, barometerConfig()->baro_hardware);
#endif

#ifdef USE_RANGEFINDER
    rangefinderInit();
#endif

#ifdef USE_ADC_INTERNAL
    adcInternalInit();
#endif

    return gyroDetected;
}

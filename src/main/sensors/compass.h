#pragma once

#include "common/time.h"
#include "common/maths.h"
#include "drivers/io_types.h"
#include "drivers/sensor.h"
#include "pg/pg.h"
#include "sensors/sensors.h"


// Type of magnetometer used/detected
typedef enum {
    MAG_DEFAULT = 0,
    MAG_NONE = 1,
    MAG_HMC5883 = 2,
    MAG_AK8975 = 3,
    MAG_AK8963 = 4,
    MAG_QMC5883 = 5
} magSensor_e;

typedef struct mag_s {
    float magADC[XYZ_AXIS_COUNT];
    float magneticDeclination;
} mag_t;

extern mag_t mag;

typedef struct compassConfig_s {
    int16_t mag_declination;                // Get your magnetic decliniation from here : http://magnetic-declination.com/
                                            // For example, -6deg 37min, = -637 Japan, format is [sign]dddmm (degreesminutes) default is zero.
    sensor_align_e mag_align;               // mag alignment
    uint8_t mag_hardware;                   // Which mag hardware to use on boards with more than one device
    uint8_t mag_bustype;
    uint8_t mag_i2c_device;
    uint8_t mag_i2c_address;
    uint8_t mag_spi_device;
    ioTag_t mag_spi_csn;
    ioTag_t interruptTag;
    flightDynamicsTrims_t magZero;
} compassConfig_t;

PG_DECLARE(compassConfig_t, compassConfig);

bool compassIsHealthy(quaternion *q);
void compassUpdate(timeUs_t currentTime);
bool compassInit(void);
union flightDynamicsTrims_u;
bool compassGetAverage(quaternion *vAverage);

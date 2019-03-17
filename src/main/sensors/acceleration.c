#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#include "platform.h"

#include "build/debug.h"

#include "common/axis.h"
#include "common/filter.h"
#include "common/utils.h"

#include "config/config_reset.h"
#include "config/feature.h"
#include "pg/pg.h"
#include "pg/pg_ids.h"

#include "drivers/accgyro/accgyro.h"
#include "drivers/accgyro/accgyro_fake.h"
#include "drivers/accgyro/accgyro_mpu.h"
#include "drivers/accgyro/accgyro_mpu3050.h"
#include "drivers/accgyro/accgyro_mpu6050.h"
#include "drivers/accgyro/accgyro_mpu6500.h"
#include "drivers/accgyro/accgyro_spi_bmi160.h"
#include "drivers/accgyro/accgyro_spi_icm20649.h"
#include "drivers/accgyro/accgyro_spi_icm20689.h"
#include "drivers/accgyro/accgyro_spi_mpu6000.h"
#include "drivers/accgyro/accgyro_spi_mpu6500.h"
#include "drivers/accgyro/accgyro_spi_mpu9250.h"

#ifdef USE_ACC_ADXL345
#include "drivers/accgyro_legacy/accgyro_adxl345.h"
#endif

#ifdef USE_ACC_BMA280
#include "drivers/accgyro_legacy/accgyro_bma280.h"
#endif

#ifdef USE_ACC_LSM303DLHC
#include "drivers/accgyro_legacy/accgyro_lsm303dlhc.h"
#endif

#ifdef USE_ACC_MMA8452
#include "drivers/accgyro_legacy/accgyro_mma845x.h"
#endif

#ifdef USE_ACC_IMUF9001
#include "drivers/accgyro/accgyro_imuf9001.h"
#endif

#include "drivers/bus_spi.h"

#include "fc/config.h"
#include "fc/runtime_config.h"

#include "io/beeper.h"

#include "sensors/acceleration.h"
#include "sensors/boardalignment.h"
#include "sensors/gyro.h"
#include "sensors/sensors.h"

#ifdef USE_HARDWARE_REVISION_DETECTION
#include "hardware_revision.h"
#endif


FAST_RAM_ZERO_INIT acc_t acc;

// the calibration is done is the main loop. Calibrating decreases at each cycle down to 0, then we enter in a normal mode.
static uint16_t accCalibrationCyclesToDo = 0;

static flightDynamicsTrims_t *accelerationTrims;

static uint16_t accLpfCutHz = 0;
static biquadFilter_t accFilter[XYZ_AXIS_COUNT];

typedef union accLowpass_u {
    kalman_t kalmanFilterState;
} accLowpass_t;
static accLowpass_t accLowpass[XYZ_AXIS_COUNT];


PG_REGISTER_WITH_RESET_FN(accelerometerConfig_t, accelerometerConfig, PG_ACCELEROMETER_CONFIG, 0);

void resetRollAndPitchTrims(rollAndPitchTrims_t *rollAndPitchTrims) {
    RESET_CONFIG_2(rollAndPitchTrims_t, rollAndPitchTrims,
        .values.roll = 0,
        .values.pitch = 0,
    );
}

void accResetRollAndPitchTrims(void) {
    resetRollAndPitchTrims(&accelerometerConfigMutable()->accelerometerTrims);
}

static void resetFlightDynamicsTrims(flightDynamicsTrims_t *accZero) {
    accZero->values.roll = 0;
    accZero->values.pitch = 0;
    accZero->values.yaw = 0;
    accZero->raw[FACTOR_X] = acc.dev.acc_1G;
    accZero->raw[FACTOR_Y] = acc.dev.acc_1G;
    accZero->raw[FACTOR_Z] = acc.dev.acc_1G;
}

void accResetFlightDynamicsTrims(void) {
    resetFlightDynamicsTrims(&accelerometerConfigMutable()->accZero);
}

void pgResetFn_accelerometerConfig(accelerometerConfig_t *instance) {
    RESET_CONFIG_2(accelerometerConfig_t, instance,
        .acc_healthy = 10,
        .acc_lpf_hz = 0,
        .acc_kalman_w = 32,
        .acc_kalman_q = 2500,
        .acc_align = ALIGN_DEFAULT,
        .acc_hardware = ACC_DEFAULT,
        .acc_high_fsr = false,
    );
    resetRollAndPitchTrims(&instance->accelerometerTrims);
    resetFlightDynamicsTrims(&instance->accZero);
}

bool accDetect(accDev_t *dev, accelerationSensor_e accHardwareToUse) {
    accelerationSensor_e accHardware = ACC_NONE;

#ifdef USE_ACC_ADXL345
    drv_adxl345_config_t acc_params;
#endif

retry:

    switch (accHardwareToUse) {
    case ACC_DEFAULT:
        FALLTHROUGH;

#ifdef USE_ACC_ADXL345
    case ACC_ADXL345:
        acc_params.useFifo = false;
        acc_params.dataRate = 800; // unused currently
        if (adxl345Detect(&acc_params, dev)) {
#ifdef ACC_ADXL345_ALIGN
            dev->accAlign = ACC_ADXL345_ALIGN;
#endif
            accHardware = ACC_ADXL345;
            break;
        }
        FALLTHROUGH;
#endif

#ifdef USE_ACC_LSM303DLHC
    case ACC_LSM303DLHC:
        if (lsm303dlhcAccDetect(dev)) {
#ifdef ACC_LSM303DLHC_ALIGN
            dev->accAlign = ACC_LSM303DLHC_ALIGN;
#endif
            accHardware = ACC_LSM303DLHC;
            break;
        }
        FALLTHROUGH;
#endif

#ifdef USE_ACC_MPU6050
    case ACC_MPU6050:
        if (mpu6050AccDetect(dev)) {
#ifdef ACC_MPU6050_ALIGN
            dev->accAlign = ACC_MPU6050_ALIGN;
#endif
            accHardware = ACC_MPU6050;
            break;
        }
        FALLTHROUGH;
#endif

#ifdef USE_ACC_MMA8452
    case ACC_MMA8452:
        if (mma8452Detect(dev)) {
#ifdef ACC_MMA8452_ALIGN
            dev->accAlign = ACC_MMA8452_ALIGN;
#endif
            accHardware = ACC_MMA8452;
            break;
        }
        FALLTHROUGH;
#endif

#ifdef USE_ACC_BMA280
    case ACC_BMA280:
        if (bma280Detect(dev)) {
#ifdef ACC_BMA280_ALIGN
            dev->accAlign = ACC_BMA280_ALIGN;
#endif
            accHardware = ACC_BMA280;
            break;
        }
        FALLTHROUGH;
#endif

#ifdef USE_ACC_SPI_MPU6000
    case ACC_MPU6000:
        if (mpu6000SpiAccDetect(dev)) {
#ifdef ACC_MPU6000_ALIGN
            dev->accAlign = ACC_MPU6000_ALIGN;
#endif
            accHardware = ACC_MPU6000;
            break;
        }
        FALLTHROUGH;
#endif

#ifdef USE_ACC_SPI_MPU9250
    case ACC_MPU9250:
        if (mpu9250SpiAccDetect(dev)) {
#ifdef ACC_MPU9250_ALIGN
            dev->accAlign = ACC_MPU9250_ALIGN;
#endif
            accHardware = ACC_MPU9250;
            break;
        }
        FALLTHROUGH;
#endif

    case ACC_MPU6500:
    case ACC_ICM20601:
    case ACC_ICM20602:
    case ACC_ICM20608G:
#if defined(USE_ACC_MPU6500) || defined(USE_ACC_SPI_MPU6500)
#ifdef USE_ACC_SPI_MPU6500
        if (mpu6500AccDetect(dev) || mpu6500SpiAccDetect(dev)) {
#else
        if (mpu6500AccDetect(dev)) {
#endif
#ifdef ACC_MPU6500_ALIGN
            dev->accAlign = ACC_MPU6500_ALIGN;
#endif
            switch (dev->mpuDetectionResult.sensor) {
            case MPU_9250_SPI:
                accHardware = ACC_MPU9250;
                break;
            case ICM_20601_SPI:
                accHardware = ACC_ICM20601;
                break;
            case ICM_20602_SPI:
                accHardware = ACC_ICM20602;
                break;
            case ICM_20608_SPI:
                accHardware = ACC_ICM20608G;
                break;
            default:
                accHardware = ACC_MPU6500;
            }
            break;
        }
#endif
        FALLTHROUGH;

#ifdef USE_ACC_SPI_ICM20649
    case ACC_ICM20649:
        if (icm20649SpiAccDetect(dev)) {
            accHardware = ACC_ICM20649;
#ifdef ACC_ICM20649_ALIGN
            dev->accAlign = ACC_ICM20649_ALIGN;
#endif
            break;
        }
        FALLTHROUGH;
#endif

#ifdef USE_ACC_IMUF9001
    case ACC_IMUF9001:
        if (imufSpiAccDetect(dev)) {
            accHardware = ACC_IMUF9001;
            break;
        }
        FALLTHROUGH;
#endif

#ifdef USE_ACC_SPI_ICM20689
    case ACC_ICM20689:
        if (icm20689SpiAccDetect(dev)) {
            accHardware = ACC_ICM20689;
#ifdef ACC_ICM20689_ALIGN
            dev->accAlign = ACC_ICM20689_ALIGN;
#endif
            break;
        }
        FALLTHROUGH;
#endif

#ifdef USE_ACCGYRO_BMI160
    case ACC_BMI160:
        if (bmi160SpiAccDetect(dev)) {
            accHardware = ACC_BMI160;
#ifdef ACC_BMI160_ALIGN
            dev->accAlign = ACC_BMI160_ALIGN;
#endif
            break;
        }
        FALLTHROUGH;
#endif

#ifdef USE_FAKE_ACC
    case ACC_FAKE:
        if (fakeAccDetect(dev)) {
            accHardware = ACC_FAKE;
            break;
        }
        FALLTHROUGH;
#endif

    default:
    case ACC_NONE:
        accHardware = ACC_NONE;
        break;
    }

    // Found anything? Check if error or ACC is really missing.
    if (accHardware == ACC_NONE && accHardwareToUse != ACC_DEFAULT && accHardwareToUse != ACC_NONE) {
        // Nothing was found and we have a forced sensor that isn't present.
        accHardwareToUse = ACC_DEFAULT;
        goto retry;
    }

    if (accHardware == ACC_NONE) {
        return (false);
    }

    detectedSensors[SENSOR_INDEX_ACC] = accHardware;
    sensorsSet(SENSOR_ACC);
    return (true);
}

bool accInit(void) {
    memset(&acc, 0, sizeof(acc));
    // copy over the common gyro mpu settings
    acc.dev.bus = *gyroSensorBus();
    acc.dev.mpuDetectionResult = *gyroMpuDetectionResult();
    acc.dev.acc_high_fsr = accelerometerConfig()->acc_high_fsr;

#ifdef USE_DUAL_GYRO
    if (gyroConfig()->gyro_to_use == GYRO_CONFIG_USE_GYRO_BOTH) {
        acc.dev.accAlign = ACC_2_ALIGN;
    } else if (gyroConfig()->gyro_to_use == GYRO_CONFIG_USE_GYRO_2) {
        acc.dev.accAlign = ACC_2_ALIGN;
    } else {
        acc.dev.accAlign = ACC_1_ALIGN;
    }
#else
    acc.dev.accAlign = ALIGN_DEFAULT;
#endif

    if (!accDetect(&acc.dev, accelerometerConfig()->acc_hardware)) {
        return (false);
    }
    acc.dev.acc_1G = 256;
    acc.dev.initFn(&acc.dev);

    for (int axis = 0; axis < XYZ_AXIS_COUNT; axis++) {
        if (accLpfCutHz) {
            biquadFilterInitLPF(&accFilter[axis], accLpfCutHz, DEFAULT_ACC_SAMPLE_INTERVAL);
        } else {
            kalmanInit(&accLowpass[axis].kalmanFilterState, accelerometerConfig()->acc_kalman_q * 0.0002f, accelerometerConfig()->acc_kalman_w);
        }
    }

    #ifndef USE_ACC_IMUF9001
    if (accelerometerConfig()->acc_align != ALIGN_DEFAULT) {
        acc.dev.accAlign = accelerometerConfig()->acc_align;
    }
    #endif

    return (true);
}

void accSetCalibrationCycles(uint16_t calibrationCyclesRequired) {
    accCalibrationCyclesToDo = calibrationCyclesRequired;
}

bool accCalibrationComplete(void) {
    return accCalibrationCyclesToDo == 0;
}

static bool accCalibrationFinalCycle(void) {
    return accCalibrationCyclesToDo == 1;
}

static bool accCalibrationFirstCycle(void) {
    return accCalibrationCyclesToDo == CALIBRATING_ACC_CYCLES;
}

static void accRunCalibration(rollAndPitchTrims_t *rollAndPitchTrims) {
    // low precision 1 point calibration
    static int32_t accCalibrationBuffer[3];

    for (int axis = 0; axis < 3; axis++) {
        if (accCalibrationFirstCycle()) {
            accCalibrationBuffer[axis] = 0;
        }

        accCalibrationBuffer[axis] += acc.accADC[axis];

        // clear globals to prevent other code from using un-calibrated data
        acc.accADC[axis] = 0;
        accelerationTrims->raw[axis] = 0;
    }

    if (accCalibrationFinalCycle()) {
        accelerationTrims->raw[X] = accCalibrationBuffer[X] / CALIBRATING_ACC_CYCLES;
        accelerationTrims->raw[Y] = accCalibrationBuffer[Y] / CALIBRATING_ACC_CYCLES;
        accelerationTrims->raw[Z] = accCalibrationBuffer[Z] / CALIBRATING_ACC_CYCLES - acc.dev.acc_1G;
        accelerationTrims->raw[FACTOR_X] = acc.dev.acc_1G;
        accelerationTrims->raw[FACTOR_Y] = acc.dev.acc_1G;
        accelerationTrims->raw[FACTOR_Z] = acc.dev.acc_1G;

        resetRollAndPitchTrims(rollAndPitchTrims);
        saveConfigAndNotify();
    }
    accCalibrationCyclesToDo--;
}

void accUpdate(timeUs_t currentTimeUs, rollAndPitchTrims_t *rollAndPitchTrims) {
    UNUSED(currentTimeUs);

    if (!acc.dev.readFn(&acc.dev)) {
        return;
    }

    for (int axis = 0; axis < XYZ_AXIS_COUNT; axis++) {
        DEBUG_SET(DEBUG_ACC, axis, acc.dev.ADCRaw[axis]);
        acc.accADC[axis] = acc.dev.ADCRaw[axis];

        if (accLpfCutHz) {
            acc.accADC[axis] = biquadFilterApply(&accFilter[axis], (float)acc.accADC[axis]);
        } else {
            acc.accADC[axis] = kalmanUpdate(&accLowpass[axis].kalmanFilterState, (float)acc.accADC[axis]);
        }
        DEBUG_SET(DEBUG_ACC_FILTER, axis, lrintf(acc.accADC[axis]));
    }
    DEBUG_SET(DEBUG_ACC, 3, acc.dev.acc_1G);

    #ifndef USE_ACC_IMUF9001
    alignSensors(acc.accADC, acc.dev.accAlign);
    #endif

    if (!accCalibrationComplete()) {
        accRunCalibration(rollAndPitchTrims);
    }

    for (int axis = 0; axis < XYZ_AXIS_COUNT; axis++) {
        acc.accADC[axis] = (acc.accADC[axis] - (float)accelerationTrims->raw[axis]) * ((float)acc.dev.acc_1G / (float)accelerationTrims->raw[axis + 3]);
    }
    DEBUG_SET(DEBUG_ACC_FILTER, 3, acc.dev.acc_1G);

    acc.accUpdatedOnce = true;
}

bool accGetVector(quaternion *vAverage) {
    if (acc.accUpdatedOnce) {
        vAverage->w = 0;
        vAverage->x = acc.accADC[X];
        vAverage->y = acc.accADC[Y];
        vAverage->z = acc.accADC[Z];
        return (true);
    } else {
        quaternionInitVector(vAverage);
        return (false);
    }
}

void accSetTrims(flightDynamicsTrims_t *accelerationTrimsToUse) {
    accelerationTrims = accelerationTrimsToUse;
}

void accInitFilters(void) {
    accLpfCutHz = accelerometerConfig()->acc_lpf_hz;

    for (int axis = 0; axis < XYZ_AXIS_COUNT; axis++) {
        if (accLpfCutHz) {
            biquadFilterInitLPF(&accFilter[axis], accLpfCutHz, DEFAULT_ACC_SAMPLE_INTERVAL);
        } else {
            kalmanInit(&accLowpass[axis].kalmanFilterState, accelerometerConfig()->acc_kalman_q * 0.001f, accelerometerConfig()->acc_kalman_w);
        }
    }
}

bool accIsHealthy(quaternion *q) {
    // accept acc_healthy% deviation
    float accModulus = quaternionModulus(q);
    accModulus = accModulus / acc.dev.acc_1G;
    return (((1.0f - accelerometerConfig()->acc_healthy * 0.01) < accModulus) && (accModulus < (1.0f + accelerometerConfig()->acc_healthy * 0.01)));
}

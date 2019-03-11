static FAST_CODE void GYRO_FILTER_FUNCTION_NAME(gyroSensor_t *gyroSensor)
{
    for (int axis = 0; axis < XYZ_AXIS_COUNT; axis++) {
        GYRO_FILTER_DEBUG_SET(DEBUG_GYRO_RAW, axis, gyroSensor->gyroDev.gyroADCRaw[axis]);
        // scale gyro output to degrees per second
        float gyroADCf = gyroSensor->gyroDev.gyroADC[axis] * gyroSensor->gyroDev.scale;
        const float gyroADCfNoFilter = gyroADCf;
        // DEBUG_GYRO_SCALED records the unfiltered, scaled gyro output
        GYRO_FILTER_DEBUG_SET(DEBUG_GYRO_SCALED, axis, lrintf(gyroADCf));

#ifdef USE_GYRO_DATA_ANALYSE
        if (isDynamicFilterActive()) {
            if (axis == X) {
                GYRO_FILTER_DEBUG_SET(DEBUG_DYNAMIC_NOTCH, 0, lrintf(gyroADCf)); // store raw data
                GYRO_FILTER_DEBUG_SET(DEBUG_DYNAMIC_NOTCH_FREQ, 3, lrintf(gyroADCf)); // store raw data
            }
        }
#endif

        // apply static notch filters and software lowpass filters
        gyroADCf = gyroSensor->notchFilter1ApplyFn((filter_t *)&gyroSensor->notchFilter1[axis], gyroADCf);
        gyroADCf = gyroSensor->notchFilter2ApplyFn((filter_t *)&gyroSensor->notchFilter2[axis], gyroADCf);
        gyroADCf = gyroSensor->lowpassFilterApplyFn((filter_t *)&gyroSensor->lowpassFilter[axis], gyroADCf);
        gyroADCf = gyroSensor->lowpass2FilterApplyFn((filter_t *)&gyroSensor->lowpass2Filter[axis], gyroADCf);

#ifdef USE_GYRO_DATA_ANALYSE
        if (isDynamicFilterActive()) {
            gyroDataAnalysePush(&gyroSensor->gyroAnalyseState, axis, gyroADCf);
            gyroADCf = gyroSensor->notchFilterDynApplyFn((filter_t *)&gyroSensor->notchFilterDyn[axis], gyroADCf);
            if (axis == X) {
                GYRO_FILTER_DEBUG_SET(DEBUG_DYNAMIC_NOTCH, 1, lrintf(gyroADCf));
            }
        }
#endif

        GYRO_FILTER_DEBUG_SET(DEBUG_GYRO_FILTER, axis, lrintf(gyroADCf));
        GYRO_FILTER_DEBUG_SET(DEBUG_GYRO_FILTER_DIFF, axis, lrintf(gyroADCf - gyroADCfNoFilter));
        UNUSED(gyroADCfNoFilter);

        gyroSensor->gyroDev.gyroADCf[axis] = gyroADCf;
    }
}

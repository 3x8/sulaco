#pragma once

#include "arm_math.h"

#include "common/time.h"
#include "common/filter.h"

// max for F3 targets
#define FFT_WINDOW_SIZE 32

typedef struct gyroAnalyseState_s {
    // accumulator for oversampled data => no aliasing and less noise
    uint8_t sampleCount;
    uint8_t maxSampleCount;
    float maxSampleCountRcp;
    float oversampledGyroAccumulator[XYZ_AXIS_COUNT];

    // filter for downsampled accumulated gyro
    biquadFilter_t gyroBandpassFilter[XYZ_AXIS_COUNT];

    // downsampled gyro data circular buffer for frequency analysis
    uint8_t circularBufferIdx;
    float downsampledGyroData[XYZ_AXIS_COUNT][FFT_WINDOW_SIZE];

    // update state machine step information
    uint8_t updateTicks;
    uint8_t updateStep;
    uint8_t updateAxis;

    arm_rfft_fast_instance_f32 fftInstance;
    float fftData[FFT_WINDOW_SIZE];
    float rfftData[FFT_WINDOW_SIZE];

    biquadFilter_t detectedFrequencyFilter[XYZ_AXIS_COUNT];
    uint16_t centerFreq[XYZ_AXIS_COUNT];
} gyroAnalyseState_t;

STATIC_ASSERT(FFT_WINDOW_SIZE <= (uint8_t) -1, window_size_greater_than_underlying_type);

void gyroDataAnalyseStateInit(gyroAnalyseState_t *gyroAnalyse, uint32_t targetLooptime);
void gyroDataAnalysePush(gyroAnalyseState_t *gyroAnalyse, int axis, float sample);
void gyroDataAnalyse(gyroAnalyseState_t *gyroAnalyse, biquadFilter_t *notchFilterDyn);

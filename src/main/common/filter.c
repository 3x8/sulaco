#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#include "platform.h"

#include "build/debug.h"

#include "common/filter.h"
#include "common/maths.h"
#include "common/utils.h"

#define M_LN2_FLOAT 0.69314718055994530942f
#define M_PI_FLOAT  3.14159265358979323846f
#define BIQUAD_Q 1.0f / sqrtf(2.0f)     /* quality factor - 2nd order butterworth*/

// NULL filter
FAST_CODE float nullFilterApply(filter_t *filter, float input) {
    UNUSED(filter);
    return input;
}


// PT1 Low Pass filter
float pt1FilterGain(uint16_t f_cut, float dT) {
    float RC = 1 / ( 2 * M_PI_FLOAT * f_cut);
    return dT / (RC + dT);
}

void pt1FilterInit(pt1Filter_t *filter, float k) {
    filter->state = 0.0f;
    filter->k = k;
}

void pt1FilterUpdateCutoff(pt1Filter_t *filter, float k) {
    filter->k = k;
}

FAST_CODE float pt1FilterApply(pt1Filter_t *filter, float input) {
    filter->state = filter->state + filter->k * (input - filter->state);
    return filter->state;
}

// Slew filter with limit
void slewFilterInit(slewFilter_t *filter, float slewLimit, float threshold) {
    filter->state = 0.0f;
    filter->slewLimit = slewLimit;
    filter->threshold = threshold;
}

FAST_CODE float slewFilterApply(slewFilter_t *filter, float input) {
    if (filter->state >= filter->threshold) {
        if (input >= filter->state - filter->slewLimit) {
            filter->state = input;
        }
    } else if (filter->state <= -filter->threshold) {
        if (input <= filter->state + filter->slewLimit) {
            filter->state = input;
        }
    } else {
        filter->state = input;
    }
    return filter->state;
}

// get notch filter Q given center frequency (f0) and lower cutoff frequency (f1)
// Q = f0 / (f2 - f1) ; f2 = f0^2 / f1
float filterGetNotchQ(float centerFreq, float cutoffFreq) {
    return centerFreq * cutoffFreq / (centerFreq * centerFreq - cutoffFreq * cutoffFreq);
}

// biquad Filter
void biquadFilterInitLPF(biquadFilter_t *filter, float filterFreq, uint32_t refreshRate) {
    biquadFilterInit(filter, filterFreq, refreshRate, BIQUAD_Q, FILTER_LPF);
}

void biquadFilterInit(biquadFilter_t *filter, float filterFreq, uint32_t refreshRate, float Q, biquadFilterType_e filterType) {
    // setup variables
    const float omega = 2.0f * M_PI_FLOAT * filterFreq * refreshRate * 0.000001f;
    const float sn = sin_approx(omega);
    const float cs = cos_approx(omega);
    const float alpha = sn / (2.0f * Q);

    float b0 = 0, b1 = 0, b2 = 0, a0 = 0, a1 = 0, a2 = 0;

    switch (filterType) {
    case FILTER_LPF:
        // 2nd order Butterworth (with Q=1/sqrt(2)) / Butterworth biquad section with Q
        // described in http://www.ti.com/lit/an/slaa447/slaa447.pdf
        b0 = (1 - cs) * 0.5f;
        b1 = 1 - cs;
        b2 = (1 - cs) * 0.5f;
        a0 = 1 + alpha;
        a1 = -2 * cs;
        a2 = 1 - alpha;
        break;
    case FILTER_NOTCH:
        b0 =  1;
        b1 = -2 * cs;
        b2 =  1;
        a0 =  1 + alpha;
        a1 = -2 * cs;
        a2 =  1 - alpha;
        break;
    case FILTER_BPF:
        b0 = alpha;
        b1 = 0;
        b2 = -alpha;
        a0 = 1 + alpha;
        a1 = -2 * cs;
        a2 = 1 - alpha;
        break;
    }

    // precompute the coefficients
    filter->b0 = b0 / a0;
    filter->b1 = b1 / a0;
    filter->b2 = b2 / a0;
    filter->a1 = a1 / a0;
    filter->a2 = a2 / a0;

    // zero initial samples
    filter->x1 = filter->x2 = 0;
    filter->y1 = filter->y2 = 0;
}

FAST_CODE void biquadFilterUpdate(biquadFilter_t *filter, float filterFreq, uint32_t refreshRate, float Q, biquadFilterType_e filterType) {
    // backup state
    float x1 = filter->x1;
    float x2 = filter->x2;
    float y1 = filter->y1;
    float y2 = filter->y2;

    biquadFilterInit(filter, filterFreq, refreshRate, Q, filterType);

    // restore state
    filter->x1 = x1;
    filter->x2 = x2;
    filter->y1 = y1;
    filter->y2 = y2;
}

FAST_CODE void biquadFilterUpdateLPF(biquadFilter_t *filter, float filterFreq, uint32_t refreshRate) {
    biquadFilterUpdate(filter, filterFreq, refreshRate, BIQUAD_Q, FILTER_LPF);
}

/* Computes a biquadFilter_t filter on a sample (slightly less precise than df2 but works in dynamic mode) */
FAST_CODE float biquadFilterApplyDF1(biquadFilter_t *filter, float input) {
    /* compute result */
    const float result = filter->b0 * input + filter->b1 * filter->x1 + filter->b2 * filter->x2 - filter->a1 * filter->y1 - filter->a2 * filter->y2;

    /* shift x1 to x2, input to x1 */
    filter->x2 = filter->x1;
    filter->x1 = input;

    /* shift y1 to y2, result to y1 */
    filter->y2 = filter->y1;
    filter->y1 = result;

    return result;
}

/* Computes a biquadFilter_t filter in direct form 2 on a sample (higher precision but can't handle changes in coefficients */
FAST_CODE float biquadFilterApply(biquadFilter_t *filter, float input) {
    const float result = filter->b0 * input + filter->x1;
    filter->x1 = filter->b1 * input - filter->a1 * result + filter->x2;
    filter->x2 = filter->b2 * input - filter->a2 * result;
    return result;
}

// kalman filter
void kalmanInit(kalman_t *filter, float q, uint32_t w) {
    memset(filter, 0, sizeof(kalman_t));
    filter->q     = q * 0.001f;
    filter->r     = 95.0f;
    filter->p     = 15.0f;
    filter->k     = 0.15f;
    filter->w     = w;
}

#pragma GCC push_options
#pragma GCC optimize("O3")

#define VARIANCE_SCALE 0.001f
FAST_CODE float kalmanUpdate(kalman_t *filter, float input) {
    const float windowSizeInverse = 1.0f/filter->w;

    // project the state ahead using acceleration
    filter->x += (filter->x - filter->lastX);

    // update last state
    filter->lastX = filter->x;

    // prediction update
    filter->p = filter->p + filter->q;

    // measurement update
    filter->k = filter->p / (filter->p + filter->r);
    filter->x += filter->k * (input - filter->x);
    filter->p = (1.0f - filter->k) * filter->p;

    //DEBUG_SET(DEBUG_KALMAN, DEBUG_KALMAN_Q, lrintf(filter->q * 1000));
    DEBUG_SET(DEBUG_KALMAN, DEBUG_KALMAN_Q, lrintf(ABS(input - filter->x)  * 10));
    DEBUG_SET(DEBUG_KALMAN, DEBUG_KALMAN_R, lrintf(filter->r * 10));
    DEBUG_SET(DEBUG_KALMAN, DEBUG_KALMAN_P, lrintf(filter->p * 10));
    DEBUG_SET(DEBUG_KALMAN, DEBUG_KALMAN_K, lrintf(filter->k * 1000));

    // variance update
    filter->window[filter->windowIndex] = input;
    filter->meanSum +=  filter->window[filter->windowIndex];
    filter->varianceSum =  filter->varianceSum + (filter->window[filter->windowIndex] *  filter->window[filter->windowIndex]);
    if (filter->windowIndex++ >= filter->w) {
        filter->windowIndex = 0;
    }
    filter->mean =  filter->meanSum * windowSizeInverse;
    filter->variance =  ABS(filter->varianceSum *  windowSizeInverse - (filter->mean *  filter->mean));
    filter->r = sqrtf(filter->variance) * VARIANCE_SCALE;

    return(filter->x);
}

#pragma GCC pop_options

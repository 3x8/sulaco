#pragma once
#include <stdbool.h>

struct filter_s;
typedef struct filter_s filter_t;

typedef struct pt1Filter_s {
  float state;
  float k;
} pt1Filter_t;

typedef struct slewFilter_s {
  float state;
  float slewLimit;
  float threshold;
} slewFilter_t;

/* this holds the data required to update samples thru a filter */
typedef struct biquadFilter_s {
  float b0, b1, b2, a1, a2;
  float x1, x2, y1, y2;
} biquadFilter_t;

typedef enum {
  FILTER_PT1 = 0,
  FILTER_BIQUAD,
  FILTER_KALMAN,
} lowpassFilterType_e;

typedef enum {
  FILTER_LPF,    // 2nd order Butterworth section
  FILTER_NOTCH,
  FILTER_BPF,
} biquadFilterType_e;

#if (defined(STM32F7) || defined(STM32F4))
  #define MAX_WINDOW_SIZE 256
#else
  #define MAX_WINDOW_SIZE 64
#endif

typedef struct kalman_s {
  uint32_t w;    // window size
  float q;       // process noise covariance
  float r;       // measurement noise covariance
  float p;       // estimation error covariance matrix
  float k;       // kalman gain
  float x;       // state
  float lastX;   // previous state

  float window[MAX_WINDOW_SIZE];
  float variance;
  float varianceSum;
  float mean;
  float meanSum;
  uint32_t windowIndex;
} kalman_t;

typedef float (*filterApplyFnPtr)(filter_t *filter, float input);

float nullFilterApply(filter_t *filter, float input);

void biquadFilterInitLPF(biquadFilter_t *filter, float filterFreq, uint32_t refreshRate);
void biquadFilterInit(biquadFilter_t *filter, float filterFreq, uint32_t refreshRate, float Q, biquadFilterType_e filterType);
void biquadFilterUpdate(biquadFilter_t *filter, float filterFreq, uint32_t refreshRate, float Q, biquadFilterType_e filterType);
void biquadFilterUpdateLPF(biquadFilter_t *filter, float filterFreq, uint32_t refreshRate);

float biquadFilterApplyDF1(biquadFilter_t *filter, float input);
float biquadFilterApply(biquadFilter_t *filter, float input);
float filterGetNotchQ(float centerFreq, float cutoffFreq);

float pt1FilterGain(uint16_t f_cut, float dT);
void pt1FilterInit(pt1Filter_t *filter, float k);
void pt1FilterUpdateCutoff(pt1Filter_t *filter, float k);
float pt1FilterApply(pt1Filter_t *filter, float input);

void slewFilterInit(slewFilter_t *filter, float slewLimit, float threshold);
float slewFilterApply(slewFilter_t *filter, float input);

void kalmanInit(kalman_t *filter, float q, uint32_t w);
float kalmanUpdate(kalman_t *filter, float input);

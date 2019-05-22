#pragma once

typedef enum {
    INTERPOLATION_CHANNELS_RP,
    INTERPOLATION_CHANNELS_RPY,
    INTERPOLATION_CHANNELS_RPYT,
    INTERPOLATION_CHANNELS_T,
    INTERPOLATION_CHANNELS_RPT,
} interpolationChannels_e;

#ifdef USE_GYRO_IMUF9001
extern volatile bool isSetpointNew;
#endif
extern volatile uint16_t currentRxRefreshRate;

void processRcCommand(void);
float getSetpointRate(int axis);
uint32_t getSetpointRateInt(int axis);
float getRcDeflection(int axis);
float getRcDeflectionAbs(int axis);
float getThrottlePIDAttenuation(void);
void updateRcCommands(void);
void resetYawAxis(void);
void initRcProcessing(void);
bool isMotorsReversed(void);
bool rcSmoothingIsEnabled(void);
#ifdef USE_RC_SMOOTHING_FILTER
int rcSmoothingGetValue(int whichValue);
bool rcSmoothingAutoCalculate(void);
bool rcSmoothingInitializationComplete(void);
#endif

#if defined(USE_TPA_CURVES)
float getThrottlePIDAttenuationKp(void);
float getThrottlePIDAttenuationKi(void);
float getThrottlePIDAttenuationKd(void);
#endif

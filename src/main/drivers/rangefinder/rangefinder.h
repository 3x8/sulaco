#pragma once

#include "common/time.h"
#include "drivers/io_types.h"

#define RANGEFINDER_OUT_OF_RANGE        (-1)
#define RANGEFINDER_HARDWARE_FAILURE    (-2)
#define RANGEFINDER_NO_NEW_DATA         (-3)

typedef struct rangefinderHardwarePins_s {
    ioTag_t triggerTag;
    ioTag_t echoTag;
} rangefinderHardwarePins_t;

struct rangefinderDev_s;
typedef void (*rangefinderOpInitFuncPtr)(struct rangefinderDev_s * dev);
typedef void (*rangefinderOpStartFuncPtr)(struct rangefinderDev_s * dev);
typedef int32_t (*rangefinderOpReadFuncPtr)(struct rangefinderDev_s * dev);

typedef struct rangefinderDev_s {
    timeMs_t delayMs;
    int16_t maxRangeCm;

    // these are full detection cone angles, maximum tilt is half of this
    int16_t detectionConeDeciDegrees; // detection cone angle as in device spec
    int16_t detectionConeExtendedDeciDegrees; // device spec is conservative, in practice have slightly larger detection cone

    // function pointers
    rangefinderOpInitFuncPtr init;
    rangefinderOpStartFuncPtr update;
    rangefinderOpReadFuncPtr read;
} rangefinderDev_t;

extern int16_t rangefinderMaxRangeCm;
extern int16_t rangefinderMaxAltWithTiltCm;
extern int16_t rangefinderCfAltCm;

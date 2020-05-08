#pragma once

#include "common/time.h"
#include "pg/pg.h"

#if defined(USE_GPS) || defined(USE_MAG)
extern int16_t magHold;
#endif

typedef struct throttleCorrectionConfig_s {
    uint16_t throttle_correction_angle;     // the angle when the throttle correction is maximal. in 0.1 degres, ex 225 = 22.5 ,30.0, 450 = 45.0 deg
    uint8_t throttle_correction_value;      // the correction that will be applied at throttle_correction_angle.
} throttleCorrectionConfig_t;

PG_DECLARE(throttleCorrectionConfig_t, throttleCorrectionConfig);

union rollAndPitchTrims_u;
void applyAndSaveAccelerometerTrimsDelta(union rollAndPitchTrims_u *rollAndPitchTrimsDelta);

void resetArmingDisabled(void);

void disarm(void);
void tryArm(void);

bool processRx(timeUs_t currentTimeUs);
void updateArmingStatus(void);

void taskMainPidLoop(timeUs_t currentTimeUs);
FAST_CODE void subTaskMotorUpdate(timeUs_t currentTimeUs);
bool isFlipOverAfterCrashMode(void);

void runawayTakeoffTemporaryDisable(uint8_t disableFlag);
bool isAirmodeActivated();
timeUs_t getLastDisarmTimeUs(void);
bool isTryingToArm();
void resetTryingToArm();

void subTaskTelemetryPollSensors(timeUs_t currentTimeUs);

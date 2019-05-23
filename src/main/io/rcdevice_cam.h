#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "common/time.h"
#include "io/rcdevice.h"
#include "fc/rc_modes.h"

#define FIVE_KEY_CABLE_JOYSTICK_MIN 1080
#define FIVE_KEY_CABLE_JOYSTICK_MAX 1920
#define FIVE_KEY_CABLE_JOYSTICK_MID_START 1350
#define FIVE_KEY_CABLE_JOYSTICK_MID_END 1650

typedef struct rcdeviceSwitchState_s {
    bool isActivated;
} rcdeviceSwitchState_t;

extern runcamDevice_t *camDevice;
extern bool rcdeviceInMenu;

void rcdeviceInit(void);
void rcdeviceUpdate(timeUs_t currentTimeUs);

bool rcdeviceIsEnabled(void);

// used for unit test
rcdeviceSwitchState_t switchStates[BOXCAMERA3 - BOXCAMERA1 + 1];

void rcdeviceSend5KeyOSDCableSimualtionEvent(rcdeviceCamSimulationKeyEvent_e key);

#include <stdbool.h>
#include <stdint.h>

#include "platform.h"

#include "fc/runtime_config.h"
#include "io/beeper.h"

uint8_t armingFlags = 0;
uint8_t stateFlags = 0;
uint16_t flightModeFlags = 0;

static uint32_t enabledSensors = 0;

// Must be shorter than OSD_WARNINGS_MAX_SIZE (11) to be displayed fully in OSD
const char *armingDisableFlagNames[]= {
    "NOGYRO",
    "FAILSAFE",
    "RXLOSS",
    "BADRX",
    "BOXFAILSAFE",
    "RUNAWAY",
    "THROTTLE",
    "ANGLE",
    "BOOTGRACE",
    "NOPREARM",
    "LOAD",
    "CALIB",
    "CLI",
    "CMS",
    "OSD",
    "BST",
    "MSP",
    "PARALYZE",
    "GPS",
    "ARMSWITCH"
};

static armingDisableFlags_e armingDisableFlags = 0;

void setArmingDisabled(armingDisableFlags_e flag) {
    armingDisableFlags = armingDisableFlags | flag;
}

void unsetArmingDisabled(armingDisableFlags_e flag) {
    armingDisableFlags = armingDisableFlags & ~flag;
}

bool getArmingDisabled(armingDisableFlags_e flag) {
    return(armingDisableFlags & flag);
}

bool isArmingDisabled(void) {
    return (armingDisableFlags);
}

armingDisableFlags_e getArmingDisableFlags(void) {
    return (armingDisableFlags);
}

uint16_t enableFlightMode(flightModeFlags_e mask) {
    uint16_t oldVal = flightModeFlags;

    flightModeFlags |= (mask);
    if (flightModeFlags != oldVal) {
        beeperConfirmationBeeps(1);
    }
    return (flightModeFlags);
}

uint16_t disableFlightMode(flightModeFlags_e mask) {
    uint16_t oldVal = flightModeFlags;

    flightModeFlags &= ~(mask);
    if (flightModeFlags != oldVal){
        beeperConfirmationBeeps(1);
    }
    return (flightModeFlags);
}

bool sensors(uint32_t mask) {
    return (enabledSensors & mask);
}

void sensorsSet(uint32_t mask) {
    enabledSensors |= mask;
}

void sensorsClear(uint32_t mask) {
    enabledSensors &= ~(mask);
}

uint32_t sensorsMask(void) {
    return (enabledSensors);
}

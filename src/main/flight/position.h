#pragma once

#include "common/time.h"

bool isAltitudeOffset(void);
void calculateEstimatedAltitude(timeUs_t currentTimeUs);
int32_t getEstimatedAltitude(void);
int16_t getEstimatedVario(void);

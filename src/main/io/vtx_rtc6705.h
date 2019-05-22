#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "platform.h"

extern const char * const rtc6705PowerNames[];

bool vtxRTC6705CanUpdate(void);
bool vtxRTC6705Init(void);

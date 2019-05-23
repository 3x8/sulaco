#pragma once

#include "common/time.h"

void taskStackCheck(timeUs_t currentTimeUs);
uint32_t stackUsedSize(void);
uint32_t stackTotalSize(void);
uint32_t stackHighMem(void);

#pragma once

#include "pg/pg.h"
#include "common/time.h"
#include "drivers/rangefinder/rangefinder.h"
#include "sensors/battery.h"

#define RANGEFINDER_HCSR04_TASK_PERIOD_MS 70

typedef struct sonarConfig_s {
    ioTag_t triggerTag;
    ioTag_t echoTag;
} sonarConfig_t;

PG_DECLARE(sonarConfig_t, sonarConfig);

bool hcsr04Detect(rangefinderDev_t *dev, const sonarConfig_t * sonarConfig);

#pragma once

#include "common/time.h"

#define RANGEFINDER_TF_TASK_PERIOD_MS 10

bool lidarTFminiDetect(rangefinderDev_t *dev);
bool lidarTF02Detect(rangefinderDev_t *dev);

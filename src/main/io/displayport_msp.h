#pragma once

#include "pg/pg.h"
#include "drivers/display.h"

PG_DECLARE(displayPortProfile_t, displayPortProfileMsp);

struct displayPort_s;
struct displayPort_s *displayPortMspInit(void);

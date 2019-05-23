#pragma once

#include "pg/pg.h"
#include "drivers/display.h"

PG_DECLARE(displayPortProfile_t, displayPortProfileMax7456);

struct vcdProfile_s;
displayPort_t *max7456DisplayPortInit(const struct vcdProfile_s *vcdProfile);

#pragma once

#include "pg/pg.h"

// Video Character Display parameters

enum VIDEO_SYSTEMS {
    VIDEO_SYSTEM_AUTO = 0,
    VIDEO_SYSTEM_PAL,
    VIDEO_SYSTEM_NTSC
};

typedef struct vcdProfile_s {
    uint8_t video_system;
    int8_t h_offset;
    int8_t v_offset;
} vcdProfile_t;

PG_DECLARE(vcdProfile_t, vcdProfile);

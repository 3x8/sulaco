#pragma once

#include "pg/pg.h"

typedef struct boardAlignment_s {
    int32_t rollDegrees;
    int32_t pitchDegrees;
    int32_t yawDegrees;
} boardAlignment_t;

PG_DECLARE(boardAlignment_t, boardAlignment);

void alignSensors(float *dest, uint8_t rotation);
void initBoardAlignment(const boardAlignment_t *boardAlignment);
bool isBoardAlignmentStandard(const boardAlignment_t *boardAlignment);

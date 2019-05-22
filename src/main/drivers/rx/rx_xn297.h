#pragma once

#include <stdbool.h>
#include <stdint.h>

uint16_t XN297_UnscramblePayload(uint8_t* data, int len, const uint8_t *rxAddr);
uint8_t XN297_WritePayload(uint8_t *data, int len, const uint8_t *rxAddr);

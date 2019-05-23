#pragma once

struct magDev_s;
bool fakeMagDetect(struct magDev_s *mag);
void fakeMagSet(int16_t x, int16_t y, int16_t z);

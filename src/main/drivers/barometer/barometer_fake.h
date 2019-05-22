#pragma once

struct baroDev_s;
bool fakeBaroDetect(struct baroDev_s *baro);
void fakeBaroSet(int32_t pressure, int32_t temperature);

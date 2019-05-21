#pragma once

struct accDev_s;
extern struct accDev_s *fakeAccDev;
bool fakeAccDetect(struct accDev_s *acc);
void fakeAccSet(struct accDev_s *acc, int16_t x, int16_t y, int16_t z);

struct gyroDev_s;
extern struct gyroDev_s *fakeGyroDev;
bool fakeGyroDetect(struct gyroDev_s *gyro);
void fakeGyroSet(struct gyroDev_s *gyro, int16_t x, int16_t y, int16_t z);

#pragma once

#ifdef USE_BEEPER
#define BEEP_TOGGLE              systemBeepToggle()
#define BEEP_OFF                 systemBeep(false)
#define BEEP_ON                  systemBeep(true)
#else
#define BEEP_TOGGLE do {} while (0)
#define BEEP_OFF    do {} while (0)
#define BEEP_ON     do {} while (0)
#endif

void systemBeep(bool on);
void systemBeepToggle(void);
struct beeperDevConfig_s;
void beeperInit(const struct beeperDevConfig_s *beeperDevConfig);

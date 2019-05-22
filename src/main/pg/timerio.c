#include "timerio.h"

#ifdef USE_TIMER_MGMT

PG_REGISTER_ARRAY(timerIOConfig_t, MAX_TIMER_PINMAP_COUNT, timerIOConfig, PG_TIMER_IO_CONFIG, 0);

#endif

#include <stdbool.h>
#include <stdint.h>

#include "platform.h"

#ifdef USE_TARGET_CONFIG

#include "fc/config.h"

#include "flight/pid.h"

#include "sensors/gyro.h"

// Motolab target supports 2 different type of boards Tornado / Cyclone.
void targetConfiguration(void)
{
    gyroConfigMutable()->gyro_sync_denom = 4;
    pidConfigMutable()->pid_process_denom = 1;
}
#endif

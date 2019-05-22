#include <stdint.h>

#include "platform.h"


#ifdef TARGET_VALIDATECONFIG

#include "fc/config.h"

#include "sensors/gyro.h"

void targetValidateConfiguration(void)
{
    if (gyroConfig()->gyro_use_32khz && gyroConfig()->gyroMovementCalibrationThreshold < 148) {
        gyroConfigMutable()->gyroMovementCalibrationThreshold = 148;
    }
}

#endif

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "platform.h"

#include "build/build_config.h"

#include "drivers/time.h"
#include "drivers/io.h"
#include "pwm_esc_detect.h"
#include "timer.h"

#ifdef USE_BRUSHED_ESC_AUTODETECT
uint8_t hardwareMotorType = MOTOR_UNKNOWN;

void detectBrushedESC(void)
{
    int i = 0;
    while (!(timerHardware[i].usageFlags & TIM_USE_MOTOR) && (i < USABLE_TIMER_CHANNEL_COUNT)) {
        i++;
    }

    IO_t MotorDetectPin = IOGetByTag(timerHardware[i].tag);
    IOInit(MotorDetectPin, OWNER_SYSTEM, 0);
    IOConfigGPIO(MotorDetectPin, IOCFG_IPU);

    delayMicroseconds(10);  // allow configuration to settle

    // Check presence of brushed ESC's
    if (IORead(MotorDetectPin)) {
        hardwareMotorType = MOTOR_BRUSHLESS;
    } else {
        hardwareMotorType = MOTOR_BRUSHED;
    }
}
#endif

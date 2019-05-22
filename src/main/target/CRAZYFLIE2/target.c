#include <stdint.h>

#include "platform.h"
#include "drivers/io.h"

#include "drivers/timer.h"
#include "drivers/timer_def.h"
#include "drivers/dma.h"

const timerHardware_t timerHardware[USABLE_TIMER_CHANNEL_COUNT] = {
#if defined(CRAZYFLIE2BQ)
    DEF_TIM(TIM14, CH1, PA7,  TIM_USE_PPM,   0, 0 ), // PPM IN
    DEF_TIM(TIM3,  CH1, PB4,  TIM_USE_MOTOR, 0, 0 ), // PWM1 - OUT1 (Motor 1)
    DEF_TIM(TIM2,  CH3, PA2,  TIM_USE_MOTOR, 0, 0 ), // PWM2 - OUT2 (Motor 2)
    DEF_TIM(TIM3,  CH2, PB5,  TIM_USE_MOTOR, 0, 0 ), // PWM3 - OUT3 (Motor 3)
    DEF_TIM(TIM2,  CH4, PA3,  TIM_USE_MOTOR, 0, 0 ), // PWM4 - OUT4 (Motor 4)
#else
    DEF_TIM(TIM2,  CH4, PB11, TIM_USE_MOTOR, 0, 0 ), // PWM1 - OUT1 (Motor 1)
    DEF_TIM(TIM2,  CH2, PA1,  TIM_USE_MOTOR, 0, 0 ), // PWM2 - OUT2 (Motor 2)
    DEF_TIM(TIM2,  CH1, PA15, TIM_USE_MOTOR, 0, 0 ), // PWM3 - OUT3 (Motor 3)
    DEF_TIM(TIM4,  CH4, PB9,  TIM_USE_MOTOR, 0, 0 ), // PWM4 - OUT4 (Motor 4)
#endif
};

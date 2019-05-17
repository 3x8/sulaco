#include <stdint.h>
#include "platform.h"

#include "drivers/io.h"
#include "drivers/timer.h"
#include "drivers/dma.h"
#include "drivers/timer_def.h"

const timerHardware_t timerHardware[USABLE_TIMER_CHANNEL_COUNT] = {
    DEF_TIM(TIM8, CH3, PB9, TIM_USE_MOTOR,                   0), // PWM1
    DEF_TIM(TIM8, CH2, PB8, TIM_USE_MOTOR,                   0), // PWM2
    DEF_TIM(TIM3, CH4, PB1, TIM_USE_MOTOR,                   0), // PWM3
    DEF_TIM(TIM2, CH2, PA1, TIM_USE_MOTOR,                   0), // PWM4
    DEF_TIM(TIM2, CH3, PA2, TIM_USE_MOTOR,                   0), // PWM5
    DEF_TIM(TIM2, CH4, PA3, TIM_USE_MOTOR,                   0), // PWM6
    DEF_TIM(TIM2, CH1, PA0, TIM_USE_MOTOR,                   0), // PWM7
    DEF_TIM(TIM3, CH3, PB0, TIM_USE_MOTOR,                   0), // PWM8

    DEF_TIM(TIM1, CH1, PA8, TIM_USE_LED|TIM_USE_TRANSPONDER, 0), // LED
};

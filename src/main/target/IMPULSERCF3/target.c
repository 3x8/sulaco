#include <stdint.h>

#include "platform.h"
#include "drivers/io.h"

#include "drivers/timer.h"
#include "drivers/timer_def.h"
#include "drivers/dma.h"

const timerHardware_t timerHardware[USABLE_TIMER_CHANNEL_COUNT] = {
    DEF_TIM(TIM2,  CH1,  PA15, TIM_USE_PPM,   0), // PPM IN
    DEF_TIM(TIM3,  CH1,  PB4,  TIM_USE_MOTOR, 0), // PWM1       UP(1,3)
    DEF_TIM(TIM3,  CH2,  PB5,  TIM_USE_MOTOR, 0), // PWM2
    DEF_TIM(TIM3,  CH4,  PB1,  TIM_USE_MOTOR, 0), // PWM3
    DEF_TIM(TIM3,  CH3,  PB0,  TIM_USE_MOTOR, 0), // PWM4
    DEF_TIM(TIM4,  CH3,  PB8,  TIM_USE_MOTOR, 0), // PWM5       UP(1,7)
    DEF_TIM(TIM8,  CH3,  PB9,  TIM_USE_MOTOR, 0), // PWM6       UP(2,1)
    DEF_TIM(TIM1,  CH1,  PA8,  TIM_USE_LED,   0), // LED_STRIP  D(1,2)
};

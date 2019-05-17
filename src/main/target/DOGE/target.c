#include <stdint.h>

#include "platform.h"
#include "drivers/io.h"

#include "drivers/timer.h"
#include "drivers/dma.h"
#include "drivers/timer_def.h"

const timerHardware_t timerHardware[USABLE_TIMER_CHANNEL_COUNT] = {
    DEF_TIM(TIM1,  CH1, PA8,  TIM_USE_PPM,   0), // PWM1 - PA8
    DEF_TIM(TIM8,  CH2, PB8,  TIM_USE_MOTOR, 0), // PWM2 - PB8,  DMA2ch5
    DEF_TIM(TIM8,  CH3, PB9,  TIM_USE_MOTOR, 0), // PWM3 - PB9,  DMA2ch1
    DEF_TIM(TIM2,  CH4, PA10, TIM_USE_MOTOR, 0), // PMW4 - PA10, DMA1ch7
    DEF_TIM(TIM2,  CH3, PA9,  TIM_USE_MOTOR, 0), // PWM5 - PA9,  DMA1ch1
    DEF_TIM(TIM2,  CH1, PA0,  TIM_USE_MOTOR, 0), // PWM6 - PA0
    DEF_TIM(TIM2,  CH2, PA1,  TIM_USE_MOTOR, 0), // PWM7 - PA1
    DEF_TIM(TIM3,  CH3, PB0,  TIM_USE_MOTOR, 0), // PWM8 - PB1
    DEF_TIM(TIM3,  CH4, PB1,  TIM_USE_MOTOR, 0), // PWM9 - PB0
    DEF_TIM(TIM16, CH1, PA6,  TIM_USE_LED,   0), // PWM9 - PB0
};

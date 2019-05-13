#include <stdint.h>

#include "platform.h"
#include "drivers/io.h"

#include "drivers/timer.h"
#include "drivers/timer_def.h"
#include "drivers/dma.h"

const timerHardware_t timerHardware[USABLE_TIMER_CHANNEL_COUNT] = {

    DEF_TIM(TIM16, CH1, PB8,  TIM_USE_PPM | TIM_USE_LED, 0),
    DEF_TIM(TIM17, CH1, PB9,  0,                         0),
    DEF_TIM(TIM1,  CH1, PA8,  TIM_USE_MOTOR,             0),
    DEF_TIM(TIM8,  CH1, PC6,  TIM_USE_MOTOR,             0),
    DEF_TIM(TIM8,  CH2, PC7,  TIM_USE_MOTOR,             0),
    DEF_TIM(TIM8,  CH3, PC8,  TIM_USE_MOTOR,             0),
    DEF_TIM(TIM3,  CH4, PB1,  0,                         0),
    DEF_TIM(TIM3,  CH2, PA4,  0,                         0),
    DEF_TIM(TIM4,  CH1, PD12, TIM_USE_BEEPER,            0),
    DEF_TIM(TIM4,  CH2, PD13, 0,                         0),
    DEF_TIM(TIM4,  CH3, PD14, 0,                         0),
    DEF_TIM(TIM4,  CH4, PD15, 0,                         0),
    DEF_TIM(TIM2,  CH2, PA1,  0,                         0),
    DEF_TIM(TIM2,  CH3, PA2,  0,                         0),

};

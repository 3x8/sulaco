#include <stdint.h>

#include "platform.h"
#include "drivers/io.h"

#include "drivers/timer.h"
#include "drivers/timer_def.h"
#include "drivers/dma.h"

const timerHardware_t timerHardware[USABLE_TIMER_CHANNEL_COUNT] = {
    DEF_TIM(TIM2, CH3, PB10, TIM_USE_PWM | TIM_USE_PPM,   0, 0), // PPM
    DEF_TIM(TIM3, CH4, PB1,  TIM_USE_PWM,                 0, 0), // S2_IN
    DEF_TIM(TIM3, CH3, PB0,  TIM_USE_PWM,                 0, 0), // S3_IN
    DEF_TIM(TIM3, CH2, PA7,  TIM_USE_PWM,                 0, 0), // S4_IN
    DEF_TIM(TIM3, CH1, PA6,  TIM_USE_PWM,                 0, 0), // S5_IN
    DEF_TIM(TIM2, CH1, PA5,  TIM_USE_PWM,                 0, 0), // S6_IN
    DEF_TIM(TIM1, CH3, PA10, TIM_USE_MOTOR,               0, 0), // S1_OUT
    DEF_TIM(TIM2, CH2, PB3,  TIM_USE_MOTOR,               0, 0), // S2_OUT
    DEF_TIM(TIM4, CH3, PB8,  TIM_USE_MOTOR,               0, 0), // S3_OUT
    DEF_TIM(TIM4, CH4, PB9,  TIM_USE_MOTOR,               0, 0), // S4_OUT
    DEF_TIM(TIM5, CH1, PA0,  TIM_USE_MOTOR | TIM_USE_LED, 0, 0), // S5_OUT
    DEF_TIM(TIM5, CH2, PA1,  TIM_USE_MOTOR,               0, 0), // S6_OUT
};

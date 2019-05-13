#include <stdint.h>

#include "platform.h"
#include "drivers/io.h"

#include "drivers/timer.h"
#include "drivers/timer_def.h"
#include "drivers/dma.h"

const timerHardware_t timerHardware[USABLE_TIMER_CHANNEL_COUNT] = {
    DEF_TIM(TIM1, CH1, PE9,  TIM_USE_PWM | TIM_USE_PPM, 0, 0), // PPM
    DEF_TIM(TIM1, CH2, PE11, TIM_USE_PWM,               0, 0), // S2_IN
    DEF_TIM(TIM1, CH3, PE13, TIM_USE_PWM,               0, 0), // S3_IN
    DEF_TIM(TIM1, CH4, PE14, TIM_USE_PWM,               0, 0), // S4_IN
    DEF_TIM(TIM9, CH1, PE6,  TIM_USE_PWM,               0, 0), // S5_IN
    DEF_TIM(TIM9, CH2, PE7,  TIM_USE_PWM,               0, 0), // S6_IN
    DEF_TIM(TIM2, CH2, PA1,  TIM_USE_MOTOR,             0, 0), // S1_OUT
    DEF_TIM(TIM2, CH3, PA2,  TIM_USE_MOTOR,             0, 0), // S2_OUT
    DEF_TIM(TIM2, CH4, PA3,  TIM_USE_MOTOR,             0, 0), // S3_OUT
    DEF_TIM(TIM3, CH2, PB5,  TIM_USE_MOTOR,             0, 0), // S4_OUT
    DEF_TIM(TIM3, CH3, PB0,  TIM_USE_MOTOR,             0, 0), // S5_OUT
    DEF_TIM(TIM3, CH4, PB1,  TIM_USE_MOTOR,             0, 0), // S6_OUT
};

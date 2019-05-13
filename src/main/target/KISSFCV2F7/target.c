#include <stdint.h>

#include "platform.h"
#include "drivers/io.h"

#include "drivers/dma.h"
#include "drivers/timer.h"
#include "drivers/timer_def.h"

const timerHardware_t timerHardware[USABLE_TIMER_CHANNEL_COUNT] = {

    DEF_TIM(TIM9, CH1, PA2, TIM_USE_PWM | TIM_USE_PPM,   0, 0),

    DEF_TIM(TIM8,  CH1, PC6,  TIM_USE_MOTOR,               0, 0),
    DEF_TIM(TIM5,  CH1, PA0,  TIM_USE_MOTOR,               0, 0),
    DEF_TIM(TIM4,  CH3, PB8,  TIM_USE_MOTOR,               0, 0),
    DEF_TIM(TIM4,  CH1, PB6,  TIM_USE_MOTOR,               0, 0),

    DEF_TIM(TIM4,  CH2, PB7,  TIM_USE_MOTOR,               0, 0),
    DEF_TIM(TIM8,  CH2, PC7,  TIM_USE_MOTOR,               0, 0),

    DEF_TIM(TIM2,  CH2, PB3,  TIM_USE_LED,                    0, 0)

};

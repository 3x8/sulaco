#include <stdint.h>

#include "platform.h"
#include "drivers/io.h"
#include "drivers/dma.h"

#include "drivers/timer.h"
#include "drivers/timer_def.h"

const timerHardware_t timerHardware[USABLE_TIMER_CHANNEL_COUNT] = {

    DEF_TIM(TIM12, CH2, PB15, TIM_USE_PWM | TIM_USE_PPM, 0, 0),
    DEF_TIM(TIM8,  CH1, PC6,  TIM_USE_PWM,               0, 0),
    DEF_TIM(TIM8,  CH2, PC7,  TIM_USE_PWM,               0, 0),
//    DEF_TIM(TIM8,  CH4, PC9,  TIM_USE_PWM,               0, 0), // Used for SDIO
//    DEF_TIM(TIM8,  CH3, PC8,  TIM_USE_PWM,               0, 0), // Used for SDIO

    DEF_TIM(TIM4,  CH3, PB8,  TIM_USE_MOTOR,             0, 0),
    DEF_TIM(TIM2,  CH4, PA3,  TIM_USE_MOTOR,             0, 1),
    DEF_TIM(TIM3,  CH2, PB5,  TIM_USE_MOTOR,             0, 0),
    DEF_TIM(TIM4,  CH4, PB9,  TIM_USE_MOTOR,             0, 0),
    DEF_TIM(TIM9,  CH2, PE6,  TIM_USE_MOTOR,             0, 0),
    DEF_TIM(TIM3,  CH1, PB4,  TIM_USE_MOTOR,             0, 0),
};

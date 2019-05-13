#include "platform.h"
#include "drivers/io.h"

#include "drivers/dma.h"
#include "drivers/timer.h"
#include "drivers/timer_def.h"

const timerHardware_t timerHardware[USABLE_TIMER_CHANNEL_COUNT] = {
    DEF_TIM(TIM4,  CH1,  PB6,  TIM_USE_MOTOR,               0, 0), // M1
    DEF_TIM(TIM4,  CH2,  PB7,  TIM_USE_MOTOR,               0, 0), // M2
    DEF_TIM(TIM4,  CH3,  PB8,  TIM_USE_MOTOR,               0, 0), // M3
    DEF_TIM(TIM4,  CH4,  PB9,  TIM_USE_MOTOR,               0, 0), // M4
    DEF_TIM(TIM3,  CH3,  PB0,  TIM_USE_MOTOR,               0, 0), // M5
    DEF_TIM(TIM3,  CH4,  PB1,  TIM_USE_MOTOR,               0, 0), // M6

    DEF_TIM(TIM3,  CH1,  PC6,  TIM_USE_ANY,                 0, 0), // UART6_TX, M7
    DEF_TIM(TIM3,  CH2,  PC7,  TIM_USE_ANY,                 0, 0), // UART6_RX, M8

    DEF_TIM(TIM1,  CH1,  PA8,  TIM_USE_PPM,                 0, 0),
    DEF_TIM(TIM2,  CH1,  PA15, TIM_USE_LED,                 0, 0),
    DEF_TIM(TIM8,  CH4,  PC9,  TIM_USE_ANY,                 0, 0)
};

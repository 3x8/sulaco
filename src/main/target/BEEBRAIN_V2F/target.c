#include <stdint.h>

#include "platform.h"
#include "drivers/io.h"

#include "drivers/dma.h"
#include "drivers/timer.h"
#include "drivers/timer_def.h"

const timerHardware_t timerHardware[USABLE_TIMER_CHANNEL_COUNT] = {
    DEF_TIM(TIM1,  CH3N, PB15, TIM_USE_MOTOR,                     0), // PWM1  - PB15 - DMA1_CH6 - *TIM1_CH3N, TIM15_CH1N, TIM15_CH2
    DEF_TIM(TIM15, CH1,  PB14, TIM_USE_MOTOR,                     0), // PWM2  - PB14 - DMA1_CH5 - TIM1_CH2N, *TIM15_CH1
    DEF_TIM(TIM1,  CH1,  PA8,  TIM_USE_MOTOR,                     0), // PWM3  - PA8  - DMA1_CH2 - *TIM1_CH1, TIM4_ETR
    DEF_TIM(TIM8,  CH2N, PB0,  TIM_USE_MOTOR,                     0), // PWM4  - PB0  - DMA2_CH5 - TIM3_CH3, TIM1_CH2N, *TIM8_CH2N
    DEF_TIM(TIM16, CH1,  PB8,  TIM_USE_TRANSPONDER | TIM_USE_LED, 0),
};

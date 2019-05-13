#include <stdint.h>

#include "platform.h"
#include "drivers/io.h"

#include "drivers/dma.h"
#include "drivers/timer.h"
#include "drivers/timer_def.h"

const timerHardware_t timerHardware[USABLE_TIMER_CHANNEL_COUNT] = {
    DEF_TIM(TIM15, CH1, PA2, TIM_USE_MOTOR,               0), // DMA1_CH5
    DEF_TIM(TIM2 , CH4, PA3, TIM_USE_MOTOR,               0), // DMA1_CH7
    DEF_TIM(TIM3,  CH4, PB7, TIM_USE_MOTOR,               0), // DMA1_CH3
    DEF_TIM(TIM1,  CH1, PA8, TIM_USE_MOTOR,               0), // DMA1_CH2
    DEF_TIM(TIM8,  CH2, PB8, TIM_USE_MOTOR | TIM_USE_LED, 0), // DMA2_CH5
    DEF_TIM(TIM8,  CH3, PB9, TIM_USE_MOTOR,               0), // DMA2_CH1
};

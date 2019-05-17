#include <stdint.h>

#include "platform.h"
#include "drivers/io.h"

#include "drivers/dma.h"
#include "drivers/timer.h"
#include "drivers/timer_def.h"

const timerHardware_t timerHardware[USABLE_TIMER_CHANNEL_COUNT] = {
    DEF_TIM(TIM3, CH3, PB0,  TIM_USE_MOTOR, 0, 0 ), // S1_OUT - DMA1_ST7
    DEF_TIM(TIM3, CH4, PB1,  TIM_USE_MOTOR, 0, 0 ), // S2_OUT - DMA1_ST2
    DEF_TIM(TIM2, CH4, PB11, TIM_USE_MOTOR, 0, 1 ), // S3_OUT - DMA1_ST6
    DEF_TIM(TIM2, CH3, PB10, TIM_USE_MOTOR, 0, 0 ), // S4_OUT - DMA1_ST1

    DEF_TIM(TIM1, CH3, PA10, TIM_USE_ANY,   0, 0 ), // FC CAM - DMA1_ST3
    DEF_TIM(TIM4, CH1, PB6,  TIM_USE_LED,   0, 0 ), // LED    - DMA1_ST3
};

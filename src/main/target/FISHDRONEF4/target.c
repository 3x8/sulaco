#include <stdint.h>

#include "platform.h"
#include "drivers/io.h"

#include "drivers/dma.h"
#include "drivers/timer.h"
#include "drivers/timer_def.h"

const timerHardware_t timerHardware[USABLE_TIMER_CHANNEL_COUNT] = {
    DEF_TIM(TIM3, CH3, PB0,  TIM_USE_PPM,   0, 0 ), // PPM IN

    DEF_TIM(TIM4, CH3, PB8,  TIM_USE_MOTOR, 0, 0 ), // S1_OUT - DMA1_ST7
    DEF_TIM(TIM2, CH3, PA2,  TIM_USE_MOTOR, 0, 0 ), // S2_OUT - DMA1_ST1
    DEF_TIM(TIM2, CH1, PA15, TIM_USE_MOTOR, 0, 0 ), // S3_OUT - DMA1_ST5
    DEF_TIM(TIM2, CH4, PA3,  TIM_USE_MOTOR, 0, 1 ), // S4_OUT - DMA1_ST6

    DEF_TIM(TIM5, CH1, PA0,  TIM_USE_LED,   0, 0 ), // LED_STRIP - DMA1_ST2
};

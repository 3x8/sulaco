#include <stdint.h>

#include "platform.h"
#include "drivers/io.h"

#include "drivers/dma.h"
#include "drivers/timer.h"
#include "drivers/timer_def.h"

const timerHardware_t timerHardware[USABLE_TIMER_CHANNEL_COUNT] = {

    DEF_TIM(TIM4, CH4, PB9,  TIM_USE_PPM | TIM_USE_LED, 1,  0 ),     // PPM IN
    DEF_TIM(TIM3, CH4, PB1,  TIM_USE_MOTOR, 0, 0 ),                  // S1_OUT - TIM3_UP - BURST
    DEF_TIM(TIM3, CH3, PB0,  TIM_USE_MOTOR, 0, 0 ),                  // S2_OUT - TIM3_UP - BURST
    DEF_TIM(TIM2, CH3, PA2,  TIM_USE_MOTOR, 0, 0 ),                  // S3_OUT - TIM2_UP - BURST
    DEF_TIM(TIM2, CH4, PA3,  TIM_USE_MOTOR, 0, 1 ),                  // S4_OUT - TIM2_UP - BURST
    DEF_TIM(TIM1, CH3, PA10, TIM_USE_MOTOR, 0, 1 ),                  // S5_OUT - TIM1_UP - BURST
    DEF_TIM(TIM1, CH1, PA8,  TIM_USE_MOTOR, 0, 1 ),                  // S6_OUT - TIM1_UP - BURST
};

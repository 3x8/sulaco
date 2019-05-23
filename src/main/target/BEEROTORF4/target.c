#include <stdint.h>

#include "platform.h"
#include "drivers/io.h"

#include "drivers/dma.h"
#include "drivers/timer.h"
#include "drivers/timer_def.h"

const timerHardware_t timerHardware[USABLE_TIMER_CHANNEL_COUNT] = {
    DEF_TIM(TIM9, CH2,  PA3, TIM_USE_PPM,                       0, 0), // PPM IN

    DEF_TIM(TIM1, CH2N, PB0, TIM_USE_MOTOR,                     0, 0), // M1 - DMAR: DMA2_ST5
    DEF_TIM(TIM1, CH3N, PB1, TIM_USE_MOTOR,                     0, 0), // M2 -
    DEF_TIM(TIM2, CH2,  PA1, TIM_USE_MOTOR,                     0, 0), // M3 - DMAR: DMA1_ST7
    DEF_TIM(TIM2, CH1,  PA0, TIM_USE_MOTOR,                     0, 0), // M4 -
    DEF_TIM(TIM8, CH1,  PC6, TIM_USE_MOTOR,                     0, 0), // M5 - DMAR: DMA2_ST1
    DEF_TIM(TIM8, CH2,  PC7, TIM_USE_MOTOR,                     0, 0), // M6 -
    DEF_TIM(TIM3, CH2,  PB5, TIM_USE_MOTOR,                     0, 0), // M7 - DMAR: DMA1_ST2
    DEF_TIM(TIM4, CH4,  PB9, TIM_USE_MOTOR,                     0, 0), // M8 - DMAR: DMA1_ST6

    DEF_TIM(TIM4, CH3,  PB8, TIM_USE_LED | TIM_USE_TRANSPONDER, 0, 0), // LED_STRIP / TRANSPONDER - DMA1_ST7 (can be used for DShot, conflicts with OSD TX)
};

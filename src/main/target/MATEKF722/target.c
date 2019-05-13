#include <stdint.h>

#include "platform.h"
#include "drivers/io.h"

#include "drivers/dma.h"
#include "drivers/timer.h"
#include "drivers/timer_def.h"

const timerHardware_t timerHardware[USABLE_TIMER_CHANNEL_COUNT] = {
    DEF_TIM(TIM9, CH2, PA3, TIM_USE_PPM, 0, 0),      // PPM

    DEF_TIM(TIM8, CH1, PC6, TIM_USE_MOTOR, 0, 0),   // S1   DMA1_ST4
    DEF_TIM(TIM8, CH2, PC7, TIM_USE_MOTOR, 0, 0),   // S2   DMA2_ST3
    DEF_TIM(TIM8, CH3, PC8, TIM_USE_MOTOR, 0, 0),   // S3   DMA2_ST4
    DEF_TIM(TIM8, CH4, PC9, TIM_USE_MOTOR, 0, 0),   // S4   DMA2_ST7

    DEF_TIM(TIM3, CH4, PB1, TIM_USE_MOTOR, 0, 0),   // S5   DMA1_ST2
    DEF_TIM(TIM1, CH1, PA8, TIM_USE_MOTOR, 0, 0),   // S6   DMA2_ST6

    DEF_TIM(TIM4, CH3, PB8, TIM_USE_MOTOR, 0, 0),  // pwm/S7  DMA1_ST7
    DEF_TIM(TIM5, CH3, PA2, TIM_USE_MOTOR, 0, 0),  // TX2/S8  DMA1_ST0

    DEF_TIM(TIM5, CH1, PA0,  TIM_USE_PWM, 0, 0), // TX4
    DEF_TIM(TIM5, CH2, PA1,  TIM_USE_PWM, 0, 0), // RX4

    DEF_TIM(TIM2, CH1, PA15, TIM_USE_LED, 0, 0),  // LED STRIP  DMA1_ST5
};

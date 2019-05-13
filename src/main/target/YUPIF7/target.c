#include <stdint.h>

#include "platform.h"
#include "drivers/io.h"

#include "drivers/dma.h"
#include "drivers/timer.h"
#include "drivers/timer_def.h"

const timerHardware_t timerHardware[USABLE_TIMER_CHANNEL_COUNT] = {
    DEF_TIM(TIM8,  CH3, PC8,  TIM_USE_PPM,                 0, 0 ), // PPM IN
    DEF_TIM(TIM5,  CH1, PA0,  TIM_USE_MOTOR,               0, 0 ), // S1_OUT - DMA1_ST2
    DEF_TIM(TIM5,  CH2, PA1,  TIM_USE_MOTOR,               0, 0 ), // S2_OUT - DMA1_ST4
    DEF_TIM(TIM5,  CH3, PA2,  TIM_USE_MOTOR,               0, 0 ), // S3_OUT - DMA1_ST1
    DEF_TIM(TIM5,  CH4, PA3,  TIM_USE_MOTOR,               0, 1 ), // S4_OUT - DMA1_ST6
    DEF_TIM(TIM3,  CH3, PB0,  TIM_USE_MOTOR,               0, 0 ), // S5_OUT - DMA1_ST7 - LED Control
    DEF_TIM(TIM3,  CH4, PB1,  TIM_USE_MOTOR | TIM_USE_LED, 0, 0 ), // S6_OUT
    DEF_TIM(TIM4,  CH2, PB7,  TIM_USE_ANY,                 0, 0 ), // Camera Control
    DEF_TIM(TIM12, CH1, PB14, TIM_USE_BEEPER,              0, 0 ), // BEEPER PWM
};

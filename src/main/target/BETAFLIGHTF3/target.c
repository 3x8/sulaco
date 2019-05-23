#include <stdint.h>

#include "platform.h"
#include "drivers/io.h"

#include "drivers/timer.h"
#include "drivers/timer_def.h"
#include "drivers/dma.h"

const timerHardware_t timerHardware[USABLE_TIMER_CHANNEL_COUNT] = {
    DEF_TIM(TIM4,  CH2,  PB7, TIM_USE_PPM,                 0), // PPM  DMA(1,4)

    // Motors 1-4
    DEF_TIM(TIM16, CH1,  PA6, TIM_USE_MOTOR,               0), // PWM1 UP(1,6)
    DEF_TIM(TIM8,  CH1N, PA7, TIM_USE_MOTOR,               0), // PWM2 UP(2,1)
    DEF_TIM(TIM8,  CH2,  PB8, TIM_USE_MOTOR,               0), // PWM3 UP(2,1)
    DEF_TIM(TIM17, CH1,  PB9, TIM_USE_MOTOR,               0), // PWM4 UP(1,7)

    // Motors 5-6 or SoftSerial
    DEF_TIM(TIM3,  CH3,  PB0, TIM_USE_MOTOR,               0), // PWM5 UP(1,3)
    DEF_TIM(TIM3,  CH4,  PB1, TIM_USE_MOTOR,               0), // PWM6 UP(1,3)

    // Motors 7-8 or UART2
    DEF_TIM(TIM2,  CH4,  PA3, TIM_USE_MOTOR,               0), // PWM7/UART2_RX
    DEF_TIM(TIM2,  CH3,  PA2, TIM_USE_MOTOR,               0), // PWM8/UART2_TX

    DEF_TIM(TIM1,  CH1,  PA8, TIM_USE_MOTOR | TIM_USE_LED, 0), // LED  DMA(1,2)
};

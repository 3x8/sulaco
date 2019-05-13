#include <stdint.h>

#include "platform.h"
#include "drivers/io.h"

#include "drivers/dma.h"
#include "drivers/timer.h"
#include "drivers/timer_def.h"

const timerHardware_t timerHardware[USABLE_TIMER_CHANNEL_COUNT] = {
    DEF_TIM(TIM2,  CH2,  PB3,  TIM_USE_ANY,                 0, 0), // CAMERA_CONTROL_PIN

    // TIM8_UP (DMA2_ST1_CH7)
    DEF_TIM(TIM8,  CH1,  PC6,  TIM_USE_MOTOR,               0, 0), // M1
    DEF_TIM(TIM8,  CH2,  PC7,  TIM_USE_MOTOR,               0, 0), // M2
    DEF_TIM(TIM8,  CH3,  PC8,  TIM_USE_MOTOR,               0, 0), // M3
    DEF_TIM(TIM8,  CH4,  PC9,  TIM_USE_MOTOR,               0, 0), // M4
    // TIM3_UP (DMA1_ST2_CH5)
    DEF_TIM(TIM3,  CH3,  PB0,  TIM_USE_MOTOR,               0, 0), // M5
    DEF_TIM(TIM3,  CH4,  PB1,  TIM_USE_MOTOR,               0, 0), // M6

    // backdoor timers
    DEF_TIM(TIM1,  CH2,  PA9,  TIM_USE_ANY,                 0, 0), // UART1_TX

    DEF_TIM(TIM9,  CH1,  PA2,  TIM_USE_ANY,                 0, 0), // UART2_TX
    DEF_TIM(TIM9,  CH2,  PA3,  TIM_USE_ANY,                 0, 0), // UART2_RX

    DEF_TIM(TIM5,  CH1,  PA0,  TIM_USE_ANY,                 0, 0), // UART4_TX
    DEF_TIM(TIM5,  CH2,  PA1,  TIM_USE_ANY,                 0, 0), // UART4_RX

    DEF_TIM(TIM4,  CH1,  PB6,  TIM_USE_PPM | TIM_USE_LED,   0, 0), // LED & PPM (DMA1_ST0_CH2)
};

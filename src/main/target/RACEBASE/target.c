#include <stdint.h>

#include "platform.h"
#include "drivers/io.h"

#include "drivers/timer.h"
#include "drivers/timer_def.h"
#include "drivers/dma.h"

const timerHardware_t timerHardware[USABLE_TIMER_CHANNEL_COUNT] = {
    DEF_TIM(TIM2,  CH1, PA0, TIM_USE_PPM,   0),
    DEF_TIM(TIM8,  CH1, PB6, TIM_USE_MOTOR, 0), // PWM1 - DMA2 CH3
    DEF_TIM(TIM3,  CH4, PB7, TIM_USE_MOTOR, 0), // PWM2 - DMA1 CH3
    DEF_TIM(TIM8,  CH2, PB8, TIM_USE_MOTOR, 0), // PMW3 - DMA2 CH5
    DEF_TIM(TIM17, CH1, PB9, TIM_USE_MOTOR, 0), // PWM4  -DMA1 CH1
    DEF_TIM(TIM1,  CH1, PA8, TIM_USE_LED,   0), // LED  - DMA1 CH2
};

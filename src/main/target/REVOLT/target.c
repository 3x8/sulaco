#include <stdint.h>

#include "platform.h"
#include "drivers/io.h"

#include "drivers/dma.h"
#include "drivers/timer.h"
#include "drivers/timer_def.h"

const timerHardware_t timerHardware[USABLE_TIMER_CHANNEL_COUNT] = {
    DEF_TIM(TIM11, CH1,  PB9, TIM_USE_ANY,                 0, 0), //cam control

    DEF_TIM(TIM8,  CH2N, PB0, TIM_USE_MOTOR,               0, 0), // Motor 1
    DEF_TIM(TIM8,  CH3N, PB1, TIM_USE_MOTOR,               0, 0), // Motor 2
    DEF_TIM(TIM2,  CH4, PA3,  TIM_USE_MOTOR,               0, 0), // Motor 3
    DEF_TIM(TIM2,  CH3, PA2,  TIM_USE_MOTOR,               0, 0), // Motor 4

    DEF_TIM(TIM4,  CH1, PB6,  TIM_USE_LED,                 0, 0), // LED for REVOLT
};

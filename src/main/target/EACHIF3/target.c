#include <stdint.h>

#include "platform.h"
#include "drivers/io.h"

#include "drivers/timer.h"
#include "drivers/timer_def.h"
#include "drivers/dma.h"

const timerHardware_t timerHardware[USABLE_TIMER_CHANNEL_COUNT] = {
    DEF_TIM(TIM2,  CH4,  PA3, TIM_USE_PPM,   0),
    DEF_TIM(TIM17, CH1N, PB7, TIM_USE_MOTOR, 0),
    DEF_TIM(TIM8,  CH1,  PB6, TIM_USE_MOTOR, 0),
    DEF_TIM(TIM8,  CH3,  PB9, TIM_USE_MOTOR, 0),
    DEF_TIM(TIM8,  CH2,  PB8, TIM_USE_MOTOR, 0),
    DEF_TIM(TIM16, CH1,  PA6, TIM_USE_LED,   0),
};

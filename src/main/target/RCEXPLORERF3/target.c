#include <stdbool.h>
#include <stdint.h>

#include "platform.h"
#include "drivers/io.h"

#include "drivers/timer.h"
#include "drivers/timer_def.h"
#include "drivers/dma.h"

const timerHardware_t timerHardware[USABLE_TIMER_CHANNEL_COUNT] = {
    DEF_TIM(TIM1,  CH1, PA8, TIM_USE_MOTOR, 0),
    DEF_TIM(TIM17, CH1, PA7, TIM_USE_MOTOR, 0),
    DEF_TIM(TIM3,  CH3, PB0, TIM_USE_MOTOR, 0),
    DEF_TIM(TIM3,  CH2, PA4, TIM_USE_MOTOR, 0),
    DEF_TIM(TIM3,  CH4, PB1, TIM_USE_MOTOR, 0),
    DEF_TIM(TIM2,  CH2, PA1, TIM_USE_PPM,   0),
    DEF_TIM(TIM16, CH1, PB8, TIM_USE_LED,   0),
};

#include <stdint.h>

#include "platform.h"
#include "drivers/io.h"
#include "drivers/dma.h"

#include "drivers/timer.h"
#include "drivers/timer_def.h"

const timerHardware_t timerHardware[USABLE_TIMER_CHANNEL_COUNT] = {
    DEF_TIM(TIM3, CH2, PC7, TIM_USE_PPM,                 0, 0 ),
    DEF_TIM(TIM5, CH1, PA0, TIM_USE_MOTOR,               0, 0 ),
    DEF_TIM(TIM5, CH2, PA1, TIM_USE_MOTOR,               0, 0 ),
    DEF_TIM(TIM5, CH3, PA2, TIM_USE_MOTOR,               0, 0 ),
    DEF_TIM(TIM5, CH4, PA3, TIM_USE_MOTOR,               0, 1 ),
    DEF_TIM(TIM3, CH3, PB0, TIM_USE_MOTOR | TIM_USE_LED, 0, 0 ),
    DEF_TIM(TIM3, CH4, PB1, TIM_USE_MOTOR,               0, 0 ),
    DEF_TIM(TIM8, CH3, PC8, TIM_USE_MOTOR,               0, 0 ),
    DEF_TIM(TIM8, CH4, PC9, TIM_USE_MOTOR,               0, 0 ),
};

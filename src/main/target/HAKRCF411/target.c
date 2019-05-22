#include <stdint.h>

#include "platform.h"
#include "drivers/io.h"

#include "drivers/dma.h"
#include "drivers/timer.h"
#include "drivers/timer_def.h"

const timerHardware_t timerHardware[USABLE_TIMER_CHANNEL_COUNT] = {
    DEF_TIM(TIM4, CH2, PB7,  TIM_USE_PPM,   0, 0),
    DEF_TIM(TIM1, CH1, PA8,  TIM_USE_MOTOR, 0, 0),
    DEF_TIM(TIM2, CH3, PB10, TIM_USE_MOTOR, 0, 0),
    DEF_TIM(TIM3, CH4, PB1,  TIM_USE_MOTOR, 0, 0),
    DEF_TIM(TIM3, CH3, PB0,  TIM_USE_MOTOR, 0, 0),
    DEF_TIM(TIM2, CH1, PA15, TIM_USE_MOTOR, 0, 0),
    DEF_TIM(TIM2, CH2, PB3,  TIM_USE_MOTOR, 0, 0),
    DEF_TIM(TIM4, CH1, PB6,  TIM_USE_LED,   0, 0),

};

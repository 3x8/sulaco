#include <stdint.h>

#include "platform.h"
#include "drivers/io.h"

#include "drivers/timer.h"
#include "drivers/timer_def.h"
#include "drivers/dma.h"

const timerHardware_t timerHardware[USABLE_TIMER_CHANNEL_COUNT] = {

    DEF_TIM(TIM2,  CH2,   PB3, TIM_USE_ANY,                0, 0), // USE FOR CAMERA CONTROL

    DEF_TIM(TIM4,  CH1,  PB6, TIM_USE_MOTOR,               0, 0), // D1-ST6
    DEF_TIM(TIM4,  CH2,  PB7, TIM_USE_MOTOR,               0, 0), // D1-ST6
    DEF_TIM(TIM4,  CH3,  PB8, TIM_USE_MOTOR,               0, 0), // D1-ST6
    DEF_TIM(TIM4,  CH4,  PB9, TIM_USE_MOTOR,               0, 0), // D1-ST6

    DEF_TIM(TIM3,  CH4, PB1, TIM_USE_MOTOR | TIM_USE_LED,  0, 0), // D1-ST2


};

#include <stdint.h>

#include "platform.h"
#include "drivers/io.h"

#include "drivers/dma.h"
#include "drivers/timer.h"
#include "drivers/timer_def.h"

const timerHardware_t timerHardware[USABLE_TIMER_CHANNEL_COUNT] = {


    DEF_TIM(TIM11, CH1,  PB9, TIM_USE_ANY,                 0, 0), //   CAMERA_CONTROL_PIN

    DEF_TIM(TIM1,  CH2N, PB0, TIM_USE_MOTOR,               0, 0), // M1 - D2_ST6
    DEF_TIM(TIM8,  CH3N, PB1, TIM_USE_MOTOR,               0, 0), // M2_OUT D2_ST2
    DEF_TIM(TIM2,  CH4,  PA3, TIM_USE_MOTOR,               0, 1), // M3_OUT D1_ST6
    DEF_TIM(TIM2,  CH3,  PA2, TIM_USE_MOTOR,               0, 0), // M4_OUT D1_ST1

    DEF_TIM(TIM3,  CH1,  PB4, TIM_USE_BEEPER,              0, 0), // BEEPER PWM
    DEF_TIM(TIM4,  CH3,  PB8, TIM_USE_MOTOR | TIM_USE_LED, 0, 0), // LED & MOTOR5 D1_ST7

};

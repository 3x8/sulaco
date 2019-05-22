#include <stdint.h>

#include "platform.h"
#include "drivers/io.h"

#include "drivers/timer.h"
#include "drivers/timer_def.h"

const timerHardware_t timerHardware[USABLE_TIMER_CHANNEL_COUNT] = {

    DEF_TIM(TIM2, CH1, PA0,  TIM_USE_PWM,   0), // PWM1 - RC1
    DEF_TIM(TIM2, CH2, PA1,  TIM_USE_PWM,   0), // PWM2 - RC2
    DEF_TIM(TIM2, CH3, PA2,  TIM_USE_PWM,   0), // PWM3 - RC3
    DEF_TIM(TIM2, CH4, PA3,  TIM_USE_PWM,   0), // PWM4 - RC4
    DEF_TIM(TIM3, CH1, PA6,  TIM_USE_PWM,   0), // PWM5 - RC5
    DEF_TIM(TIM3, CH2, PA7,  TIM_USE_PWM,   0), // PWM6 - RC6
    DEF_TIM(TIM3, CH3, PB0,  TIM_USE_PWM,   0), // PWM7 - RC7
    DEF_TIM(TIM3, CH4, PB1,  TIM_USE_PWM,   0), // PWM8 - RC8
    DEF_TIM(TIM1, CH1, PA8,  TIM_USE_MOTOR, 0), // PWM9 - OUT1
    DEF_TIM(TIM1, CH4, PA11, TIM_USE_MOTOR, 0), // PWM10 - OUT2
    DEF_TIM(TIM4, CH1, PB6,  TIM_USE_MOTOR, 0), // PWM11 - OUT3
    DEF_TIM(TIM4, CH2, PB7,  TIM_USE_MOTOR, 0), // PWM12 - OUT4
    DEF_TIM(TIM4, CH3, PB8,  TIM_USE_MOTOR, 0), // PWM13 - OUT5
    DEF_TIM(TIM4, CH4, PB9,  TIM_USE_MOTOR, 0), // PWM14 - OUT6

};

#include <stdint.h>

#include "platform.h"
#include "drivers/io.h"

#include "drivers/timer.h"
#include "drivers/timer_def.h"
#include "drivers/dma.h"

const timerHardware_t timerHardware[USABLE_TIMER_CHANNEL_COUNT] = {
    DEF_TIM(TIM8, CH2, PC7, TIM_USE_PPM,   0, 0), // PPM IN
    DEF_TIM(TIM5, CH3, PA2, TIM_USE_MOTOR, 0, 0), // PWM1
    DEF_TIM(TIM5, CH4, PA3, TIM_USE_MOTOR, 0, 0), // PWM2
    DEF_TIM(TIM5, CH1, PA0, TIM_USE_MOTOR, 0, 0), // PWM3
    DEF_TIM(TIM5, CH2, PA1, TIM_USE_MOTOR, 0, 0), // PWM4
    DEF_TIM(TIM3, CH4, PB1, TIM_USE_MOTOR, 0, 0), // PWM5
    DEF_TIM(TIM3, CH3, PB0, TIM_USE_MOTOR, 0, 0), // PWM6
    DEF_TIM(TIM4, CH3, PB8, TIM_USE_MOTOR, 0, 0), // PWM7
    DEF_TIM(TIM4, CH4, PB9, TIM_USE_MOTOR, 0, 0), // PWM8
    DEF_TIM(TIM8, CH1, PC6, TIM_USE_LED,   0, 0), // LED_STRIP
};

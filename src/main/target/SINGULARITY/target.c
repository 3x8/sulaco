#include <stdint.h>

#include "platform.h"
#include "drivers/io.h"

#include "drivers/timer.h"
#include "drivers/timer_def.h"
#include "drivers/dma.h"

const timerHardware_t timerHardware[USABLE_TIMER_CHANNEL_COUNT] = {
    DEF_TIM(TIM2,  CH1, PA15, TIM_USE_PPM,   0), // PPM/SERIAL RX
    DEF_TIM(TIM3,  CH1, PB4,  TIM_USE_MOTOR, 0), // PWM1
    DEF_TIM(TIM17, CH1, PB5,  TIM_USE_MOTOR, 0), // PWM2
    DEF_TIM(TIM3,  CH3, PB0,  TIM_USE_MOTOR, 0), // PWM3
    DEF_TIM(TIM3,  CH4, PB1,  TIM_USE_MOTOR, 0), // PWM4
    DEF_TIM(TIM16, CH1, PB8,  TIM_USE_MOTOR, 0), // PWM5
    DEF_TIM(TIM4,  CH4, PB9,  TIM_USE_MOTOR, 0), // PWM6
    DEF_TIM(TIM15, CH1, PA2,  TIM_USE_MOTOR, 0), // SOFTSERIAL1 RX (NC)
    DEF_TIM(TIM15, CH2, PA3,  TIM_USE_MOTOR, 0), // SOFTSERIAL1 TX
    DEF_TIM(TIM1,  CH1, PA8,  TIM_USE_LED,   0), // LED_STRIP
};

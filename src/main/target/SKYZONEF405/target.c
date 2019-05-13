#include <stdint.h>

#include <platform.h>
#include "drivers/io.h"

#include "drivers/dma.h"
#include "drivers/timer.h"
#include "drivers/timer_def.h"

const timerHardware_t timerHardware[USABLE_TIMER_CHANNEL_COUNT] = {
    DEF_TIM(TIM12, CH2, PB15, TIM_USE_PPM,   0, 0), // PPM

    DEF_TIM(TIM3,  CH3, PB0,  TIM_USE_MOTOR, 0, 0), // S1 (1,7)
    DEF_TIM(TIM3,  CH4, PB1,  TIM_USE_MOTOR, 0, 0), // S2 (2,2)
    DEF_TIM(TIM3,  CH2, PC7,  TIM_USE_MOTOR, 0, 0), // S3 (2,4)  (2.2)
    DEF_TIM(TIM3,  CH1, PB4,  TIM_USE_MOTOR, 0, 0), // S4 (2,7)
    DEF_TIM(TIM8,  CH3, PC8,  TIM_USE_MOTOR, 0, 0), // S5 (1,2)
    DEF_TIM(TIM8,  CH4, PC9,  TIM_USE_MOTOR, 0, 0), // S6 (1,5)
    DEF_TIM(TIM8,  CH1, PC6,  TIM_USE_MOTOR, 0, 0), // S7 (2,6)
    DEF_TIM(TIM1,  CH1, PA8,  TIM_USE_MOTOR, 0, 1), // S8 (2,1)  (2.3 2.6)

    DEF_TIM(TIM4,  CH1, PB6,  TIM_USE_LED,   0, 0), // LED STRIP(1,0)

    DEF_TIM(TIM2,  CH2, PB3,  TIM_USE_PWM,   0, 0), // FC CAM
};

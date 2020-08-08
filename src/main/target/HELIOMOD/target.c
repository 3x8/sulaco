#include <stdint.h>

#include <platform.h>
#include "drivers/io.h"

#include "drivers/dma.h"
#include "drivers/timer.h"
#include "drivers/timer_def.h"

const timerHardware_t timerHardware[USABLE_TIMER_CHANNEL_COUNT] = {

    DEF_TIM(TIM4,  CH1,  PB6, TIM_USE_ANY,                 0, 0), //   CAMERA_CONTROL_PIN
    DEF_TIM(TIM12, CH1, PB14, TIM_USE_PWM | TIM_USE_PPM,   0, 0),

    // Motors
    DEF_TIM(TIM8,  CH1, PC6,  TIM_USE_MOTOR,               0, 0), // S1_OUT D1_ST7
    DEF_TIM(TIM8,  CH2, PC7,  TIM_USE_MOTOR,               0, 0), // S2_OUT D1_ST2
    DEF_TIM(TIM8,  CH3, PC8,  TIM_USE_MOTOR,               0, 1), // S3_OUT D1_ST6
    DEF_TIM(TIM8,  CH4, PC9,  TIM_USE_MOTOR,               0, 0), // S4_OUT D1_ST1

    // LED strip
    DEF_TIM(TIM1,  CH1, PA8,  TIM_USE_LED, 0, 0), // D1_ST0
};

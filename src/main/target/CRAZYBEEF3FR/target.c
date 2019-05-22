#include <stdint.h>

#include "platform.h"

#include "drivers/io.h"
#include "drivers/timer.h"
#include "drivers/timer_def.h"
#include "drivers/dma.h"

const timerHardware_t timerHardware[USABLE_TIMER_CHANNEL_COUNT] = {
    // TIM8_UP, DMA2_CH1
    DEF_TIM(TIM8, CH2, PB8, TIM_USE_MOTOR, 0),
    DEF_TIM(TIM8, CH3, PB9, TIM_USE_MOTOR, 0),
    // TIM2_UP, DMA1_CH2
    DEF_TIM(TIM2, CH4, PA3, TIM_USE_MOTOR, 0),
    DEF_TIM(TIM2, CH3, PA2, TIM_USE_MOTOR, 0),
	DEF_TIM(TIM4, CH1, PB6, TIM_USE_MOTOR, 0), //PB6 for servo
	DEF_TIM(TIM3, CH1, PB4, TIM_USE_LED,   0), //LED_STRIP
};

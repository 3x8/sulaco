#include <stdint.h>

#include "platform.h"
#include "drivers/io.h"

#include "drivers/dma.h"
#include "drivers/timer.h"
#include "drivers/timer_def.h"

const timerHardware_t timerHardware[USABLE_TIMER_CHANNEL_COUNT] = {
    DEF_TIM(TIM2, CH4, PA3, TIM_USE_MOTOR, 0, 1),
    DEF_TIM(TIM3, CH3, PB0, TIM_USE_MOTOR, 0, 0),
    DEF_TIM(TIM3, CH4, PB1, TIM_USE_MOTOR, 0, 0),
    DEF_TIM(TIM2, CH3, PA2, TIM_USE_MOTOR, 0, 0),
#if defined(PLUMF4) || defined(KIWIF4V2)
//    DEF_TIM(TIM4,  CH1, PA0,  TIM_USE_LED,   TIMER_OUTPUT_STANDARD, 0),  //LED
//Switch LED_STRIP back to VTX.DTA, since the LED pad does not seem to be working:
    DEF_TIM(TIM4, CH2, PB7, TIM_USE_LED,   0, 0), // LED
#else
    DEF_TIM(TIM4, CH2, PB7, TIM_USE_LED,   0, 0), // LED
#endif
};

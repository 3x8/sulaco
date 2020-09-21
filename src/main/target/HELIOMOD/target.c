#include <stdint.h>

#include <platform.h>
#include "drivers/io.h"

#include "drivers/dma.h"
#include "drivers/timer.h"
#include "drivers/timer_def.h"

const timerHardware_t timerHardware[USABLE_TIMER_CHANNEL_COUNT] = {
  // led strip
  DEF_TIM(TIM1, CH1, PA8, TIM_USE_LED, 0, 0),
  // camera control
  DEF_TIM(TIM4, CH1, PB6, TIM_USE_ANY, 0, 0),
  DEF_TIM(TIM12, CH1, PB14, TIM_USE_PWM | TIM_USE_PPM, 0, 0),

  // motors
  DEF_TIM(TIM3, CH1, PC6, TIM_USE_MOTOR, 0, 0),
  DEF_TIM(TIM3, CH2, PC7, TIM_USE_MOTOR, 0, 0),
  DEF_TIM(TIM3, CH3, PC8, TIM_USE_MOTOR, 0, 0),
  DEF_TIM(TIM3, CH4, PC9, TIM_USE_MOTOR, 0, 0),
};

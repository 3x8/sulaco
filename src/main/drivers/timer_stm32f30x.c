#include "platform.h"

#include "common/utils.h"

#include "stm32f30x.h"
#include "rcc.h"
#include "timer.h"

const timerDef_t timerDefinitions[HARDWARE_TIMER_DEFINITION_COUNT] = {
    { .TIMx = TIM1,  .rcc = RCC_APB2(TIM1),  .inputIrq = TIM1_CC_IRQn },
    { .TIMx = TIM2,  .rcc = RCC_APB1(TIM2),  .inputIrq = TIM2_IRQn },
    { .TIMx = TIM3,  .rcc = RCC_APB1(TIM3),  .inputIrq = TIM3_IRQn },
    { .TIMx = TIM4,  .rcc = RCC_APB1(TIM4),  .inputIrq = TIM4_IRQn },
    { .TIMx = TIM6,  .rcc = RCC_APB1(TIM6),  .inputIrq = 0 },
    { .TIMx = TIM7,  .rcc = RCC_APB1(TIM7),  .inputIrq = 0 },
    { .TIMx = TIM8,  .rcc = RCC_APB2(TIM8),  .inputIrq = TIM8_CC_IRQn },
    { .TIMx = TIM15, .rcc = RCC_APB2(TIM15), .inputIrq = TIM1_BRK_TIM15_IRQn },
    { .TIMx = TIM16, .rcc = RCC_APB2(TIM16), .inputIrq = TIM1_UP_TIM16_IRQn },
    { .TIMx = TIM17, .rcc = RCC_APB2(TIM17), .inputIrq = TIM1_TRG_COM_TIM17_IRQn },
};

uint32_t timerClock(TIM_TypeDef *tim)
{
    UNUSED(tim);
    return SystemCoreClock;
}

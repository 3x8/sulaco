#include "platform.h"

#if defined(USE_PWM) || defined(USE_PPM)

#include "drivers/io.h"
#include "drivers/nvic.h"
#include "drivers/rx/rx_pwm.h"
#include "drivers/timer.h"

#include "pg/pg.h"
#include "pg/pg_ids.h"

#include "rx_pwm.h"

#ifdef USE_PWM
PG_REGISTER_WITH_RESET_FN(pwmConfig_t, pwmConfig, PG_PWM_CONFIG, 0);

void pgResetFn_pwmConfig(pwmConfig_t *pwmConfig)
{
    pwmConfig->inputFilteringMode = INPUT_FILTERING_DISABLED;
    for (unsigned inputIndex = 0; inputIndex < PWM_INPUT_PORT_COUNT; inputIndex++) {
        pwmConfig->ioTags[inputIndex] = timerioTagGetByUsage(TIM_USE_PWM, inputIndex);
    }
}
#endif

#ifdef USE_PPM
PG_REGISTER_WITH_RESET_FN(ppmConfig_t, ppmConfig, PG_PPM_CONFIG, 0);

void pgResetFn_ppmConfig(ppmConfig_t *ppmConfig)
{
    ppmConfig->ioTag = timerioTagGetByUsage(TIM_USE_PPM, 0);
}
#endif

#endif

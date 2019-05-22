#include <stdbool.h>
#include <stdint.h>

#include "platform.h"

#ifdef USE_SERVOS

#include "common/utils.h"

#include "flight/mixer.h"
#include "flight/mixer_tricopter.h"

#include "pg/pg.h"
#include "pg/pg_ids.h"


PG_REGISTER_WITH_RESET_TEMPLATE(tricopterMixerConfig_t, tricopterMixerConfig, PG_TRICOPTER_CONFIG, 0);

PG_RESET_TEMPLATE(tricopterMixerConfig_t, tricopterMixerConfig,
    .dummy = 0
);

#define TRICOPTER_ERROR_RATE_YAW_SATURATED 75 // rate at which tricopter yaw axis becomes saturated, determined experimentally by TriFlight

bool mixerTricopterIsServoSaturated(float errorRate)
{
    return errorRate > TRICOPTER_ERROR_RATE_YAW_SATURATED;
}

float mixerTricopterMotorCorrection(int motor)
{
    UNUSED(motor);
    return 0.0f;
}

void mixerTricopterInit(void)
{

}

#endif // USE_SERVOS

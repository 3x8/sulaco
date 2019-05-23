#include <stdbool.h>
#include <stdint.h>

#include "platform.h"

#ifdef USE_SERVOS

#include "flight/mixer.h"
#include "flight/mixer_tricopter.h"
#include "flight/servos.h"


bool servosTricopterIsEnabledServoUnarmed(void)
{
    return servoConfig()->tri_unarmed_servo;
}

void servosTricopterMixer(void)
{
    servoMixer();
}

void servosTricopterInit(void)
{

}

#endif // USE_SERVOS

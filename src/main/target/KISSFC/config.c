#include <stdbool.h>
#include <stdint.h>

#include "platform.h"

#ifdef USE_TARGET_CONFIG

#include "fc/config.h"

#include "sensors/boardalignment.h"

void targetConfiguration(void)
{
#ifdef KISSCC
    // alternative defaults settings for Beebrain target
    boardAlignmentMutable()->rollDegrees = 180;
    boardAlignmentMutable()->pitchDegrees = 0;
    boardAlignmentMutable()->yawDegrees = 0;
#endif
}
#endif

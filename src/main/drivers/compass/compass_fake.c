#include <stdbool.h>
#include <stdint.h>

#include "platform.h"

#ifdef USE_FAKE_MAG

#include "build/build_config.h"

#include "common/axis.h"
#include "common/utils.h"

#include "compass.h"
#include "compass_fake.h"


static int16_t fakeMagData[XYZ_AXIS_COUNT];

static bool fakeMagInit(magDev_t *mag)
{
    UNUSED(mag);

    // initially point north
    fakeMagData[X] = 4096;
    fakeMagData[Y] = 0;
    fakeMagData[Z] = 0;
    return true;
}

void fakeMagSet(int16_t x, int16_t y, int16_t z)
{
    fakeMagData[X] = x;
    fakeMagData[Y] = y;
    fakeMagData[Z] = z;
}

static bool fakeMagRead(magDev_t *mag, int16_t *magData)
{
    UNUSED(mag);

    magData[X] = fakeMagData[X];
    magData[Y] = fakeMagData[Y];
    magData[Z] = fakeMagData[Z];
    return true;
}

bool fakeMagDetect(magDev_t *mag)
{
    mag->init = fakeMagInit;
    mag->read = fakeMagRead;
    return true;
}
#endif // USE_FAKE_MAG

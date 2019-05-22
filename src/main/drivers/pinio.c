#include <stdint.h>

#include "platform.h"

#ifdef USE_PINIO

#include "build/debug.h"

#include "pg/pinio.h"

#include "drivers/io.h"

typedef struct pinioRuntime_s {
    IO_t io;
    bool inverted;
    bool state;
} pinioRuntime_t;

static pinioRuntime_t pinioRuntime[PINIO_COUNT];

void pinioInit(const pinioConfig_t *pinioConfig)
{
    for (int i = 0; i < PINIO_COUNT; i++) {
        IO_t io = IOGetByTag(pinioConfig->ioTag[i]);

        if (!io) {
            continue;
        }

        IOInit(io, OWNER_PINIO, RESOURCE_INDEX(i));

        switch (pinioConfig->config[i] & PINIO_CONFIG_MODE_MASK) {
        case PINIO_CONFIG_MODE_OUT_PP:
            // Initial state after reset is input, pull-up.
            // Avoid momentary off by presetting the output to hi.
            if (pinioConfig->config[i] & PINIO_CONFIG_OUT_INVERTED) {
                IOHi(io);
            }
            IOConfigGPIO(io, IOCFG_OUT_PP);
            break;
        }

        if (pinioConfig->config[i] & PINIO_CONFIG_OUT_INVERTED)
        {
            pinioRuntime[i].inverted = true;
            IOHi(io);
            pinioRuntime[i].state = true;
        } else {
            pinioRuntime[i].inverted = false;
            IOLo(io);
            pinioRuntime[i].state = false;
        }
        pinioRuntime[i].io = io;
    }
}

void pinioSet(int index, bool on)
{
    bool newState = on ^ pinioRuntime[index].inverted;
    if (newState != pinioRuntime[index].state) {
        IOWrite(pinioRuntime[index].io, newState);
        pinioRuntime[index].state = newState;
    }
}
#endif

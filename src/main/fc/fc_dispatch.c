#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

#include "platform.h"

#include "common/utils.h"

#include "drivers/time.h"

#include "fc/fc_dispatch.h"

static dispatchEntry_t *head = NULL;
static bool dispatchEnabled = false;

bool dispatchIsEnabled(void)
{
    return dispatchEnabled;
}

void dispatchEnable(void)
{
    dispatchEnabled = true;
}

void dispatchProcess(uint32_t currentTime)
{
    for (dispatchEntry_t **p = &head; *p; ) {
        if (cmp32(currentTime, (*p)->delayedUntil) < 0)
            break;
        // unlink entry first, so handler can replan self
        dispatchEntry_t *current = *p;
        *p = (*p)->next;
        current->inQue = false;
        (*current->dispatch)(current);
    }
}

void dispatchAdd(dispatchEntry_t *entry, int delayUs)
{
    uint32_t delayedUntil = micros() + delayUs;
    dispatchEntry_t **p = &head;

    if (entry->inQue) {
      return;    // Allready in Queue, abort
    }

    while (*p && cmp32((*p)->delayedUntil, delayedUntil) < 0)
        p = &(*p)->next;

    entry->next = *p;
    entry->delayedUntil = delayedUntil;
    entry->inQue = true;
    *p = entry;
}

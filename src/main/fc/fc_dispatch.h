#pragma once

struct dispatchEntry_s;
typedef void dispatchFunc(struct dispatchEntry_s* self);

typedef struct dispatchEntry_s {
    dispatchFunc *dispatch;
    uint32_t delayedUntil;
    struct dispatchEntry_s *next;
    bool inQue;
} dispatchEntry_t;

bool dispatchIsEnabled(void);
void dispatchEnable(void);
void dispatchProcess(uint32_t currentTime);
void dispatchAdd(dispatchEntry_t *entry, int delayUs);

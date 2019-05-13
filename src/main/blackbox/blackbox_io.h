#pragma once

typedef enum {
    BLACKBOX_RESERVE_SUCCESS,
    BLACKBOX_RESERVE_TEMPORARY_FAILURE,
    BLACKBOX_RESERVE_PERMANENT_FAILURE
} blackboxBufferReserveStatus_e;

/*
 * We want to limit how bursty our writes to the device are. Note that this will also restrict the maximum size of a
 * header write we can make:
 */
#define BLACKBOX_MAX_ACCUMULATED_HEADER_BUDGET 256

/*
 * Ideally, each iteration in which we are logging headers would write a similar amount of data to the device as a
 * regular logging iteration. This way we won't hog the CPU by making a gigantic write:
 */
#define BLACKBOX_TARGET_HEADER_BUDGET_PER_ITERATION 64

extern int32_t blackboxHeaderBudget;

void blackboxOpen(void);
void blackboxWrite(uint8_t value);
int blackboxWriteString(const char *s);

void blackboxDeviceFlush(void);
bool blackboxDeviceFlushForce(void);
bool blackboxDeviceOpen(void);
void blackboxDeviceClose(void);

void blackboxEraseAll(void);
bool isBlackboxErased(void);

bool blackboxDeviceBeginLog(void);
bool blackboxDeviceEndLog(bool retainLog);

bool isBlackboxDeviceFull(void);
unsigned int blackboxGetLogNumber(void);

void blackboxReplenishHeaderBudget(void);
blackboxBufferReserveStatus_e blackboxDeviceReserveBufferSpace(int32_t bytes);

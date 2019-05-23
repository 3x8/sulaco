#pragma once

#include "common/streambuf.h"

#define MSP_V2_FRAME_ID         255

typedef enum {
    MSP_V1          = 0,
    MSP_V2_OVER_V1  = 1,
    MSP_V2_NATIVE   = 2,
    MSP_VERSION_COUNT
} mspVersion_e;

#define MSP_VERSION_MAGIC_INITIALIZER { 'M', 'M', 'X' }

// return positive for ACK, negative on error, zero for no reply
typedef enum {
    MSP_RESULT_ACK = 1,
    MSP_RESULT_ERROR = -1,
    MSP_RESULT_NO_REPLY = 0,
    MSP_RESULT_CMD_UNKNOWN = -2,   // don't know how to process command, try next handler
} mspResult_e;

typedef enum {
    MSP_DIRECTION_REPLY = 0,
    MSP_DIRECTION_REQUEST = 1
} mspDirection_e;

typedef struct mspPacket_s {
    sbuf_t buf;
    int16_t cmd;
    uint8_t flags;
    int16_t result;
    uint8_t direction;
} mspPacket_t;

struct serialPort_s;
typedef void (*mspPostProcessFnPtr)(struct serialPort_s *port); // msp post process function, used for gracefully handling reboots, etc.
typedef mspResult_e (*mspProcessCommandFnPtr)(mspPacket_t *cmd, mspPacket_t *reply, mspPostProcessFnPtr *mspPostProcessFn);
typedef void (*mspProcessReplyFnPtr)(mspPacket_t *cmd);


void mspInit(void);
mspResult_e mspFcProcessCommand(mspPacket_t *cmd, mspPacket_t *reply, mspPostProcessFnPtr *mspPostProcessFn);
void mspFcProcessReply(mspPacket_t *reply);
bool mspCommonProcessOutCommand(uint8_t cmdMSP, sbuf_t *dst, mspPostProcessFnPtr *mspPostProcessFn);
mspResult_e mspCommonProcessInCommand(uint8_t cmdMSP, sbuf_t *dst, mspPostProcessFnPtr *mspPostProcessFn);
bool mspProcessOutCommand(uint8_t cmdMSP, sbuf_t *dst);
mspResult_e mspProcessInCommand(uint8_t cmdMSP, sbuf_t *dst);

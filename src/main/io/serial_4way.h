#pragma once

#include "drivers/io_types.h"
#include "io/serial_4way_impl.h"

#define USE_SERIAL_4WAY_BLHELI_BOOTLOADER
#define USE_SERIAL_4WAY_SK_BOOTLOADER

#define imC2 0
#define imSIL_BLB 1
#define imATM_BLB 2
#define imSK 3
#define imARM_BLB 4

extern uint8_t selected_esc;

extern ioMem_t ioMem;

typedef union __attribute__ ((packed)) {
    uint8_t bytes[2];
    uint16_t word;
} uint8_16_u;

typedef union __attribute__ ((packed)) {
    uint8_t bytes[4];
    uint16_t words[2];
    uint32_t dword;
} uint8_32_u;

//extern uint8_32_u DeviceInfo;

bool isMcuConnected(void);
uint8_t esc4wayInit(void);
struct serialPort_s;
void esc4wayProcess(struct serialPort_s *mspPort);
void esc4wayRelease(void);

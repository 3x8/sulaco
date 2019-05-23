#pragma once

#include "drivers/serial.h"

#if defined(STM32F7)
#include "common/maths.h"

#include "usbd_cdc.h"

extern USBD_HandleTypeDef  USBD_Device;
#endif

typedef struct {
    serialPort_t port;

    // Buffer used during bulk writes.
    uint8_t txBuf[20];
    uint8_t txAt;
    // Set if the port is in bulk write mode and can buffer.
    bool buffering;
} vcpPort_t;

serialPort_t *usbVcpOpen(void);
struct serialPort_s;
uint32_t usbVcpGetBaudRate(struct serialPort_s *instance);
uint8_t usbVcpIsConnected(void);

#include <stdbool.h>
#include <stdint.h>

#include "platform.h"

#include "build/build_config.h"

#include "drivers/rcc.h"
#include "drivers/serial.h"
#include "drivers/serial_uart.h"
#include "drivers/serial_uart_impl.h"

FAST_RAM_ZERO_INIT uartDevice_t uartDevice[UARTDEV_COUNT];      // Only those configured in target.h
FAST_RAM_ZERO_INIT uartDevice_t *uartDevmap[UARTDEV_COUNT_MAX]; // Full array

void uartPinConfigure(const serialPinConfig_t *pSerialPinConfig)
{
    uartDevice_t *uartdev = uartDevice;

    for (size_t hindex = 0; hindex < UARTDEV_COUNT; hindex++) {

        const uartHardware_t *hardware = &uartHardware[hindex];
        const UARTDevice_e device = hardware->device;

        for (int pindex = 0 ; pindex < UARTHARDWARE_MAX_PINS ; pindex++) {
            if (hardware->rxPins[pindex] && (hardware->rxPins[pindex] == pSerialPinConfig->ioTagRx[device]))
                uartdev->rx = pSerialPinConfig->ioTagRx[device];

            if (hardware->txPins[pindex] && (hardware->txPins[pindex] == pSerialPinConfig->ioTagTx[device]))
                uartdev->tx = pSerialPinConfig->ioTagTx[device];
        }

        if (uartdev->rx || uartdev->tx) {
            uartdev->hardware = hardware;
            uartDevmap[device] = uartdev++;
        }
    }
}

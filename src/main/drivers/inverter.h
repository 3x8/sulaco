#pragma once

#if defined(INVERTER_PIN_UART1) || defined(INVERTER_PIN_UART2) || defined(INVERTER_PIN_UART3) || defined(INVERTER_PIN_UART4) || defined(INVERTER_PIN_UART5) || defined(INVERTER_PIN_UART6)
#define USE_INVERTER
#endif

#include "drivers/serial.h"

void initInverters(const serialPinConfig_t *serialPinConfigToUse);

void enableInverter(USART_TypeDef *USARTx, bool on);

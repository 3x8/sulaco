#pragma once

#if defined(STM32F1) || defined(STM32F3) || defined(STM32F4)
#define MAX_SPI_PIN_SEL 2
#else
#define MAX_SPI_PIN_SEL 4
#endif

typedef struct spiPinDef_s {
    ioTag_t pin;
#ifdef STM32F7
    uint8_t af;
#endif
} spiPinDef_t;

typedef struct spiHardware_s {
    SPIDevice device;
    SPI_TypeDef *reg;
    spiPinDef_t sckPins[MAX_SPI_PIN_SEL];
    spiPinDef_t misoPins[MAX_SPI_PIN_SEL];
    spiPinDef_t mosiPins[MAX_SPI_PIN_SEL];
#ifndef STM32F7
    uint8_t af;
#endif
    rccPeriphTag_t rcc;
#if defined(USE_HAL_DRIVER)
    uint8_t dmaIrqHandler;
#endif
} spiHardware_t;

extern const spiHardware_t spiHardware[];

typedef struct SPIDevice_s {
    SPI_TypeDef *dev;
    ioTag_t sck;
    ioTag_t miso;
    ioTag_t mosi;
#ifdef STM32F7
    uint8_t sckAF;
    uint8_t misoAF;
    uint8_t mosiAF;
#else
    uint8_t af;
#endif
    rccPeriphTag_t rcc;
    volatile uint16_t errorCount;
    bool leadingEdge;
#if defined(USE_HAL_DRIVER)
    SPI_HandleTypeDef hspi;
    DMA_HandleTypeDef hdma;
    uint8_t dmaIrqHandler;
#endif
} spiDevice_t;

extern spiDevice_t spiDevice[SPIDEV_COUNT];

void spiInitDevice(SPIDevice device);
uint32_t spiTimeoutUserCallback(SPI_TypeDef *instance);

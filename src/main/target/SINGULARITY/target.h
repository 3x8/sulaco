#pragma once

#define TARGET_BOARD_IDENTIFIER "SING"


#define LED0_PIN                PB3

#define USE_BEEPER
#define BEEPER_PIN              PC15

#define USE_EXTI
#define MPU_INT_EXTI            PC13
#define USE_MPU_DATA_READY_SIGNAL

#define USE_GYRO
#define USE_GYRO_MPU6050
#define GYRO_MPU6050_ALIGN      CW0_DEG_FLIP

#define USE_ACC
#define USE_ACC_MPU6050
#define ACC_MPU6050_ALIGN       CW0_DEG_FLIP

#define USE_FLASHFS
#define USE_FLASH_M25P16

#define USE_VCP
#define USE_UART1          // JST-SH Serial - TX (PA9) RX (PA10)
#define USE_UART2          // Input - TX (NC) RX (PA15)
#define USE_UART3          // Solder Pads - TX (PB10) RX (PB11)
#define USE_SOFTSERIAL1     // Telemetry
#define USE_SOFTSERIAL2

#define SERIAL_PORT_COUNT 6

#define USE_ESCSERIAL
#define ESCSERIAL_TIMER_TX_PIN  PA15  // (HARDARE=0,PPM)

#define UART1_TX_PIN            PA9
#define UART1_RX_PIN            PA10

#define UART2_TX_PIN            PA14 //Not connected
#define UART2_RX_PIN            PA15

#define UART3_TX_PIN            PB10
#define UART3_RX_PIN            PB11

#define SOFTSERIAL1_RX_PIN      PA2 //Not connected
#define SOFTSERIAL1_TX_PIN      PA3

#define USE_I2C
#define USE_I2C_DEVICE_1
#define I2C_DEVICE              (I2CDEV_1)

#define USE_SPI
#define USE_SPI_DEVICE_1 // PA4, 5, 6, 7
#define USE_SPI_DEVICE_2 // PB12,13,14,15 on AF5

#define USE_VTX_RTC6705

#define RTC6705_CS_PIN          PA4
#define RTC6705_SPI_INSTANCE    SPI1

#define FLASH_CS_PIN            PB12
#define FLASH_SPI_INSTANCE      SPI2

#define USE_ADC

#define ADC_INSTANCE            ADC2
#define VBAT_ADC_PIN            PB2
#define VBAT_SCALE_DEFAULT      77

#define ENABLE_BLACKBOX_LOGGING_ON_SPIFLASH_BY_DEFAULT

#define DEFAULT_RX_FEATURE      FEATURE_RX_SERIAL
#define SERIALRX_UART           SERIAL_PORT_USART2

// IO - stm32f303cc in 48pin package
#define TARGET_IO_PORTA         0xffff
#define TARGET_IO_PORTB         0xffff
#define TARGET_IO_PORTC         (BIT(13)|BIT(14)|BIT(15))
//#define TARGET_IO_PORTF (BIT(0)|BIT(1))
// !!TODO - check the following line is correct
#define TARGET_IO_PORTF         (BIT(0)|BIT(1)|BIT(3)|BIT(4))

#define USABLE_TIMER_CHANNEL_COUNT 10
#define USED_TIMERS             (TIM_N(1) | TIM_N(2) | TIM_N(3) | TIM_N(15) | TIM_N(16) |TIM_N(17))

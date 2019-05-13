#pragma once

// Treat the target as generic, and expect manufacturer id / board name
// to be supplied when the board is configured for the first time
#define GENERIC_TARGET

#define TARGET_BOARD_IDENTIFIER "S7X2"

#define USBD_PRODUCT_STRING     "S7X2"

#define USE_BEEPER

// MPU interrupt
#define USE_EXTI
#define USE_MPU_DATA_READY_SIGNAL
//#define DEBUG_MPU_DATA_READY_INTERRUPT
#define MPU_INT_EXTI PB15 // XXX Should be gone

#define USE_ACC
#define USE_GYRO

#define USE_ACC_SPI_MPU6500
#define USE_GYRO_SPI_MPU6500
// Other USE_ACCs and USE_GYROs should follow

// Should be gone
#define MPU6500_CS_PIN          PC4  // XXX Should be gone
#define MPU6500_SPI_INSTANCE    SPI1 // XXX Should be gone
#define ACC_MPU6500_ALIGN CW0_DEG
#define GYRO_MPU6500_ALIGN CW0_DEG


#define USE_MAG
#define USE_MAG_HMC5883
#define USE_MAG_QMC5883
#define MAG_HMC5883_ALIGN CW270_DEG_FLIP

#define USE_BARO
#define USE_BARO_MS5611
#define USE_BARO_BMP280
#define USE_BARO_LPS

#define USE_SDCARD

#define SDCARD_SPI_INITIALIZATION_CLOCK_DIVIDER 256 // 328kHz
#define SDCARD_SPI_FULL_SPEED_CLOCK_DIVIDER     4 // 21MHz

#define USE_I2C
#define USE_I2C_DEVICE_1
#define USE_I2C_DEVICE_2
#define USE_I2C_DEVICE_3
#define I2C_FULL_RECONFIGURABILITY

#define USE_VCP

#define USE_UART1
#define USE_UART2
#define USE_UART3
#define USE_UART4
#define USE_UART5
#define USE_UART6
#define USE_SOFTSERIAL1
#define USE_SOFTSERIAL2

#define SERIAL_PORT_COUNT       9

#define USE_ESCSERIAL

#define USE_SPI
#define USE_SPI_DEVICE_1
#define USE_SPI_DEVICE_2
#define USE_SPI_DEVICE_3
#define SPI_FULL_RECONFIGURABILITY

#define USE_ADC

#define TARGET_IO_PORTA 0xffff
#define TARGET_IO_PORTB 0xffff
#define TARGET_IO_PORTC 0xffff
#define TARGET_IO_PORTD 0xffff
#define TARGET_IO_PORTE 0xffff
#define TARGET_IO_PORTF 0xffff

#define USABLE_TIMER_CHANNEL_COUNT 70

#define USE_TIMER_MGMT

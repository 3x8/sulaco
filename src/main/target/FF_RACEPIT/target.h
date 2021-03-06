#pragma once
#define TARGET_BOARD_IDENTIFIER "RACE"
#define USBD_PRODUCT_STRING     "RacePit"
#define USE_TARGET_CONFIG

/*--------------LED----------------*/
#define LED0_PIN                PB5
#define LED1_PIN                PB4
/*---------------------------------*/

/*------------BEEPER---------------*/
#define USE_BEEPER
#define BEEPER_PIN              PB3
#define BEEPER_INVERTED
/*---------------------------------*/

/*---------- VTX POWER SWITCH---------*/
#define USE_PINIO
#define PINIO1_PIN              PB8 // VTX power switcher
#define USE_PINIOBOX

/*----------CAMERA CONTROL---------*/
#define CAMERA_CONTROL_PIN      PA10
/*---------------------------------*/

/*------------SENSORS--------------*/
// MPU interrupt
#define USE_EXTI
#define MPU_INT_EXTI            PC4

#define USE_MPU_DATA_READY_SIGNAL
#define ENSURE_MPU_DATA_READY_IS_LOW

#define USE_GYRO
#define USE_ACC

#define MPU6000_CS_PIN          SPI1_NSS_PIN
#define MPU6000_SPI_INSTANCE    SPI1

#define USE_GYRO_SPI_MPU6000
#define GYRO_MPU6000_ALIGN      CW90_DEG_FLIP

#define USE_ACC_SPI_MPU6000
#define ACC_MPU6000_ALIGN       CW90_DEG_FLIP
/*---------------------------------*/


/*-------------OSD-----------------*/
#define USE_MAX7456
#define MAX7456_SPI_INSTANCE    SPI2
#define MAX7456_SPI_CS_PIN      SPI2_NSS_PIN
#define MAX7456_SPI_CLK         (SPI_CLOCK_STANDARD) // 10MHz
#define MAX7456_RESTORE_CLK     (SPI_CLOCK_FAST)
/*---------------------------------*/

/*-----------USB-UARTs-------------*/
#define USE_VCP

#define USE_UART1
#define UART1_RX_PIN            PB7
#define UART1_TX_PIN            PA9

#define USE_UART2
#define UART2_RX_PIN            PA3
#define UART2_TX_PIN            PA2

#define USE_UART3
#define UART3_RX_PIN            PC11
#define UART3_TX_PIN            PC10
#define INVERTER_PIN_UART3      PC15

#define USE_UART4
#define UART4_TX_PIN            PA0
#define UART4_RX_PIN            PA1

#define USE_UART5
#define UART5_RX_PIN            PD2
#define UART5_TX_PIN            PC12

#define USE_UART6
#define UART6_RX_PIN            PC7
#define UART6_TX_PIN            PC6

#define SERIAL_PORT_COUNT       7
/*---------------------------------*/

/*-------------SPIs----------------*/
#define USE_SPI

#define USE_SPI_DEVICE_1
#define SPI1_NSS_PIN            PA4
#define SPI1_SCK_PIN            PA5
#define SPI1_MISO_PIN           PA6
#define SPI1_MOSI_PIN           PA7

#define USE_SPI_DEVICE_2
#define SPI2_NSS_PIN            PB12
#define SPI2_SCK_PIN            PB13
#define SPI2_MISO_PIN           PB14
#define SPI2_MOSI_PIN           PB15
/*---------------------------------*/

/*-------------I2C-----------------*/
#define USE_I2C
#define USE_I2C_PULLUP
#define USE_I2C_DEVICE_3
#define I2C_DEVICE              (I2CDEV_3)
#define I2C3_SCL                PA8
#define I2C3_SDA                PC9
/*---------------------------------*/

/*-------------ADCs----------------*/
#define USE_ADC
#define DEFAULT_VOLTAGE_METER_SOURCE    VOLTAGE_METER_ADC
#define DEFAULT_CURRENT_METER_SOURCE    CURRENT_METER_ADC
#define VBAT_ADC_PIN                    PC2
#define CURRENT_METER_ADC_PIN           PC1
/*---------------------------------*/

/*-------------ESCs----------------*/
#define USE_SERIAL_4WAY_BLHELI_INTERFACE
#define USE_ESCSERIAL
#define ESCSERIAL_TIMER_TX_PIN  PB0  // (HARDWARE=0)
/*---------------------------------*/

/*--------DEFAULT VALUES-----------*/
#define DEFAULT_RX_FEATURE      FEATURE_RX_SERIAL
#define SERIALRX_PROVIDER       SERIALRX_SBUS
#define SERIALRX_UART           SERIAL_PORT_USART3

#define TARGET_IO_PORTA         0xffff
#define TARGET_IO_PORTB         0xffff
#define TARGET_IO_PORTC         0xffff
#define TARGET_IO_PORTD         (BIT(2))
/*---------------------------------*/

/*--------------TIMERS-------------*/
#define USABLE_TIMER_CHANNEL_COUNT  6
#define USED_TIMERS             (TIM_N(1) | TIM_N(2) | TIM_N(3) | TIM_N(4) )
/*---------------------------------*/

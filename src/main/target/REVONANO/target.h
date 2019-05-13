#pragma once
#define TARGET_BOARD_IDENTIFIER "REVN"

#define USBD_PRODUCT_STRING "Revo Nano"
#ifdef OPBL
#define USBD_SERIALNUMBER_STRING "0x8010000"
#endif

#define LED0_PIN                PC14
#define LED1_PIN                PC13

#define USE_BEEPER
#define BEEPER_PIN              PC13

#define MPU6500_CS_PIN          PB12
#define MPU6500_SPI_INSTANCE    SPI2

#define USE_ACC
#define USE_ACC_MPU6500
#define USE_ACC_SPI_MPU6500
#define ACC_MPU6500_ALIGN       CW270_DEG

#define USE_GYRO
#define USE_GYRO_MPU6500
#define USE_GYRO_SPI_MPU6500
#define GYRO_MPU6500_ALIGN      CW270_DEG

#define USE_BARO
#define USE_BARO_MS5611

// MPU6500 interrupts
#define USE_EXTI
#define MPU_INT_EXTI            PA15
#define USE_MPU_DATA_READY_SIGNAL

#define USE_VCP
#define USE_USB_DETECT
//#define USB_DETECT_PIN          PA9

// The Flexi Port can be used for either UART1 or I2CDEV_1, see I2C section below
#define USE_UART1 // Flexi Port
#define UART1_RX_PIN            PB7
#define UART1_TX_PIN            PB6
#define PINIO1_PIN              PB10 // DTR pin

#define USE_UART2 // Main Port
#define UART2_RX_PIN            PA3
#define UART2_TX_PIN            PA2
#define INVERTER_PIN_UART2      PC15 //Sbus on USART 2 of nano.

#define USE_SOFTSERIAL1
#define USE_SOFTSERIAL2

#define SERIAL_PORT_COUNT       5

#define USE_ESCSERIAL
#define ESCSERIAL_TIMER_TX_PIN  PB10  // (HARDARE=0,PPM)

#define USE_SPI
#define USE_SPI_DEVICE_2

#define USE_I2C
/* The Flexi Port can be used for either UART1 or I2CDEV_1
 * I2C resources undefined by default
 * To use I2C use the following CLI commands:
 *   resource SERIAL_RX 1 NONE
 *   resource SERIAL_TX 1 NONE
 *   resource I2C1_SCL 1 PB6
 *   resource I2C1_SDA 1 PB7
 */
#define USE_I2C_DEVICE_1        // UART1/FlexiPort (PB6,PB7)
#define I2C_DEVICE              I2CDEV_1
#define I2C1_SCL                NONE // Define as PB6 if required
#define I2C1_SDA                NONE // Define as PB7 if required
#define USE_I2C_DEVICE_3
#define I2C3_SCL                PA8
#define I2C3_SDA                PB4
#define BARO_I2C_INSTANCE       I2CDEV_3

#undef USE_LED_STRIP

#define USE_ADC
#define CURRENT_METER_ADC_PIN   PA7
#define VBAT_ADC_PIN            PA6
#define RSSI_ADC_PIN            PA5

#define TARGET_IO_PORTA         0xffff
#define TARGET_IO_PORTB         0xffff
#define TARGET_IO_PORTC         (BIT(13) | BIT(14) | BIT(15))

#define USABLE_TIMER_CHANNEL_COUNT 12
#define USED_TIMERS             ( TIM_N(1) | TIM_N(2) | TIM_N(3) | TIM_N(4) | TIM_N(5) )

#pragma once

#define TARGET_BOARD_IDENTIFIER         "HESP"
#define USBD_PRODUCT_STRING             "HELIOMOD"
#define TARGET_MANUFACTURER_IDENTIFIER  "HESP"

#undef USE_BOARD_INFO

#define USE_TARGET_CONFIG

#define USE_DSHOT_DMAR
#define ENABLE_DSHOT_DMAR       true

#define LED0_PIN                PB7
#define USE_BEEPER
#define BEEPER_PIN              PC15
#define BEEPER_INVERTED

#define CAMERA_CONTROL_PIN      PB6

#define USE_BUTTERED_PIDS       true

#define DEFAULT_PIDS_ROLL   {27, 17, 37, 0}
#define DEFAULT_PIDS_PITCH  {27, 17, 37, 0}
#define DEFAULT_PIDS_YAW    {41, 51, 1, 0}

// EXTI ICM20601 allways 125us -> 8kHz (some lost at 250us ... at 16K and 32K gyro rate ... also)
//#define DEBUG_MPU_DATA_READY_INTERRUPT

// ICM20601
#define USE_GYRO_SPI_ICM20601

// ICM20602
#define USE_ACC
#define USE_GYRO

#define DEFAULT_ATTITUDE_UPDATE_INTERVAL 1000
#define DEFAULT_ACC_SAMPLE_INTERVAL      1000

#define USE_EXTI
#define MPU_INT_EXTI            PB0
#define USE_MPU_DATA_READY_SIGNAL
#define ENSURE_MPU_DATA_READY_IS_LOW

#define USE_ACC_MPU6500
#define USE_ACC_SPI_MPU6500
#define USE_GYRO_MPU6500
#define USE_GYRO_SPI_MPU6500

#define ACC_MPU6500_ALIGN       CW0_DEG
#define GYRO_MPU6500_ALIGN      CW0_DEG
#define MPU6500_SPI_INSTANCE    SPI1
#define MPU6500_CS_PIN          SPI1_NSS_PIN

// OSD
#define USE_MAX7456
#define MAX7456_SPI_INSTANCE    SPI3
#define MAX7456_SPI_CS_PIN      SPI3_NSS_PIN
#define MAX7456_SPI_CLK         (SPI_CLOCK_STANDARD) // 10MHz
#define MAX7456_RESTORE_CLK     (SPI_CLOCK_FAST)

// FLASH
#define FLASH_SPI_INSTANCE      SPI3
#define FLASH_CS_PIN            SPI3_NSS_PIN

#define USE_FLASH
#define USE_FLASH_M25P16
#define USE_FLASHFS

#define ENABLE_BLACKBOX_LOGGING_ON_SPIFLASH_BY_DEFAULT

// UARTS
#define USE_VCP

#define VBUS_SENSING_PIN        PC5
#define USE_UART1
#define UART1_RX_PIN            PA10
#define UART1_TX_PIN            PA9

#define USE_UART2
#define UART2_RX_PIN            PA3
#define UART2_TX_PIN            PA2

#define USE_UART3
#define UART3_RX_PIN            PB11
#define UART3_TX_PIN            PB10

#define USE_UART4
#define UART4_RX_PIN            PC11

#define USE_UART5
#define UART5_RX_PIN            PD2
#define UART5_TX_PIN            PC12

#define SERIAL_PORT_COUNT       6

#define USE_ESCSERIAL
#define ESCSERIAL_TIMER_TX_PIN  NONE

#define USE_SPI

#define USE_SPI_DEVICE_1
#define SPI1_NSS_PIN            PB1
#define SPI1_SCK_PIN            PB3
#define SPI1_MISO_PIN           PA6
#define SPI1_MOSI_PIN           PA7

#define USE_SPI_DEVICE_2
#define SPI2_NSS_PIN            PB12
#define SPI2_SCK_PIN            PB13
#define SPI2_MISO_PIN           PC2
#define SPI2_MOSI_PIN           PC3

#define USE_SPI_DEVICE_3
#define SPI3_NSS_PIN            PC14
#define SPI3_SCK_PIN            PC10
#define SPI3_MISO_PIN           PB4
#define SPI3_MOSI_PIN           PB5

#define USE_ADC
#define ADC_INSTANCE                  ADC1
#define DEFAULT_VOLTAGE_METER_SOURCE  VOLTAGE_METER_ADC
#define DEFAULT_CURRENT_METER_SOURCE  CURRENT_METER_ADC
#define CURRENT_METER_ADC_PIN         PA1
#define VBAT_ADC_PIN                  PA0
#define CURRENT_METER_SCALE_DEFAULT   250
#define VBAT_SCALE                    109

#define DEFAULT_RX_FEATURE      FEATURE_RX_SERIAL
#define SERIALRX_UART           SERIAL_PORT_USART3
#define SERIALRX_PROVIDER       SERIALRX_CRSF
#define DEFAULT_FEATURES        (FEATURE_TELEMETRY | FEATURE_AIRMODE)

#define USE_SERIAL_4WAY_BLHELI_INTERFACE

#define TARGET_IO_PORTA         0xffff
#define TARGET_IO_PORTB         0xffff
#define TARGET_IO_PORTC         0xffff
#define TARGET_IO_PORTD         (BIT(2))

#define USABLE_TIMER_CHANNEL_COUNT 7
#define USED_TIMERS             (TIM_N(1) | TIM_N(8) | TIM_N(4) | TIM_N(12))

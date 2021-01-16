#pragma once

#define TARGET_BOARD_IDENTIFIER         "X721"
#define USBD_PRODUCT_STRING             "CLRACINGF7V21"
#define TARGET_MANUFACTURER_IDENTIFIER  "CLR"

#undef USE_BOARD_INFO

#define USE_TARGET_CONFIG

#define USE_DSHOT_DMAR
#define ENABLE_DSHOT_DMAR       true

#define LED0_PIN                PB0
#define USE_BEEPER
#define BEEPER_PIN              PB4
#define BEEPER_INVERTED

#define CAMERA_CONTROL_PIN      PB3

#define USE_BUTTERED_PIDS       true

#define DEFAULT_PIDS_ROLL   {27, 17, 37, 0}
#define DEFAULT_PIDS_PITCH  {27, 17, 37, 0}
#define DEFAULT_PIDS_YAW    {41, 51, 1, 0}

#define DEFAULT_ATTITUDE_UPDATE_INTERVAL 1000
#define DEFAULT_ACC_SAMPLE_INTERVAL      1000

#define USE_DUAL_GYRO
#define USE_EXTI
#define MPU_INT_EXTI
#define USE_GYRO_EXTI

#define GYRO_1_EXTI_PIN         PC4
#define GYRO_2_EXTI_PIN         PC14
#define USE_MPU_DATA_READY_SIGNAL
#define ENSURE_MPU_DATA_READY_IS_LOW
//#define DEBUG_MPU_DATA_READY_INTERRUPT
// EXTI ICM20601 allways 125us -> 8kHz (some lost at 250us ... at 16K and 32K gyro rate ... also)

#define USE_ACC
#define USE_GYRO

// ICM20601
#define USE_GYRO_SPI_ICM20601

//MPU-6000
#define USE_ACC_SPI_MPU6000
#define USE_GYRO_SPI_MPU6000

// ICM-20602
#define USE_ACC_SPI_MPU6500
#define USE_GYRO_SPI_MPU6500

#define GYRO_1_CS_PIN           PA4
#define GYRO_1_SPI_INSTANCE     SPI1
#define GYRO_1_ALIGN            CW0_DEG
#define ACC_1_ALIGN             CW0_DEG

#define GYRO_2_CS_PIN           PC13
#define GYRO_2_SPI_INSTANCE     SPI1
#define GYRO_2_ALIGN            CW90_DEG
#define ACC_2_ALIGN             CW90_DEG

// OSD
#define USE_MAX7456
#define MAX7456_SPI_INSTANCE    SPI3
#define MAX7456_SPI_CS_PIN      SPI3_NSS_PIN
#define MAX7456_SPI_CLK         (SPI_CLOCK_STANDARD)
#define MAX7456_RESTORE_CLK     (SPI_CLOCK_FAST)

// FLASH
#define FLASH_SPI_INSTANCE      SPI2
#define FLASH_CS_PIN            SPI2_NSS_PIN

#define USE_FLASH
#define USE_FLASH_W25N01G
#define USE_FLASHFS
#define ENABLE_BLACKBOX_LOGGING_ON_SPIFLASH_BY_DEFAULT

// UARTS
#define USE_VCP

#define USE_UART1
#define UART1_TX_PIN            PA9
#define UART1_RX_PIN            PA10

#define USE_UART2
#define UART2_TX_PIN            PA2
#define UART2_RX_PIN            PA3

#define USE_UART3
#define UART3_TX_PIN            PB10
#define UART3_RX_PIN            PB11

#define USE_UART4
#define UART4_TX_PIN            PA0
#define UART4_RX_PIN            PA1

#define USE_UART5
#define UART5_TX_PIN            PC12
#define UART5_RX_PIN            PD2

#define USE_UART6
#define UART6_TX_PIN            PC6
#define UART6_RX_PIN            PC7

#define SERIAL_PORT_COUNT       7

#define USE_ESCSERIAL

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

#define USE_SPI_DEVICE_3
#define SPI3_NSS_PIN            PA15
#define SPI3_SCK_PIN            PC10
#define SPI3_MISO_PIN           PC11
#define SPI3_MOSI_PIN           PB5

#define USE_ADC
#define ADC_INSTANCE                  ADC1
#define DEFAULT_VOLTAGE_METER_SOURCE  VOLTAGE_METER_ADC
#define DEFAULT_CURRENT_METER_SOURCE  CURRENT_METER_ADC
#define CURRENT_METER_ADC_PIN         PC1
#define VBAT_ADC_PIN                  PC2
#define RSSI_ADC_PIN                  PC3
#define CURRENT_METER_SCALE_DEFAULT   250                     // 3.3/120A  = 25mv/A

#define BINDPLUG_PIN            PB2
#define DEFAULT_RX_FEATURE      FEATURE_RX_SERIAL
#define SERIALRX_UART           SERIAL_PORT_UART5

#define USE_SERIAL_4WAY_BLHELI_INTERFACE

#define TARGET_IO_PORTA         0xffff
#define TARGET_IO_PORTB         0xffff
#define TARGET_IO_PORTC         0xffff
#define TARGET_IO_PORTD         (BIT(2))

#define USABLE_TIMER_CHANNEL_COUNT 6
#define USED_TIMERS             (TIM_N(2) | TIM_N(3) | TIM_N(4))

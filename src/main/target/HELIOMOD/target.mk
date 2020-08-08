
F405_TARGETS   += $(TARGET)
FEATURES       += VCP ONBOARDFLASH
TARGET_SRC =  \
            stm32f4xx_crc.c \
            drivers/accgyro/accgyro_mpu.c \
            drivers/accgyro/accgyro_mpu6500.c \
            drivers/accgyro/accgyro_spi_mpu6500.c \
            drivers/accgyro/accgyro_spi_mpu6000.c \
             drivers/max7456.c

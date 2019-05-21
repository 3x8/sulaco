#pragma once

// Registers
#define MPU3050_SMPLRT_DIV      0x15
#define MPU3050_DLPF_FS_SYNC    0x16
#define MPU3050_INT_CFG         0x17
#define MPU3050_TEMP_OUT        0x1B
#define MPU3050_GYRO_OUT        0x1D
#define MPU3050_USER_CTRL       0x3D
#define MPU3050_PWR_MGM         0x3E

bool mpu3050Detect(gyroDev_t *gyro);

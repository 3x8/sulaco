#pragma once

#define BST_BUFFER_SIZE                              128

#define I2C_ADDR_TBS_CORE_PNP_PRO                    0x80
#define I2C_ADDR_RESERVED                            0x8A
#define I2C_ADDR_PNP_PRO_DIDITAL_CURRENT_SENSOR      0xC0
#define I2C_ADDR_PNP_PRO_GPS                         0xC2
#define I2C_ADDR_TSB_BLACKBOX                        0xC4
#define I2C_ADDR_CROSSFIRE_UHF_RECEIVER              0xEC
#define I2C_ADDR_CLEANFLIGHT_FC                      0xC8

typedef enum BSTDevice {
    BSTDEV_1,
    BSTDEV_2
} BSTDevice;

void bstInit(BSTDevice index);
uint32_t bstTimeoutUserCallback(void);
uint16_t bstGetErrorCounter(void);

bool bstWriteBusy(void);
bool bstMasterWrite(uint8_t* data);
bool bstSlaveRead(uint8_t* buf);
bool bstSlaveWrite(uint8_t* data);

void bstMasterWriteLoop(void);

void crc8Cal(uint8_t data_in);

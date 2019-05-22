#pragma once

uint8_t Stk_SignOn(void);
uint8_t Stk_ConnectEx(uint8_32_u *pDeviceInfo);
uint8_t Stk_ReadEEprom(ioMem_t *pMem);
uint8_t Stk_WriteEEprom(ioMem_t *pMem);
uint8_t Stk_ReadFlash(ioMem_t *pMem);
uint8_t Stk_WriteFlash(ioMem_t *pMem);
uint8_t Stk_Chip_Erase(void);

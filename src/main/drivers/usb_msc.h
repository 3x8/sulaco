#pragma once

#define MSC_MAGIC 0xDDDD1010

void mscInit(void);
bool mscCheckBoot(void);
uint8_t mscStart(void);
bool mscCheckButton(void);
void mscWaitForButton(void);
void systemResetToMsc(void);
void systemResetFromMsc(void);

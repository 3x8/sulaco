#pragma once

#include <stdint.h>
#include <stdbool.h>

#define EEPROM_CONF_VERSION 172

bool isEEPROMVersionValid(void);
bool isEEPROMStructureValid(void);
bool loadEEPROM(void);
void writeConfigToEEPROM(void);
uint16_t getEEPROMConfigSize(void);

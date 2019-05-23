#pragma once

#include "flash_impl.h"

#define JEDEC_ID_WINBOND_W25Q256       0xEF4019

bool m25p16_detect(flashDevice_t *fdevice, uint32_t chipID);

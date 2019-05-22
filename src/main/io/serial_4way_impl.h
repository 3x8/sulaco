#pragma once

#include "drivers/io_types.h"

typedef struct {
    IO_t io;
} escHardware_t;

extern uint8_t selected_esc;

bool isEscHi(uint8_t selEsc);
bool isEscLo(uint8_t selEsc);
void setEscHi(uint8_t selEsc);
void setEscLo(uint8_t selEsc);
void setEscInput(uint8_t selEsc);
void setEscOutput(uint8_t selEsc);

#define ESC_IS_HI  isEscHi(selected_esc)
#define ESC_IS_LO  isEscLo(selected_esc)
#define ESC_SET_HI setEscHi(selected_esc)
#define ESC_SET_LO setEscLo(selected_esc)
#define ESC_INPUT  setEscInput(selected_esc)
#define ESC_OUTPUT setEscOutput(selected_esc)

typedef struct ioMem_s {
    uint8_t D_NUM_BYTES;
    uint8_t D_FLASH_ADDR_H;
    uint8_t D_FLASH_ADDR_L;
    uint8_t *D_PTR_I;
} ioMem_t;

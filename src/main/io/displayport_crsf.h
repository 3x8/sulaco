#pragma once

#include "drivers/display.h"

#define CRSF_DISPLAY_PORT_ROWS_MAX          9
#define CRSF_DISPLAY_PORT_COLS_MAX          32
#define CRSF_DISPLAY_PORT_MAX_BUFFER_SIZE   (CRSF_DISPLAY_PORT_ROWS_MAX * CRSF_DISPLAY_PORT_COLS_MAX)

typedef struct crsfDisplayPortScreen_s {
    char buffer[CRSF_DISPLAY_PORT_MAX_BUFFER_SIZE];
    bool pendingTransport[CRSF_DISPLAY_PORT_ROWS_MAX];
    uint8_t rows;
    uint8_t cols;
    bool reset;
} crsfDisplayPortScreen_t;

struct displayPort_s;
struct displayPort_s *displayPortCrsfInit(void);
crsfDisplayPortScreen_t *crsfDisplayPortScreen(void);
void crsfDisplayPortMenuOpen(void);
void crsfDisplayPortMenuExit(void);
void crsfDisplayPortRefresh(void);
int crsfDisplayPortNextRow(void);
void crsfDisplayPortSetDimensions(uint8_t rows, uint8_t cols);

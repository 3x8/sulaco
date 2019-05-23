#pragma once

#include "drivers/bus.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define FONT_WIDTH 5
#define FONT_HEIGHT 7
#define HORIZONTAL_PADDING 1
#define VERTICAL_PADDING 1

#define CHARACTER_WIDTH_TOTAL (FONT_WIDTH + HORIZONTAL_PADDING)
#define CHARACTER_HEIGHT_TOTAL (FONT_HEIGHT + VERTICAL_PADDING)

#define SCREEN_CHARACTER_COLUMN_COUNT (SCREEN_WIDTH / CHARACTER_WIDTH_TOTAL)
#define SCREEN_CHARACTER_ROW_COUNT (SCREEN_HEIGHT / CHARACTER_HEIGHT_TOTAL)

#define VERTICAL_BARGRAPH_ZERO_CHARACTER (128 + 32)
#define VERTICAL_BARGRAPH_CHARACTER_COUNT 7

bool ug2864hsweg01InitI2C(busDevice_t *bus);

void i2c_OLED_set_xy(busDevice_t *bus, uint8_t col, uint8_t row);
void i2c_OLED_set_line(busDevice_t *bus, uint8_t row);
void i2c_OLED_send_char(busDevice_t *bus, unsigned char ascii);
void i2c_OLED_send_string(busDevice_t *bus, const char *string);
void i2c_OLED_clear_display(busDevice_t *bus);
void i2c_OLED_clear_display_quick(busDevice_t *bus);

#include "stdint.h"

#include "color.h"
#include "colorconversion.h"

/*
 * Source below found here: http://www.kasperkamperman.com/blog/arduino/arduino-programming-hsb-to-rgb/
 */

rgbColor24bpp_t* hsvToRgb24(const hsvColor_t* c)
{
    static rgbColor24bpp_t r;

    uint16_t val = c->v;
    uint16_t sat = 255 - c->s;
    uint32_t base;
    uint16_t hue = c->h;

    if (sat == 0) { // Acromatic color (gray). Hue doesn't mind.
        r.rgb.r = val;
        r.rgb.g = val;
        r.rgb.b = val;
    } else {

        base = ((255 - sat) * val) >> 8;

        switch (hue / 60) {
            case 0:
            r.rgb.r = val;
            r.rgb.g = (((val - base) * hue) / 60) + base;
            r.rgb.b = base;
            break;
            case 1:
            r.rgb.r = (((val - base) * (60 - (hue % 60))) / 60) + base;
            r.rgb.g = val;
            r.rgb.b = base;
            break;

            case 2:
            r.rgb.r = base;
            r.rgb.g = val;
            r.rgb.b = (((val - base) * (hue % 60)) / 60) + base;
            break;

            case 3:
            r.rgb.r = base;
            r.rgb.g = (((val - base) * (60 - (hue % 60))) / 60) + base;
            r.rgb.b = val;
            break;

            case 4:
            r.rgb.r = (((val - base) * (hue % 60)) / 60) + base;
            r.rgb.g = base;
            r.rgb.b = val;
            break;

            case 5:
            r.rgb.r = val;
            r.rgb.g = base;
            r.rgb.b = (((val - base) * (60 - (hue % 60))) / 60) + base;
            break;

        }
    }
    return &r;
}

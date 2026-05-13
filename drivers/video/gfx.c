#include "gfx.h"
#include <stdint.h>

void putpixel(int x, int y, uint32_t color)
{
    uint8_t* row = (uint8_t*)framebuffer + (y * fbPitch);
    uint32_t* pixel = (uint32_t*)(row + (x * 4));
    *pixel = color;
}

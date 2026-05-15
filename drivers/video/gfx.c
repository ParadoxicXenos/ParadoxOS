#include "gfx.h"
#include <stdint.h>

void putpixel(int x, int y, uint32_t color)
{
    framebuffer[y * (fbPitch / 4) + x] = color;
}
void fillrect(uint8_t *vram,
                     uint8_t r, uint8_t g, uint8_t b,
                     uint32_t x, uint32_t y,
                     uint32_t w, uint32_t h)
{
    uint32_t *pixel;
    uint32_t color = (r << 16) | (g << 8) | b;

    for (uint32_t j = 0; j < h; j++) {

        // go to start of row
        pixel = (uint32_t *)(vram + (y + j) * fbPitch + x * 4);

        for (uint32_t i = 0; i < w; i++) {
            pixel[i] = color;
        }
    }
}
void clearScreen(){
fillrect((uint8_t*)framebuffer,
         0, 0, 0,
         0, 0,
         640, 480);

}


extern uint8_t threeDfx[4096];

void drawchar(unsigned char c, int x, int y, uint8_t r, uint8_t g, uint8_t b)
{
    uint32_t color = (r << 16) | (g << 8) | b;
    uint8_t *glyph = threeDfx + c * 16;

    for (int cy = 0; cy < 16; cy++) {
        for (int cx = 0; cx < 8; cx++) {
            if (glyph[cy] & (0x80 >> cx)) {
                putpixel(x + cx, y + cy, color);
            }
        }
    }
}
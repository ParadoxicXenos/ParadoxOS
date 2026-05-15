#include <stdint.h>
extern void removeLastChar(char str[80]);
extern void putpixel(int x, int y, uint32_t color);
extern void fillrect(uint8_t *vram,
                     uint8_t r, uint8_t g, uint8_t b,
                     uint32_t x, uint32_t y,
                     uint32_t w, uint32_t h);
extern void clearScreen();
#include <stdint.h>
extern void removeLastChar(char str[80]);
extern void putpixel(int x, int y, uint32_t color);
extern void fillrect(uint8_t *vram,
                     uint8_t r, uint8_t g, uint8_t b,
                     uint32_t x, uint32_t y,
                     uint32_t w, uint32_t h);
extern void clearScreen();
extern void print(char chars[]);
extern void clearChar(int row, int col);
extern void drawchar(unsigned char c, int x, int y,uint8_t r, uint8_t g, uint8_t b);
extern void putString(char str[80], int row);
extern void putStringl(char str[80], int row);
extern void newLine();
extern void prompt(int row);
char translate(uint8_t scancode);
extern void splash();
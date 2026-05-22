#include "gfx.h"
#include <stdint.h>
extern void stringCopy(char *dest, char *src);
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define CHAR_WIDTH 8
#define CHAR_HEIGHT 16
#define COLS (SCREEN_WIDTH / CHAR_WIDTH)   // 80
#define ROWS (SCREEN_HEIGHT / CHAR_HEIGHT) // 30
extern uint32_t *framebuffer;
extern uint32_t fbPitch;
extern uint8_t threeDfx[4096];
void putArgbString(char *str, int r, int g, int b);
int red = 255;
int blue = 255;
int green = 255;
void prompt(int row);
void newLine(void);
struct colors {
  int r;
  int g;
  int b;
  char name[80];
};

struct colors colorList[9];

struct colors colorList[9] = {
    {47, 54, 153, "PURPLE"},
    {32, 107, 29, "GREEN"},
    {26, 128, 184, "BLUE"},
    {235, 146, 52, "ORANGE"},
    {235, 207, 52, "YELLOW"},
    {232, 30, 30, "RED"},
    {111, 227, 175, "MINT"},
    {255, 255, 255, "WHITE"},
    {255, 128, 234, "PINK"}
};


void putpixel(int x, int y, uint32_t color) {
  if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
    return;

  framebuffer[y * (fbPitch / 4) + x] = color;
}

/* =========================================
   RECTANGLES
   ========================================= */

void fillrect(uint8_t *vram, uint8_t r, uint8_t g, uint8_t b, uint32_t x,
              uint32_t y, uint32_t w, uint32_t h) {
  uint32_t color = (r << 16) | (g << 8) | b;

  for (uint32_t j = 0; j < h; j++) {
    uint32_t *pixel = (uint32_t *)(vram + ((y + j) * fbPitch) + (x * 4));

    for (uint32_t i = 0; i < w; i++) {
      pixel[i] = color;
    }
  }
}

/* =========================================
   SCREEN
   ========================================= */

void clearScreen(void) {
  fillrect((uint8_t *)framebuffer, 0, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

  cursorRow = 0;
  cursorCol = 0;

  prompt(cursorRow);
}

/* =========================================
   CHARACTER DRAWING
   ========================================= */

void drawchar(unsigned char c, int x, int y, uint8_t r, uint8_t g, uint8_t b) {
  uint32_t color = (r << 16) | (g << 8) | b;

  uint8_t *glyph = threeDfx + ((unsigned char)c * 16);

  for (int cy = 0; cy < CHAR_HEIGHT; cy++) {
    for (int cx = 0; cx < CHAR_WIDTH; cx++) {
      if (glyph[cy] & (0x80 >> cx)) {
        putpixel(x + cx, y + cy, color);
      }
    }
  }
}

/* =========================================
   CURSOR
   ========================================= */

void newLine(void) {
  cursorRow++;
  cursorCol = 0;

  if (cursorRow >= ROWS) {
    clearScreen();
    cursorRow = 0;
  }
}

/* =========================================
   STRINGS
   ========================================= */

void putString(char *str) {
  for (int i = 0; str[i] != '\0'; i++) {
    drawchar(str[i], cursorCol * CHAR_WIDTH, cursorRow * CHAR_HEIGHT, red, green,blue);

    cursorCol++;
  }
}
void putArgbInt(int num,int r,int g,int b) {
    char buffer[16];
    int i = 0;

    if (num == 0) {
        putArgbString("0",r,g,b);
        return;
    }

    while (num > 0) {
        buffer[i] = (num % 10) + '0';
        i++;
        num /= 10;
    }

    buffer[i] = '\0';

    // reverse
    for (int j = 0; j < i/2; j++) {
        char temp = buffer[j];
        buffer[j] = buffer[i-1-j];
        buffer[i-1-j] = temp;
    }

    putArgbString(buffer,r,g,b);
    newLine();
}

void putArgbString(char *str, int r, int g, int b) {
  for (int i = 0; str[i] != '\0'; i++) {
    drawchar(str[i], cursorCol * CHAR_WIDTH, cursorRow * CHAR_HEIGHT, r, g,b);

    cursorCol++;
  }
}
void putArgbStringl(char *str,int r,int g, int b) {
  putArgbString(str,r,g,b);
  newLine();
}

void putStringl(char *str) {
  putString(str);
  newLine();
}

/* =========================================
   CLEAR CHARACTER CELL
   ========================================= */

void clearChar(int row, int col) {
  fillrect((uint8_t *)framebuffer, 0, 0, 0, col * CHAR_WIDTH, row * CHAR_HEIGHT,
           CHAR_WIDTH, CHAR_HEIGHT);
}

/* =========================================
   PROMPT
   ========================================= */

void prompt(int row) {
  cursorRow = row;
  cursorCol = 0;

  putString(">  ");

  cursorCol = 2;
}
void splash() {
  // P
  fillrect((uint8_t *)framebuffer, red, green, blue, 1, 1, 30, 24);
  fillrect((uint8_t *)framebuffer, 0, 0, 0, 11, 4, 10, 18);
  fillrect((uint8_t *)framebuffer, red, green, blue, 1, 25, 10, 11);
  // A
  fillrect((uint8_t *)framebuffer, red, green, blue, 33, 8, 21, 28);
  fillrect((uint8_t *)framebuffer, 0, 0, 0, 41, 11, 5, 11);
  fillrect((uint8_t *)framebuffer, 0, 0, 0, 41, 25, 5, 11);
  // R
  fillrect((uint8_t *)framebuffer, red, green, blue, 56, 8, 21, 28);
  fillrect((uint8_t *)framebuffer, 0, 0, 0, 64, 11, 5, 11);
  fillrect((uint8_t *)framebuffer, 0, 0, 0, 64, 25, 5, 11);
  fillrect((uint8_t *)framebuffer, 0, 0, 0, 74, 27, 3, 4);
  // A
  fillrect((uint8_t *)framebuffer, red, green, blue, 79, 8, 21, 28);
  fillrect((uint8_t *)framebuffer, 0, 0, 0, 87, 11, 5, 11);
  fillrect((uint8_t *)framebuffer, 0, 0, 0, 87, 25, 5, 11);
  // D
  fillrect((uint8_t *)framebuffer, red, green, blue, 102, 8, 21, 28);
  fillrect((uint8_t *)framebuffer, 0, 0, 0, 119, 8, 4, 4);
  fillrect((uint8_t *)framebuffer, 0, 0, 0, 119, 32, 4, 4);
  fillrect((uint8_t *)framebuffer, 0, 0, 0, 108, 11, 7, 22);
  // O
  fillrect((uint8_t *)framebuffer, red, green, blue, 125, 8, 21, 28);
  fillrect((uint8_t *)framebuffer, 0, 0, 0, 133, 11, 5, 22);
  // X
  fillrect((uint8_t *)framebuffer, red, green, blue, 148, 8, 21, 28);
  fillrect((uint8_t *)framebuffer, 0, 0, 0, 156, 8, 5, 12);
  fillrect((uint8_t *)framebuffer, 0, 0, 0, 157, 20, 3, 2);
  fillrect((uint8_t *)framebuffer, 0, 0, 0, 157, 25, 3, 3);
  fillrect((uint8_t *)framebuffer, 0, 0, 0, 156, 28, 5, 8);
  fillrect((uint8_t *)framebuffer, 0, 0, 0, 148, 20, 1, 8);
  fillrect((uint8_t *)framebuffer, 0, 0, 0, 149, 22, 1, 4);
  fillrect((uint8_t *)framebuffer, 0, 0, 0, 168, 20, 1, 8);
  fillrect((uint8_t *)framebuffer, 0, 0, 0, 167, 22, 1, 4);
  // O
  fillrect((uint8_t *)framebuffer, red, green, blue, 171, 1, 30, 35);
  fillrect((uint8_t *)framebuffer, 0, 0, 0, 181, 4, 10, 29);
  // S
  fillrect((uint8_t *)framebuffer, red, green, blue, 203, 1, 30, 35);
  fillrect((uint8_t *)framebuffer, 0, 0, 0, 213, 4, 20, 18);
  fillrect((uint8_t *)framebuffer, 0, 0, 0, 203, 25, 20, 8);
  cursorCol = 0;
  cursorRow = 3;
}
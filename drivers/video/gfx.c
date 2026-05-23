#include "apple.h"
#include "rick.h"
#include "gfx.h"
#include <stdint.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define CHAR_WIDTH 8
#define CHAR_HEIGHT 16
#define COLS (SCREEN_WIDTH / CHAR_WIDTH)   // 80
#define ROWS (SCREEN_HEIGHT / CHAR_HEIGHT) // 30
const uint32_t rick_frame_count = 96;
const uint32_t rick_frame_width = 80;
const uint32_t rick_frame_height = 60;
const uint32_t apple_frame_width = 80;
const uint32_t apple_frame_height = 60;

struct colors {
  int r;
  int g;
  int b;
  char name[80];
};

struct colors colorList[10];

struct colors colorList[10] = {
    {115, 99, 255, "PURPLE"},
    {0, 255, 0, "GREEN"},     
    {0, 128, 255, "BLUE"},
    {235, 146, 52, "ORANGE"}, 
    {255, 221, 0, "YELLOW"},  
    {255, 0, 0, "RED"},
    {111, 227, 175, "MINT"},  
    {255, 255, 255, "WHITE"}, 
    {255, 128, 234, "PINK"},
    {221, 0, 255, "MAGENTA"}};


void putpixel(int x, int y, uint32_t color) {
  if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
    return;

  framebuffer[y * (fbPitch / 4) + x] = color;
}


void argbputpixel(int x, int y, int r, int g, int b) {
  uint32_t color = (r << 16) | (g << 8) | b;
  putpixel(x, y, color);
}
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

void putString(char *str) {
  for (int i = 0; str[i] != '\0'; i++) {
    drawchar(str[i], cursorCol * CHAR_WIDTH, cursorRow * CHAR_HEIGHT, red, green, blue);

    cursorCol++;
  }
}

void putArgbString(char *str, int r, int g, int b);
int red = 255;
int blue = 255;
int green = 255;
void prompt(int row);
void newLine(void);

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

void clearScreen() {
  fillrect((uint8_t *)framebuffer, 0, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

  cursorRow = 0;
  cursorCol = 0;

  prompt(cursorRow);
}

void newLine() {
  cursorRow++;
  cursorCol = 0;

  if (cursorRow >= ROWS) {
    clearScreen();
    cursorRow = 0;
  }
}

void putArgbInt(int num, int r, int g, int b) {
  char buffer[16];
  int i = 0;

  if (num == 0) {
    putArgbString("0", r, g, b);
    return;
  }

  while (num > 0) {
    buffer[i] = (num % 10) + '0';
    i++;
    num /= 10;
  }

  buffer[i] = '\0';

  for (int j = 0; j < i / 2; j++) {
    char temp = buffer[j];
    buffer[j] = buffer[i - 1 - j];
    buffer[i - 1 - j] = temp;
  }

  putArgbString(buffer, r, g, b);
  newLine();
}

void putArgbString(char *str, int r, int g, int b) {
  for (int i = 0; str[i] != '\0'; i++) {
    drawchar(str[i], cursorCol * CHAR_WIDTH, cursorRow * CHAR_HEIGHT, r, g, b);

    cursorCol++;
  }
}
void putArgbStringl(char *str, int r, int g, int b) {
  putArgbString(str, r, g, b);
  newLine();
}

void putStringl(char *str) {
  putString(str);
  newLine();
}

void clearChar(int row, int col) {
  fillrect((uint8_t *)framebuffer, 0, 0, 0, col * CHAR_WIDTH, row * CHAR_HEIGHT,
           CHAR_WIDTH, CHAR_HEIGHT);
}

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
void wait_ms(uint32_t ms) {
  while (ms--) {
    for (volatile uint32_t i = 0; i < 5000; i++) {
      __asm__ volatile("nop");
    }
  }
}

void playBigRick() {
  for (int f = 0; f < rick_frame_count; f++) {
    wait_ms(5000);
    clearScreen();
    uint8_t *frame = (uint8_t *)&rick_video_blob[rick_frame_offsets[f]];
    for (int y = 0; y < 60; y++) {
      for (int x = 0; x < 80; x++) {
        int pixel_index = y * 80 + x;
        int byte_index = pixel_index / 8;
        int bit_index = 7 - (x % 8);
        int pixel = (frame[byte_index] >> bit_index) & 1;
        int biggerx = (12 * x) + 160;
        int biggery = 12 * y;
        if (pixel) {
          fillrect((uint8_t *)framebuffer, red, green, blue, biggerx, biggery,
                   12, 12);
        } else {
          fillrect((uint8_t *)framebuffer, 0, 0, 0, biggerx, biggery, 12, 12);
        }
      }
    }
  }
}
void playApple() {
  for (int f = 0; f < apple_frame_count; f++) {
    wait_ms(4000);
    clearScreen();
    uint8_t *frame = (uint8_t *)&apple_video_blob[apple_frame_offsets[f]];
    for (int y = 0; y < 60; y++) {
      for (int x = 0; x < 80; x++) {
        int pixel_index = y * 80 + x;
        int byte_index = pixel_index / 8;
        int bit_index = 7 - (x % 8);
        int pixel = (frame[byte_index] >> bit_index) & 1;
        int biggerx = (12 * x) + 160;
        int biggery = 12 * y;
        if (pixel) {
          fillrect((uint8_t *)framebuffer, red, green, blue, biggerx, biggery,
                   12, 12);
        } else {
          fillrect((uint8_t *)framebuffer, 0, 0, 0, biggerx, biggery, 12, 12);
        }
      }
    }
  }
}
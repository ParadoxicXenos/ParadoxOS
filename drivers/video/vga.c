#include <stdint.h>
#include "vga.h"

int cursorRow = 0;
int cursorCol = 0;

void print(const char chars[]) {
  uint16_t *v_mem = (uint16_t *)0xB8000;

  for (int i = 0; chars[i] != '\0'; i++) {
    int cursor_pos = cursorRow * 80 + cursorCol;

    v_mem[cursor_pos] = (0x09 << 8) | (chars[i] & 0xFF);

    cursorCol++;

    if (cursorCol >= 80) {
      cursorCol = 0;
      cursorRow++;
    }

    if (cursorRow >= 25) {
      scroll();
    }
  }
}

void newLine() {
  cursorRow++;
  cursorCol = 0;

  if (cursorRow >= 25) {
    scroll();
  }
}

void printLine(const char chars[]) {
  print(chars);
  newLine();
}

void clearLine(int x) {
  uint16_t *v_mem = (uint16_t *)0xB8000;

  for (int y = 0; y < 80; y++) {
    v_mem[x * 80 + y] = (0x09 << 8) | ' ';
  }
}

void clearScreen() {
  for (int y = 0; y < 25; y++) {
    clearLine(y);
  }

  cursorRow = 0;
  cursorCol = 0;
}

void scroll() {
  uint16_t *v_mem = (uint16_t *)0xB8000;

  for (int i = 1; i < 25; i++) {
    for (int x = 0; x < 80; x++) {
      v_mem[(i - 1) * 80 + x] = v_mem[i * 80 + x];
    }
  }

  clearLine(24);
  cursorRow = 24;
  cursorCol = 0;
}

void splash() {
  printLine("______                   _           _____ _____ ");
  printLine("| ___ \\                 | |         |  _  /  ___|");
  printLine("| |_/ /_ _ _ __ __ _  __| | _____  _| | | \\ `--. ");
  printLine("|  __/ _` | '__/ _` |/ _` |/ _ \\ \\/ / | | |`--. \\");
  printLine("| | | (_| | | | (_| | (_| | (_) >  <\\ \\_/ /\\__/ /");
  printLine("\\_|  \\__,_|_|  \\__,_|\\__,_|\\___/_/\\_\\\\___/\\____/");
  printLine("Hello, world!");
  printLine("This program was made by ParadoxicXenos");
}
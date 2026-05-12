#include "input.h"

char inputString[80];

void addChar(char *s, char c) {
  while (*s)
    s++;

  *s = c;
  s++;

  *s = '\0';
}

void readLine() {
  uint16_t *v_mem = (uint16_t *)0xB8000;
  line[0] = '\0';

  for (int y = 3; y < cursorCol; y++) {
    char letter = v_mem[cursorRow * 80 + y] & 0xFF;

    addChar(line, letter);
  }
}
#include <stdint.h>

#include "../../core/input/input.h"
#include "../../drivers/keyboard/keyboard.h"

static inline uint8_t inb(uint16_t port) {
  uint8_t ret;
  __asm__ volatile("inb %w1, %b0" : "=a"(ret) : "Nd"(port) : "memory");
  return ret;
}

uint8_t readPs2Port() {
  while ((inb(0x64) & 1))
    ;

  return inb(0x60);
}

char translate(char scancode) {
  if (scancode == 0x1E) {
    addChar(inputString, 'A');
    return 'A';
  }

  if (scancode == 0x30) {
    addChar(inputString, 'B');
    return 'B';
  }

  if (scancode == 0x2E) {
    addChar(inputString, 'C');
    return 'C';
  }

  if (scancode == 0x20) {
    addChar(inputString, 'D');
    return 'D';
  }

  if (scancode == 0x12) {
    addChar(inputString, 'E');
    return 'E';
  }

  if (scancode == 0x21) {
    addChar(inputString, 'F');
    return 'F';
  }

  if (scancode == 0x22) {
    addChar(inputString, 'G');
    return 'G';
  }

  if (scancode == 0x23) {
    addChar(inputString, 'H');
    return 'H';
  }

  if (scancode == 0x17) {
    addChar(inputString, 'I');
    return 'I';
  }

  if (scancode == 0x24) {
    addChar(inputString, 'J');
    return 'J';
  }

  if (scancode == 0x25) {
    addChar(inputString, 'K');
    return 'K';
  }

  if (scancode == 0x26) {
    addChar(inputString, 'L');
    return 'L';
  }

  if (scancode == 0x32) {
    addChar(inputString, 'M');
    return 'M';
  }

  if (scancode == 0x31) {
    addChar(inputString, 'N');
    return 'N';
  }

  if (scancode == 0x18) {
    addChar(inputString, 'O');
    return 'O';
  }

  if (scancode == 0x19) {
    addChar(inputString, 'P');
    return 'P';
  }

  if (scancode == 0x10) {
    addChar(inputString, 'Q');
    return 'Q';
  }

  if (scancode == 0x13) {
    addChar(inputString, 'R');
    return 'R';
  }

  if (scancode == 0x1F) {
    addChar(inputString, 'S');
    return 'S';
  }

  if (scancode == 0x14) {
    addChar(inputString, 'T');
    return 'T';
  }

  if (scancode == 0x16) {
    addChar(inputString, 'U');
    return 'U';
  }

  if (scancode == 0x2F) {
    addChar(inputString, 'V');
    return 'V';
  }

  if (scancode == 0x11) {
    addChar(inputString, 'W');
    return 'W';
  }

  if (scancode == 0x2D) {
    addChar(inputString, 'X');
    return 'X';
  }

  if (scancode == 0x15) {
    addChar(inputString, 'Y');
    return 'Y';
  }

  if (scancode == 0x2C) {
    addChar(inputString, 'Z');
    return 'Z';
  }

  if (scancode == 0x39) {
    addChar(inputString, ' ');
    return ' ';
  }

  if (scancode == 0x33) {
    addChar(inputString, ',');
    return ',';
  }

  if (scancode == 0x02) {
    addChar(inputString, '1');
    return '1';
  }

  if (scancode == 0x03) {
    addChar(inputString, '2');
    return '2';
  }

  if (scancode == 0x04) {
    addChar(inputString, '3');
    return '3';
  }

  if (scancode == 0x05) {
    addChar(inputString, '4');
    return '4';
  }

  if (scancode == 0x06) {
    addChar(inputString, '5');
    return '5';
  }

  if (scancode == 0x07) {
    addChar(inputString, '6');
    return '6';
  }

  if (scancode == 0x08) {
    addChar(inputString, '7');
    return '7';
  }

  if (scancode == 0x09) {
    addChar(inputString, '8');
    return '8';
  }

  if (scancode == 0x0A) {
    addChar(inputString, '9');
    return '9';
  }

  if (scancode == 0x0B) {
    addChar(inputString, '0');
    return '0';
  }

  addChar(inputString, '?');
  return '?';
}

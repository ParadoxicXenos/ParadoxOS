#pragma once
#include <stdint.h>

uint8_t readPs2Port();
char translate(char scancode);
extern void readLine();
extern int cursorRow;
extern int cursorCol;
extern char line[80];
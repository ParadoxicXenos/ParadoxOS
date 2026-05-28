#pragma once
#include <stdint.h>

uint8_t readPs2Port();
extern void readLine();
extern int cursorRow;
extern int cursorCol;
extern char line[999];
extern void stringCopy(char dest[], char src[]);
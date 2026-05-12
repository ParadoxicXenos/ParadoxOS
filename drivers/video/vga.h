#pragma once
#include <stdint.h>

void print(const char chars[]);
void printLine(const char chars[]);
void newLine();
void scroll();
void clearLine(int x);
void clearScreen();
void splash();

extern int cursorRow;
extern int cursorCol;

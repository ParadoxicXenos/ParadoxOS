#pragma once
#include <stdint.h>

uint8_t readPs2Port();
extern void addChar(char *s, char c);
extern char inputString[80];
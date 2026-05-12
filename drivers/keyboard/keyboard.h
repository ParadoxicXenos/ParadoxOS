#pragma once
#include <stdint.h>

uint8_t readPs2Port();
char translate(char scancode);
extern void addChar(char *s, char c);
extern char inputString[80];
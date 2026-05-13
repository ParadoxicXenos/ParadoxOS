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
  line[0] = '\n';
  stringCopy(line, inputString);
  inputString[0] = '\0';
}

void removeLastChar(char str[80]) {
    int i = 0;

    while (str[i] != '\0') {
        i++;
    }

    if (i > 0) {
        str[i - 1] = '\0';
    }
}
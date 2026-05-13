#include <stdint.h>
#include "string.h"

//====================================
// STRING COMPARE
//====================================
int stringComp(char a[], char b[]) {
  int i = 0;

  while (a[i] != '\0' && b[i] != '\0') {
    if (a[i] != b[i]) {
      return 0;
    }
    i++;
  }

  return a[i] == b[i];
}

//====================================
// STRING COPY
//====================================
void stringCopy(char dest[], char src[]) {
  int i = 0;

  while (src[i] != '\0') {
    dest[i] = src[i];
    i++;
  }

  dest[i] = '\0';
}

//====================================
// SPLIT STRING
//====================================
void splitString(char string[], char delim, char result[10][80]) {
  int pos;
  int word = 0;
  int char_pos = 0;

  for (pos = 0;; pos++) {
    if (word >= 10)
      break;

    if (char_pos >= 79)
      continue;

    if (string[pos] == '\0') {
      result[word][char_pos] = '\0';
      break;
    }

    if (string[pos] == delim) {
      result[word][char_pos] = '\0';
      word++;
      char_pos = 0;
    } else {
      result[word][char_pos] = string[pos];
      char_pos++;
    }
  }
}
// CLEAN STRING===============================
void cleanString(char string[80], char remove, char result[80]) {
    int pos;
    int char_pos = 0;

    for (pos = 0; pos < 79 && string[pos] != '\0'; pos++) {

        if (string[pos] != remove) {
            if (char_pos < 79) {
                result[char_pos++] = string[pos];
            }
        }
    }

    result[char_pos] = '\0';
}

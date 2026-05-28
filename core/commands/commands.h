#pragma once
#include <stdint.h>
void help();
void login(char user[], char pass[]);
void createUser(char usernameInput[], char passwordInput[]);
void whoAmI();

extern int stringComp(char a[], char b[]);
extern void splitString(char string[], char delim, char result[10][80]);
extern void stringCopy(char dest[], char src[]);
extern void clearChar(int row, int col);
extern void drawchar(unsigned char c, int x, int y, uint8_t r, uint8_t g, uint8_t b);
extern void putString(char str[]);
extern void putStringl(char str[]);
extern void putArgbStringl(char *str,int r,int g, int b);
extern void putArgbString(char *str,int r,int g, int b);
extern void newLine();
extern void prompt(int row);
extern int cursorRow;
extern int cursorCol;
extern void putArgbInt(int num,int r,int g,int b);
extern void clearScreen(void);
extern void argbputpixel(int x, int y, int r, int g, int b);
struct colors {
  int r;
  int g;
  int b;
  char name[80];
};

extern struct colors colorList[11];
extern int foreRed;
extern int foreBlue;
extern int foreGreen;
extern int backRed;
extern int backBlue;
extern int backGreen;

#pragma once

void help();
void login(char user[], char pass[]);
void createUser(char usernameInput[], char passwordInput[]);
void whoAmI();

extern int stringComp(char a[], char b[]);
extern void splitString(char string[], char delim, char result[10][80]);
extern void stringCopy(char dest[], char src[]);
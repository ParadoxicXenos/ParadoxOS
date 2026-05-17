#include <stdint.h>

#include "../../drivers/video/gfx.h"
#include "../input/input.h"
#include "../users/users.h"
#include "commands.h"
extern void clearChar(int row, int col);
extern void drawchar(unsigned char c, int x, int y, uint8_t r, uint8_t g,
                     uint8_t b);
extern void putString(char str[80], int row);
extern void putStringl(char str[80], int row);
extern void newLine();
extern void prompt(int row);
extern int cursorRow;
extern int cursorCol;
extern void clearScreen(void);
//====================================
// HELP
//====================================
void help() {
  putStringl("Commands:", cursorRow);
  putStringl("HELP : Displays list of commands", cursorRow);
  putStringl("CLEAR : Clears the screens content", cursorRow);
  putStringl("LOGIN,[USERNAME],[PASSWORD] : Log into an account", cursorRow);
  putStringl("WHOAMI : Lists your accounts details.", cursorRow);
  putStringl("USERCREATE,[USERNAME],[PASSWORD] : Create an account", cursorRow);
}

//====================================
// AUTH / USER COMMANDS
//====================================
void login(char userInput[], char passInput[]) {

  for (int i = 0; i < userCount; i++) {

    if (stringComp(users[i].username, userInput) &&
        stringComp(users[i].password, passInput)) {

      loggedIn = 1;
      stringCopy(currentUser, users[i].username);

      clearScreen();
      // splash();

      putString("Logged in as ", cursorRow);
      putStringl(currentUser, cursorRow);

      return;
    }
  }

  putStringl("Incorrect username or password.", cursorRow);
}

void whoAmI() {
  if (loggedIn) {
    putString("You are: ", cursorRow);
    putStringl(currentUser, cursorRow);
  } else {
    putStringl(
        "You are not logged in, please login before running this command",
        cursorRow);
  }
}

void createUser(char usernameInput[], char passwordInput[]) {

  stringCopy(users[userCount].username, usernameInput);
  stringCopy(users[userCount].password, passwordInput);

  users[userCount].isAdmin = 1;

  putStringl("Account Succesfully Created.", cursorRow);
  putString("USERNAME: ", cursorRow);
  putStringl(users[userCount].username, cursorRow);

  putString("PASSWORD: ", cursorRow);
  putStringl(users[userCount].password, cursorRow);

  userCount++;
}
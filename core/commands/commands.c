#include <stdint.h>

#include "../../drivers/video/vga.h"
#include "../input/input.h"
#include "../users/users.h"
#include "commands.h"

//====================================
// HELP
//====================================
void help() {
  printLine("Commands:");
  printLine("HELP : Displays list of commands");
  printLine("CLEAR : Clears the screens content");
  printLine("LOGIN,[USERNAME],[PASSWORD] : Log into an account");
  printLine("WHOAMI : Lists your accounts details.");
  printLine("USERCREATE,[USERNAME],[PASSWORD] : Create an account");
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
      splash();

      print("Logged in as ");
      printLine(currentUser);

      return;
    }
  }

  printLine("Incorrect username or password.");
}

void whoAmI() {
  if (loggedIn) {
    print("You are: ");
    printLine(currentUser);
  } else {
    printLine("You are not logged in, please login before running this command");
  }
}

void createUser(char usernameInput[], char passwordInput[]) {

  stringCopy(users[userCount].username, usernameInput);
  stringCopy(users[userCount].password, passwordInput);

  users[userCount].isAdmin = 1;

  printLine("Account Succesfully Created.");
  print("USERNAME: ");
  printLine(users[userCount].username);

  print("PASSWORD: ");
  printLine(users[userCount].password);

  userCount++;
}
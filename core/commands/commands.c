#include <stdint.h>

#include "../../drivers/video/gfx.h"
#include "../input/input.h"
#include "../users/users.h"
#include "commands.h"

//====================================
// HELP
//====================================
void help() {
  putStringl("Commands:");
  putStringl("HELP : Displays list of commands");
  putStringl("CLEAR : Clears the screens content");
  putStringl("LOGIN,[USERNAME],[PASSWORD] : Log into an account");
  putStringl("WHOAMI : Lists your accounts details.");
  putStringl("USERCREATE,[USERNAME],[PASSWORD] : Create an account");
  putStringl("COLOR,[COLOR] : CHANGES PRINTING COLOR");
  putStringl("COLOR,LIST : LISTS ALL AVAILABLE COLORS");
}

//====================================
// AUTH / USER COMMANDS
//====================================
void gfxinfo(){
  putArgbString("Width: ",255,0,0);
  putArgbInt(fbWidth,255,0,0);
  cursorCol = 0;
  putArgbString("Height: ",255,0,0);
  putArgbInt(fbHeight,255,0,0);
  cursorCol = 0;
  putArgbString("BPP: ",255,0,0);
  putArgbInt(fbBpp,255,0,0);
}
void login(char userInput[], char passInput[]) {

  for (int i = 0; i < userCount; i++) {

    if (stringComp(users[i].username, userInput) &&
        stringComp(users[i].password, passInput)) {

      loggedIn = 1;
      stringCopy(currentUser, users[i].username);

      clearScreen();
      // splash();

      putString("Logged in as ");
      putStringl(currentUser);

      return;
    }
  }

  putStringl("Incorrect username or password.");
}

void changeColor(char color[]) {
    for(int i = 0; i < 9; i++) {

        if(stringComp(color, colorList[i].name)) {

            red = colorList[i].r;
            green = colorList[i].g;
            blue = colorList[i].b;

            putStringl("Color changed");            
            return;
        }
    }

    putStringl("Color not found");
}
void listColor() {
  for(int i = 0; i < 10; i++) {
        putArgbStringl(colorList[i].name,colorList[i].r,colorList[i].g,colorList[i].b ); 
    }
}

void whoAmI() {
  if (loggedIn) {
    putString("You are: ");
    putStringl(currentUser);
  } else {
    putStringl(
        "You are not logged in, please login before running this command");
  }
}

void createUser(char usernameInput[], char passwordInput[]) {

  stringCopy(users[userCount].username, usernameInput);
  stringCopy(users[userCount].password, passwordInput);

  users[userCount].isAdmin = 1;

  putStringl("Account Succesfully Created.");
  putString("USERNAME: ");
  putStringl(users[userCount].username);

  putString("PASSWORD: ");
  putStringl(users[userCount].password);

  userCount++;
}
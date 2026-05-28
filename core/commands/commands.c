#include <stdint.h>

#include "../../drivers/video/gfx.h"
#include "../input/input.h"
#include "../users/users.h"
#include "commands.h"

void help() {
  putStringl("Commands:");
  putStringl("HELP : Displays list of commands");
  putStringl("CLEAR : Clears the screens content");
  putStringl("LOGIN,[USERNAME],[PASSWORD] : Log into an account");
  putStringl("WHOAMI : Lists your accounts details.");
  putStringl("USERCREATE,[USERNAME],[PASSWORD] : Create an account");
  putStringl("COLOR,[FOREGROUND],[BACKGROUND] : Changes printing colors");
  putStringl("COLOR,LIST : Lists all available colors");
  putStringl("COLOUR,[FOREGROUND],[BACKGROUND] : Changes printing colours");
  putStringl("COLOUR,LIST : Lists all available colours");
  putStringl("BADAPPLE : Plays badapple");
  putStringl("RICK : Plays a 12 second clip of rick astley");
  putStringl("GFXINFO : List graphical propeties");

}

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

      putString("Logged in as ");
      putStringl(currentUser);

      return;
    }
  }

  putStringl("Incorrect username or password.");
}

void changeColor(char foreground[],char background[]) {
    for(int i = 0; i < 23; i++) {

        if(stringComp(foreground, colorList[i].name)) {
            uint32_t color = (foreRed << 16) | (foreGreen << 8) | foreBlue;
            foreRed = colorList[i].r;
            foreGreen = colorList[i].g;
            foreBlue = colorList[i].b;
            for (int x = 0;x<1280;x++){
              for (int y = 0; y<720;y++){
                if (framebuffer[y * (fbPitch / 4) + x] == color){
                  argbputpixel(x, y, foreRed, foreGreen, foreBlue);
                }
              }
            }

            putStringl("Foreground Color changed");            
        }
        if(stringComp(background, colorList[i].name)) {
            uint32_t color = (backRed << 16) | (backGreen << 8) | backBlue;
            backRed = colorList[i].r;
            backGreen = colorList[i].g;
            backBlue = colorList[i].b;
            for (int x = 0;x<1280;x++){
              for (int y = 0; y<720;y++){
                if (framebuffer[y * (fbPitch / 4) + x] == color){
                  argbputpixel(x, y, backRed, backGreen, backBlue);
                }
              }
            }
            putStringl("Background Color changed");           
        }
    }

}
void listColor() {
  for(int i = 0; i < 23; i++) {
        putArgbStringl(colorList[i].name,colorList[i].r,colorList[i].g,colorList[i].b ); 
    }
    putStringl("RUN : COLOR,[FOREGROUND],[BACKGROUND] TO CHANGE COLOR");
    putStringl("RUN : COLOUR,[FOREGROUND],[BACKGROUND] TO CHANGE COLOUR");
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
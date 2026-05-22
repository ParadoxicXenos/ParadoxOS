#include <stdint.h>

#include "../boot/multiboot.h"
#include "../core/commands/commands.h"
#include "../core/input/input.h"
#include "../drivers/keyboard/keyboard.h"
#include "../kernel/kernel.h"
char line[];
uint32_t *framebuffer;
uint32_t fbWidth;
uint32_t fbHeight;
uint32_t fbPitch;
uint8_t fbBpp;
multiboot_info_t *mbi;
int cursorRow;
int cursorCol;
extern void changeColor(char color[]);
extern void listColor();
extern void putArgbInt(int num,int r,int g,int b);
void kernel_main(uint32_t magic, uint32_t addr) {
  mbi = (multiboot_info_t *)addr;

  framebuffer = (uint32_t *)mbi->framebuffer_addr;
  fbWidth = (uint32_t)mbi->framebuffer_width;
  fbHeight = (uint32_t)mbi->framebuffer_height;
  fbPitch = (uint32_t)mbi->framebuffer_pitch;
  fbBpp = (uint8_t)mbi->framebuffer_bpp;
  struct colors {
  int r;
  int g;
  int b;
  char name[80];
};

  struct colors colorList[9] = {
    {47, 54, 153, "PURPLE"},
    {32, 107, 29, "GREEN"},
    {26, 128, 184, "BLUE"},
    {235, 146, 52, "ORANGE"},
    {235, 207, 52, "YELLOW"},
    {232, 30, 30, "RED"},
    {111, 227, 175, "MINT"},
    {255, 255, 255, "WHITE"},
    {255, 128, 234, "PINK"}
  };
  splash();
  putString("Width: ");
  putArgbInt(fbWidth,255,0,0);

  putString(" Height: ");
  putArgbInt(fbHeight,255,0,0);

  putString(" BPP: ");
  putArgbInt(fbBpp,255,0,0);
  prompt(cursorRow);
  while (1) {
    uint8_t scancode = readPs2Port();

    if (scancode & 0x80) // key release
      continue;

    if (scancode == 0x0E) { // backspace
      if (cursorCol <= 2) { // if we are still at a point where all that is on
                            // screen is the prompt we ignore
        continue;
      } else {
        cursorCol--;
        clearChar(cursorRow, cursorCol);
        removeLastChar(inputString);
      }
      continue;
    }
    
    if (scancode == 0x1c) { // enter key
      readLine();
      newLine();

      char parts[10][80];
      splitString(line, ',', parts);

      if (stringComp(line, "HELP")) {
        help();
        prompt(cursorRow);
        continue;
      }
      

      if (stringComp(line, "CLEAR")) {
        clearScreen();
        splash();
        prompt(cursorRow);
        continue;
      }

      if (stringComp(parts[0], "LOGIN")) {
        login(parts[1], parts[2]);
        prompt(cursorRow);
        continue;
      }

      if (stringComp(parts[0], "USERCREATE")) {
        createUser(parts[1], parts[2]);
        prompt(cursorRow);
        continue;
      }

      if (stringComp(parts[0], "COLOR")) {
        if(stringComp(parts[1],"LIST")){
          listColor();
          prompt(cursorRow);
          continue;
        }
        else{
        changeColor(parts[1]);
        prompt(cursorRow);
        continue;
      }
    }
      if (stringComp(line, "WHOAMI")) {
        whoAmI();
        prompt(cursorRow);
        continue;
      } else {
        putString(line);
        putStringl(" is not recognised as an operable command", cursorRow);
        prompt(cursorRow);
        continue;
      }
    }

    char letter = translate(scancode);
    char out[2] = {letter, '\0'};

    putString(out);
  }
}
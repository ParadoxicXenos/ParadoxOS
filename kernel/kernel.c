#include <stdint.h>

#include "../boot/multiboot.h"
#include "../core/commands/commands.h"
#include "../core/input/input.h"
#include "../drivers/keyboard/keyboard.h"
#include "../kernel/kernel.h"
char line[];
multiboot_info_t *mbi;
char parts[10][80];
uint32_t *framebuffer;
uint32_t fbWidth;
uint32_t fbHeight;
uint32_t fbPitch;
uint8_t fbBpp;

int cursorRow;
int cursorCol;
int foreRed = 255;
int foreGreen = 255;
int foreBlue = 255;
int backRed = 0;
int backGreen = 0;
int backBlue = 0;

extern struct colors colorList[];

void kernel_main(uint32_t magic, uint32_t addr) {
  mbi = (multiboot_info_t *)addr;

  framebuffer = (uint32_t *)mbi->framebuffer_addr;
  fbWidth = (uint32_t)mbi->framebuffer_width;
  fbHeight = (uint32_t)mbi->framebuffer_height;
  fbPitch = (uint32_t)mbi->framebuffer_pitch;
  fbBpp = (uint8_t)mbi->framebuffer_bpp;
  splash();

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

      splitString(line, ',', parts);

      if (stringComp(line, "HELP")) {
        help();
        prompt(cursorRow);
        partsClean();
        continue;
      }

      if (stringComp(line, "CLEAR")) {
        clearScreen();
        splash();
        prompt(cursorRow);
        partsClean();
        continue;
      }

      if (stringComp(parts[0], "LOGIN")) {
        login(parts[1], parts[2]);
        prompt(cursorRow);
        partsClean();
        continue;
      }

      if (stringComp(parts[0], "USERCREATE")) {
        createUser(parts[1], parts[2]);
        prompt(cursorRow);
        partsClean();
        continue;
      }

      if (stringComp(parts[0], "COLOR")) {
        if (stringComp(parts[1], "LIST")) {
          listColor();
          prompt(cursorRow);
          partsClean();
          continue;
        } else {
          changeColor(parts[1],parts[2]);
          prompt(cursorRow);
          partsClean();
          continue;
        }
      }
      if (stringComp(line, "WHOAMI")) {
        whoAmI();
        prompt(cursorRow);
        partsClean();
        continue;
      }
      if (stringComp(line, "RICK")) {
        playBigRick();
        clearScreen();
        prompt(cursorRow);
        partsClean();
        continue;
      }
      if (stringComp(line, "BADAPPLE")) {
        playApple();
        clearScreen();
        prompt(cursorRow);
        partsClean();
        continue;
      }

      if (stringComp(line, "GFXINFO")) {
        gfxinfo();
        prompt(cursorRow);
        partsClean();
        continue;
      } else {
        putString(line);
        putStringl(" is not recognised as an operable command");
        prompt(cursorRow);
        partsClean();
        continue;
      }
      
    }

    char letter = translate(scancode);
    char out[2] = {letter, '\0'};

    putString(out);
  }
}

#include <stdint.h>

#include "../boot/multiboot.h"
#include "../core/commands/commands.h"
#include "../core/input/input.h"
#include "../drivers/keyboard/keyboard.h"
#include "../kernel/kernel.h"
char line[];
multiboot_info_t *mbi;

uint32_t *framebuffer;
uint32_t fbWidth;
uint32_t fbHeight;
uint32_t fbPitch;
uint8_t fbBpp;

int cursorRow;
int cursorCol;

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

  struct colors colorList[10] = {
      {115, 99, 255, "PURPLE"}, {0, 255, 0, "GREEN"},
      {0, 128, 255, "BLUE"},    {235, 146, 52, "ORANGE"},
      {255, 221, 0, "YELLOW"},  {255, 0, 0, "RED"},
      {111, 227, 175, "MINT"},  {255, 255, 255, "WHITE"},
      {255, 128, 234, "PINK"},  {221, 0, 255, "MAGENTA"}};
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
        if (stringComp(parts[1], "LIST")) {
          listColor();
          prompt(cursorRow);
          continue;
        } else {
          changeColor(parts[1]);
          prompt(cursorRow);
          continue;
        }
      }
      if (stringComp(line, "WHOAMI")) {
        whoAmI();
        prompt(cursorRow);
        continue;
      }
      if (stringComp(line, "RICK")) {
        playBigRick();
        clearScreen();
        prompt(cursorRow);
        continue;
      }
      if (stringComp(line, "BADAPPLE")) {
        playApple();
        clearScreen();
        prompt(cursorRow);
        continue;
      }

      if (stringComp(line, "GFXINFO")) {
        gfxinfo();
        prompt(cursorRow);
        continue;
      } else {
        putString(line);
        putStringl(" is not recognised as an operable command");
        prompt(cursorRow);
        continue;
      }
    }

    char letter = translate(scancode);
    char out[2] = {letter, '\0'};

    putString(out);
  }
}

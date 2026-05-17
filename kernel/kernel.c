#include <stdint.h>

// #include "../drivers/video/vga.h"
#include "../boot/multiboot.h"
#include "../core/commands/commands.h"
#include "../core/input/input.h"
#include "../drivers/keyboard/keyboard.h"
#include "../kernel/kernel.h"
char line[80];
uint32_t *framebuffer;
uint32_t fbWidth;
uint32_t fbHeight;
uint32_t fbPitch;
uint8_t fbBpp;
multiboot_info_t *mbi;
int cursorRow;
int cursorCol;

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
    if (cursorCol >= 79) {
      newLine();
    }
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

      if (stringComp(line, "WHOAMI")) {
        whoAmI();
        prompt(cursorRow);
        continue;
      } else {
        putString(line, cursorRow);
        putStringl(" is not recognised as an operable command", cursorRow);
        prompt(cursorRow);
        continue;
      }
    }

    char letter = translate(scancode);
    char out[2] = {letter, '\0'};

    putString(out, cursorRow);
  }
}
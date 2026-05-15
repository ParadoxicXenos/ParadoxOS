#include <stdint.h>

#include "../drivers/video/vga.h"
#include "../drivers/keyboard/keyboard.h"
#include "../core/input/input.h"
#include "../core/commands/commands.h"
#include "../kernel/kernel.h"
#include "../boot/multiboot.h"
char line[80];
uint32_t* framebuffer;
uint32_t fbWidth;
uint32_t fbHeight;
uint32_t fbPitch;
uint8_t fbBpp;
extern void drawchar(unsigned char c, int x, int y,uint8_t r, uint8_t g, uint8_t b);
multiboot_info_t* mbi;


void kernel_main(uint32_t magic, uint32_t addr) {
  mbi = (multiboot_info_t*) addr;

  framebuffer = (uint32_t*) mbi->framebuffer_addr;
  fbWidth  = (uint32_t) mbi->framebuffer_width;
  fbHeight = (uint32_t) mbi->framebuffer_height;
  fbPitch  = (uint32_t) mbi->framebuffer_pitch;
  fbBpp    = (uint8_t) mbi->framebuffer_bpp;
  framebuffer[0] = 0x00FF0000;
  if (!(mbi->flags & (1 << 12))) {
    print("Oh shiddings no framebuffer");
  }
  clearScreen();
  drawchar('H', 0, 0, 255, 255, 255);
  drawchar('i', 8, 0, 255, 255, 255);
  framebuffer[0] = 0x00FF0000;
  splash();
  print(">  ");

  while (1) {
    uint8_t scancode = readPs2Port();

    if (scancode & 0x80)
      continue;

    if (scancode == 0x0E) {
      if (cursorCol <= 3) {
        continue;
      } else {
        cursorCol--;
      //  v_mem[cursorRow * 80 + cursorCol] = (0x09 << 8) | ' ';
        removeLastChar(inputString);
      }
      continue;
    }

    if (scancode == 0x1c) {
      readLine();
      newLine();

      char parts[10][80];
      splitString(line, ',', parts);

      if (stringComp(line, "HELP")) {
        help();
        print(">  ");
        continue;
      }

      if (stringComp(line, "CLEAR")) {
        clearScreen();
        splash();
        print(">  ");
        continue;
      }

      if (stringComp(parts[0], "LOGIN")) {
        login(parts[1], parts[2]);
        print(">  ");
        continue;
      }

      if (stringComp(parts[0], "USERCREATE")) {
        createUser(parts[1], parts[2]);
        print(">  ");
        continue;
      }

      if (stringComp(line, "WHOAMI")) {
        whoAmI();
        print(">  ");
        continue;
      } else {
        print(line);
        printLine(" is not recognised as an operable command");
        print(">  ");
        continue;
      }
    }

    char letter = translate(scancode);
    char out[2] = {letter, '\0'};

    print(out);
  }
}
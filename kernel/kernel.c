#include <stdint.h>

#include "../drivers/video/vga.h"
#include "../drivers/keyboard/keyboard.h"
#include "../core/input/input.h"
#include "../core/commands/commands.h"
#include "../core/users/users.h"
#include "../kernel/kernel.h"
#include "../boot/multiboot.h"
char line[80];

void kernel_main(struct multiboot_info* mbi) {
  if (!(mbi->flags & (1 << 12))) {
    print("Oh shiddings no framebuffer");
}
  uint16_t *v_mem = (uint16_t *)0xB8000;

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
        v_mem[cursorRow * 80 + cursorCol] = (0x09 << 8) | ' ';
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
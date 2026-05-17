#include <stdint.h>

#include "../../core/input/input.h"
#include "../../drivers/keyboard/keyboard.h"

/* ====================================
   PORT INPUT
   ==================================== */

static inline uint8_t inb(uint16_t port)
{
    uint8_t ret;

    __asm__ volatile(
        "inb %w1, %b0"
        : "=a"(ret)
        : "Nd"(port)
        : "memory"
    );

    return ret;
}

/* ====================================
   PS/2 READ
   ==================================== */

uint8_t readPs2Port(void)
{
    /* wait until output buffer has data */

    while(!(inb(0x64) & 1))
        ;

    return inb(0x60);
}

/* ====================================
   SCANCODE TABLE
   Set-1 keyboard scancodes
   ==================================== */

static const char keymap[128] =
{
    [0x02]='1',
    [0x03]='2',
    [0x04]='3',
    [0x05]='4',
    [0x06]='5',
    [0x07]='6',
    [0x08]='7',
    [0x09]='8',
    [0x0A]='9',
    [0x0B]='0',

    [0x10]='Q',
    [0x11]='W',
    [0x12]='E',
    [0x13]='R',
    [0x14]='T',
    [0x15]='Y',
    [0x16]='U',
    [0x17]='I',
    [0x18]='O',
    [0x19]='P',

    [0x1E]='A',
    [0x1F]='S',
    [0x20]='D',
    [0x21]='F',
    [0x22]='G',
    [0x23]='H',
    [0x24]='J',
    [0x25]='K',
    [0x26]='L',

    [0x2C]='Z',
    [0x2D]='X',
    [0x2E]='C',
    [0x2F]='V',
    [0x30]='B',
    [0x31]='N',
    [0x32]='M',

    [0x33]=',',
    [0x39]=' '
};

/* ====================================
   TRANSLATE
   ==================================== */

char translate(uint8_t scancode)
{
    if(scancode >= 128)
        return 0;

    char c = keymap[scancode];

    if(c == 0)
        return 0;

    addChar(
        inputString,
        c
    );

    return c;
}
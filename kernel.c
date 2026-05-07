//====================================
#include <stdint.h>

#define WIDTH 80
#define HEIGHT 25
//====================================
void print(const char chars[], int len);
void printl(const char chars[], int len);
void splash();
void scroll();
void clear_line(int x);
int cursor_row = 0;
void clear_screen();
uint8_t read_ps2_port();
int cursor_col = 0;
static inline void io_wait(void);
//====================================
extern void main() {
    splash()
    while(1) {
 //       char scancode[2];
  //      scancode[0] = (char) read_ps2_port();
    //    scancode[1] = '\0';
      //  printl(scancode);
    }
}

static inline uint8_t inb(uint16_t port)

{
    uint8_t ret;
    __asm__ volatile ( "inb %w1, %b0"
                   : "=a"(ret)
                   : "Nd"(port)
                   : "memory");
    return ret;
}

uint8_t read_ps2_port() {
    while (!(inb(0x64) & 1));

    return inb(0x60);
}

static inline void outb(uint16_t port, uint8_t val)
{
    __asm__ volatile ( "outb %b0, %w1" : : "a"(val), "Nd"(port) : "memory");

}

static inline void io_wait(void)
{
    outb(0x80, 0);
}


void print(const char chars[], int len) {
    uint16_t* v_mem = (uint16_t*) 0xB8000;

    for (int i = 0; i < len; i++) {
        int cursor_pos = cursor_row * 80 + cursor_col;
        v_mem[cursor_pos] = (0x09 << 8) | (chars[i] & 0xFF);
        cursor_col++;
        if (cursor_col >= WIDTH) {
            cursor_col = 0;
            cursor_row++;
        if (cursor_row >= HEIGHT) {
            scroll();
        }
        }
    }
}

void new_line() {
    cursor_row++;
    cursor_col = 0;
    if (cursor_row >= 25) {
        scroll();
    }
}

void printl(const char chars[], int len) {
    print(chars, len);
    new_line();
}

void splash(){
    printl("______                   _           _____ _____ ",49);
    printl("| ___ \\                 | |         |  _  /  ___|",50);
    printl("| |_/ /_ _ _ __ __ _  __| | _____  _| | | \\ `--. ",50);
    printl("|  __/ _` | '__/ _` |/ _` |/ _ \\ \\/ / | | |`--. \\",52);
    printl("| | | (_| | | | (_| | (_| | (_) >  <\\ \\_/ /\\__/ /",52);
    printl("\\_|  \\__,_|_|  \\__,_|\\__,_|\\___/_/\\_\\\\___/\\____/",57);
    printl("Hello, world!",13);
}

void scroll(){
    uint16_t* v_mem = (uint16_t*) 0xB8000;

    for (int i = 1; i < 25; i++) {
        for (int x = 0; x < 80; x++){
            v_mem[(i-1) * 80 + x] = v_mem[i * 80 + x];
        }
    }
    clear_line(24);
    cursor_row = 24;
    cursor_col = 0;
}
void clear_line(int x){
    uint16_t* v_mem = (uint16_t*) 0xB8000;
    for (int y = 0; y < 80; y++){
        v_mem[x * 80 + y] = (0x09 << 8) | ' ';
    }

}

void clear_screen(){
    for (int y = 0; y < 25; y++){
        clear_line(y);
    }
}
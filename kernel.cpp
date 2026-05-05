//====================================
#include <stdint.h>
//====================================
void print(const char chars[], int len);
void printl(const char* chars);
void splash();
int cursor_row = 0;
int cursor_col = 0;
//====================================
extern "C" void main() {
    splash();
    while (1) {}
}

void print(const char chars[], int len) {
    uint16_t* v_mem = (uint16_t*) 0xB8000;

    for (int i = 0; i < len; i++) {
        int cursor_pos = cursor_row * 80 + cursor_col;
        v_mem[cursor_pos] = (0x09 << 8) | (chars[i] & 0xFF);
        cursor_col++;
        if (cursor_col >= 80) {
            cursor_col = 0;
            cursor_row++;
        }
    }
}

void new_line() {
    cursor_row++;
    cursor_col = 0;
}

void printl(const char* chars) {
    int len = 0;
    while (chars[len] != '\0') len++;

    print(chars, len);
    new_line();
}

void splash(){
    printl("______                   _           _____ _____ ");
    printl("| ___ \\                 | |         |  _  /  ___|");
    printl("| |_/ /_ _ _ __ __ _  __| | _____  _| | | \\ `--. ");
    printl("|  __/ _` | '__/ _` |/ _` |/ _ \\ \\/ / | | |`--. \\");
    printl("| | | (_| | | | (_| | (_| | (_) >  <\\ \\_/ /\\__/ /");
    printl("\\_|  \\__,_|_|  \\__,_|\\__,_|\\___/_/\\_\\\\___/\\____/");
    printl("Hello, world!");
    printl("Program made by ParadoxicXenos");
}
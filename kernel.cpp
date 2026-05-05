//====================================
#include <stdint.h>
//====================================
void print(const char chars[], int len);
int cursor_row = 0;
int cursor_col = 0;
//====================================
extern "C" void main() {
    print("Hello", 5);
    print("World", 5);
    while (1) {}
}

void print(const char chars[], int len) {
    uint16_t* v_mem = (uint16_t*) 0xB8000;

    for (int i = 0; i < len; i++) {
        int cursor_pos = cursor_row * 80 + cursor_col;
        v_mem[cursor_pos] = (0x01 << 8) | chars[i];
        cursor_col++;
    }
}

void new_line() {
    cursor_row++;
    cursor_col = 0;
}

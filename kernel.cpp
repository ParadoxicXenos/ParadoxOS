#include <stdint.h>
void print(const char chars[], int len);
extern "C" void main() {
    const char msg[] = "Hello, World!";

    print(msg, sizeof(msg) - 1);

    while (1) {}
}
void print(const char chars[], int len) {
    uint16_t* v_mem = (uint16_t*) 0xB8000;

    for (int i = 0; i < len; i++) {
        v_mem[i] = (0x01 << 8) | chars[i];
    }
}

void splash(){
    const char msg[] = "@@@@@@@\                                    @@\                      @@@@@@\   @@@@@@\  ";
    print(msg, sizeof(msg) - 1);
    const char msg[] = "@@  __@@\                                   @@ |                    @@  __@@\ @@  __@@\ ";
    print(msg, sizeof(msg) - 1);
    
}
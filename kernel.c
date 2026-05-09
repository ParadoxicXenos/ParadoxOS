//====================================
#include <stdint.h>

//====================================
void new_line();
void print(const char chars[]);
void printl(const char chars[]);
char translate(char scancode);
void splash();
void scroll();
void clear_line(int x);
int cursor_row = 0;
void clear_screen();
uint8_t read_ps2_port();
int cursor_col = 0;
static inline void io_wait(void);
void addChar(char *s, char c);
void read_line();
void help();
char line[80];
int stringComp(char a[], char b[]);
//====================================
extern void main() {
    uint16_t* v_mem = (uint16_t*)0xB8000;
    splash();
    print(">  ");
    while (1) {
    uint8_t scancode = read_ps2_port();        
    if (scancode & 0x80) continue;
    if (scancode == 0x0E) {
        if (cursor_col<=3){
            continue;
        }
        else{
            cursor_col--;
            v_mem[cursor_row * 80 + cursor_col] = (0x09 << 8) | ' ';
        }
        continue;
    }
    if (scancode == 0x1c) {
        read_line();
        new_line();
        if (stringComp(line, "HELP")) help();
        else print(line), printl(" is not recognised as an operable command");
        print(">  ");
        continue;
    }
    char letter = translate(scancode);

    char out[2] = { letter, '\0' };

    print(out);
}
}
void help(){
    printl("Commands:");
    printl("HELP : Displays list of commands");
}

void addChar(char *s, char c) {
    while (*s) s++;

    *s = c;
    s++;

    *s = '\0';
}
void read_line(){
    uint16_t* v_mem = (uint16_t*)0xB8000;
    line[0] = '\0';

    for (int y = 3; y < cursor_col; y++){
        char letter = v_mem[cursor_row * 80 + y] & 0xFF;

        addChar(line, letter);
    }
}
char translate(char scancode){
    if (scancode == 0x1E) return 'A';
    if (scancode == 0x30) return 'B';
    if (scancode == 0x2E) return 'C';
    if (scancode == 0x20) return 'D';
    if (scancode == 0x12) return 'E';
    if (scancode == 0x21) return 'F';
    if (scancode == 0x22) return 'G';
    if (scancode == 0x23) return 'H';
    if (scancode == 0x17) return 'I';
    if (scancode == 0x24) return 'J';
    if (scancode == 0x25) return 'K';
    if (scancode == 0x26) return 'L';
    if (scancode == 0x32) return 'M';
    if (scancode == 0x31) return 'N';
    if (scancode == 0x18) return 'O';
    if (scancode == 0x19) return 'P';
    if (scancode == 0x10) return 'Q';
    if (scancode == 0x13) return 'R';
    if (scancode == 0x1F) return 'S';
    if (scancode == 0x14) return 'T';
    if (scancode == 0x16) return 'U';
    if (scancode == 0x2F) return 'V';
    if (scancode == 0x11) return 'W';
    if (scancode == 0x2D) return 'X';
    if (scancode == 0x15) return 'Y';
    if (scancode == 0x2C) return 'Z';
    if (scancode == 0x39) return ' ';
    return '?';
}

static inline uint8_t inb(uint16_t port){
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


void print(const char chars[]) {
    uint16_t* v_mem = (uint16_t*) 0xB8000;

    for (int i = 0; chars[i] != '\0'; i++) {
        int cursor_pos = cursor_row * 80 + cursor_col;

        v_mem[cursor_pos] = (0x09 << 8) | (chars[i] & 0xFF);

        cursor_col++;

        if (cursor_col >= 80) {
            cursor_col = 0;
            cursor_row++;
        }

        if (cursor_row >= 25) {
            scroll();
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

void printl(const char chars[]) {
    print(chars);
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
    printl("This program was made by ParadoxicXenos");
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

int stringComp(char a[], char b[]){
    int i = 0;

    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) {
            return 0;
        }

        i++;
    }

    return a[i] == b[i];

}
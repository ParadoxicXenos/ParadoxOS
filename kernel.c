//====================================
#include <stdint.h>

//====================================
void newLine();
void print(const char chars[]);
void printLine(const char chars[]);
char translate(char scancode);
void splash();
void scroll();
void clearLine(int x);
int cursorRow = 0;
void clearScreen();
uint8_t readPs2Port();
int cursorCol = 0;
static inline void ioWait(void);
void addChar(char *s, char c);
void readLine();
void help();
char line[80];
int stringComp(char a[], char b[]);
char username[80]="USER";
char password[80]="PASS";
int loggedIn = 0;
char currentUser[80];
void login(char user[],char pass[]);
void splitString(char string[], char delim, char result[10][80]);
void whoAmI();
void stringCopy(char dest[], char src[]);
void createUser(char user[], char pass[]);
//====================================
extern void main() {
    uint16_t* v_mem = (uint16_t*)0xB8000;
    splash();
    print(">  ");
    while (1) {
    uint8_t scancode = readPs2Port();        
    if (scancode & 0x80) continue;
    if (scancode == 0x0E) {
        if (cursorCol<=3){
            continue;
        }
        else{
            cursorCol--;
            v_mem[cursorRow * 80 + cursorCol] = (0x09 << 8) | ' ';
        }
        continue;
    }
    if (scancode == 0x1c) {
        readLine();
        newLine();
        char parts[10][80];
        splitString(line,',',parts);
        if (stringComp(line, "HELP")){
            help();
            print(">  ");
            continue;
        }
        if (stringComp(line, "CLEAR")){
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
        if (stringComp(line, "whoAmI")) {
            whoAmI();
            print(">  ");
            continue;
        }
        else{
        print(line);
        printLine(" is not recognised as an operable command");
        print(">  ");
        continue;
        }
    }
    char letter = translate(scancode);

    char out[2] = { letter, '\0' };

    print(out);
}
}

void help(){
    printLine("Commands:");
    printLine("HELP : Displays list of commands");
    printLine("CLEAR : Clears the screens content");
    printLine("LOGIN,[USERNAME],[PASSWORD] : Log into an account");
    printLine("whoAmI : Lists your accounts details.");
    printLine("USERCREATE,[USERNAME],[PASSWORD] : Create an account");
}

void addChar(char *s, char c) {
    while (*s) s++;

    *s = c;
    s++;

    *s = '\0';
}
void splitString(char string[], char delim, char result[10][80]){
    int pos;
    int word = 0;
    int char_pos = 0;
    for (pos=0; ;pos++){
        if (word >= 10) break;
        if (char_pos >= 79) continue;
        if (string[pos]=='\0'){
            result[word][char_pos]= '\0';
            break;
        }
        if (string[pos]==delim){
            result[word][char_pos]= '\0';
            word++;
            char_pos = 0;
        }
        else{
            result[word][char_pos] = string[pos];
            char_pos++;
        }
    }
}
void readLine(){
    uint16_t* v_mem = (uint16_t*)0xB8000;
    line[0] = '\0';

    for (int y = 3; y < cursorCol; y++){
        char letter = v_mem[cursorRow * 80 + y] & 0xFF;

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
    if (scancode == 0x33) return ',';
    if (scancode == 0x02) return '1';
    if (scancode == 0x03) return '2';
    if (scancode == 0x04) return '3';
    if (scancode == 0x05) return '4';
    if (scancode == 0x06) return '5';
    if (scancode == 0x07) return '6';
    if (scancode == 0x08) return '7';
    if (scancode == 0x09) return '8';
    if (scancode == 0x0A) return '9';
    if (scancode == 0x0B) return '0';
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

uint8_t readPs2Port() {
    while (!(inb(0x64) & 1));

    return inb(0x60);
}

static inline void outb(uint16_t port, uint8_t val)
{
    __asm__ volatile ( "outb %b0, %w1" : : "a"(val), "Nd"(port) : "memory");

}

static inline void ioWait(void)
{
    outb(0x80, 0);
}


void print(const char chars[]) {
    uint16_t* v_mem = (uint16_t*) 0xB8000;

    for (int i = 0; chars[i] != '\0'; i++) {
        int cursor_pos = cursorRow * 80 + cursorCol;

        v_mem[cursor_pos] = (0x09 << 8) | (chars[i] & 0xFF);

        cursorCol++;

        if (cursorCol >= 80) {
            cursorCol = 0;
            cursorRow++;
        }

        if (cursorRow >= 25) {
            scroll();
        }
    }
}

void newLine() {
    cursorRow++;
    cursorCol = 0;
    if (cursorRow >= 25) {
        scroll();
    }
}

void printLine(const char chars[]) {
    print(chars);
    newLine();
}

void splash(){
    printLine("______                   _           _____ _____ ");
    printLine("| ___ \\                 | |         |  _  /  ___|");
    printLine("| |_/ /_ _ _ __ __ _  __| | _____  _| | | \\ `--. ");
    printLine("|  __/ _` | '__/ _` |/ _` |/ _ \\ \\/ / | | |`--. \\");
    printLine("| | | (_| | | | (_| | (_| | (_) >  <\\ \\_/ /\\__/ /");
    printLine("\\_|  \\__,_|_|  \\__,_|\\__,_|\\___/_/\\_\\\\___/\\____/");
    printLine("Hello, world!");
    printLine("This program was made by ParadoxicXenos");
}

void scroll(){
    uint16_t* v_mem = (uint16_t*) 0xB8000;

    for (int i = 1; i < 25; i++) {
        for (int x = 0; x < 80; x++){
            v_mem[(i-1) * 80 + x] = v_mem[i * 80 + x];
        }
    }
    clearLine(24);
    cursorRow = 24;
    cursorCol = 0;
}
void clearLine(int x){
    uint16_t* v_mem = (uint16_t*) 0xB8000;
    for (int y = 0; y < 80; y++){
        v_mem[x * 80 + y] = (0x09 << 8) | ' ';
    }

}

void clearScreen(){
    for (int y = 0; y < 25; y++){
        clearLine(y);
    }
    cursorRow = 0;
    cursorCol = 0;
}

void login(char user[], char pass[]) {

    if (stringComp(user, username) && stringComp(pass, password)) {

        clearScreen();
        splash();
        loggedIn=1;
        print("Logged in as ");
        printLine(user);
            stringCopy(currentUser, user);
    }
    else {
        printLine("Incorrect username or password.");
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

void whoAmI(){
    if (loggedIn){
    print("You are: ");
    printLine(currentUser);
    }
    if (!loggedIn){
        printLine("You are not logged in, please login before running this command");
    }
}
void stringCopy(char dest[], char src[]) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}
void createUser(char user[], char pass[]) {
    stringCopy(username, user);
    stringCopy(password, pass);
    printLine("Account Created:");
    print("USERNAME: ");
    printLine(username);
    print("PASSWORD: ");
    printLine(password);
    printLine("Please remember to log into this account by running the LOGIN command");
}
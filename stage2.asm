[org 0x7c00]
mov ah, 0x0e
mov bx, [greeterString]
int 0x10
jmp $==

greeterString:
    db "Hello, world!",0
    
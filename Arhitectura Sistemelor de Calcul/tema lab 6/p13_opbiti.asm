bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 2
    b db 3
    c db 4
    d db 5
    ;Dandu-se 4 octeti, sa se obtina in AX suma numerelor intregi reprezentate de bitii 4-6 ai celor 4 octeti.
; our code starts here
segment code use32 class=code
    start:
    mov al, [a] ;al=a7a6a5a4a3a2a1a0
    shr al, 4   ;al=0000a7a6a5a4
                ;transform a7 in 0
    and al, 00000111    ;al=00000a6a5a4
    mov ah, 0           ;ax=0000000000000a6a5a4
    mov bl, [b]
    shr bl, 4
    and bl, 00000111    ;bl=00000b6b5b4
    mov bh, 0
    add ax, bx  ;ax=0000000000000a6a5a4+0000000000000b6b5b4
    mov bl, [c]
    shr bl, 4
    and bl, 00000111    ;bl=00000c6c5c4
    mov bh, 0
    add ax, bx  ;ax=0000000000000a6a5a4+0000000000000b6b5b4+0000000000000c6c5c4
    mov bl, [d]
    shr bl, 4
    and bl, 00000111    ;bl=00000d6d5d4
    mov bh, 0
    add ax, bx  ;ax=0000000000000a6a5a4+0000000000000b6b5b4+0000000000000c6c5c4+0000000000000d6d5d4
    
    
    
    
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

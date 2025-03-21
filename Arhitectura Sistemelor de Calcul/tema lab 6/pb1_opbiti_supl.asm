bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a dw 
    b dw
    c dd 0
    ;bitii 0-4 ai lui C coincid cu bitii 11-15 ai lui A
    ;bitii 5-11 ai lui C au valoarea 1
    ;bitii 12-15 ai lui C coincid cu bitii 8-11 ai lui B
    ;bitii 16-31 ai lui C coincid cu bitii lui A
; our code starts here
segment code use32 class=code
    start:
    mov ax, [a]
    shr ax, 11
    movsx eax, ax
    and eax, 00000000000000000000000000111111 
    or dword[c], eax ;c=00000000000000000000000000011111
    or dword[c], 000000000000000000001111111111111111 
    mov bx, [b]
    movsx ebx, bx ; ebx=0000000000000000b15b14b13b12b11b10b9b8b7b6b5b4b3b2b1b0
    shl ebx, 4  ;ebx=000000000000b15b14b13b12b11b10b9b8b7b6b5b4b3b2b1b00000
    and ebx, 00000000000011110000000000000000 
    or word[c], ebx ;c=0000000000000000b11b10b9b81111111a11a12a13a14a15
    mov cx, [a]
    movsx ecx, cx
    shl ecx, 16
    or word[c], ecx
    
    
    
     
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

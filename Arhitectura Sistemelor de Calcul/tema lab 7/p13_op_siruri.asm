bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    s db 1, 5, 3, 8, 2, 9
    ls equ $-s 
    d1 resb ls
    d2 resb ls
    ;Se da un sir de octeti S. Sa se construiasca sirul D1 ce contine elementele de pe pozitiile pare din S si sirul D2 ce contine elementele de pe pozitiile impare din S.

; our code starts here
segment code use32 class=code
    start:
        ;initializarea reg index
        mov edi, 0 ;d1
        mov ebp, 1 ;d2
        mov esi, 0 ;s
        ;initializarea ecx
        mov ecx, ls/2 ;este suficienta repetarea de 3 ori, deorece in fiecare ciclu se adauga 2 elemente
        repeta:
            mov al, [s+edi]
            mov [d1+esi], al
            mov bl, [s+ebp]
            mov [d2+esi], bl
            add edi, 2
            add ebp, 2
            inc esi
        loop repeta
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

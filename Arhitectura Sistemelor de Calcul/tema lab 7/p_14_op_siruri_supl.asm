bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
; Se da un sir de octeti S. Sa se construiasca un sir D1 care sa contina toate numerele pozitive si un sir D2 care sa contina toate numerele negative din S.
; Exemplu:
; S: 1, 3, -2, -5, 3, -8, 5, 0
; D1: 1, 3, 3, 5, 0
; D2: -2, -5, -8
    s db 1, 3, -2, -5, 3, -8, 5, 0
    ls equ $-s
    p resb ls
    n resb ls
; our code starts here
segment code use32 class=code
    start:
        mov esi, s
        mov edi, p
        mov ecx, ls
        cld
        repeta:
            lodsb ; al=[s+esi] inc esi
            cmp al, 0
            jl negativ
            jge pozitiv 
            
            pozitiv:
                stosb ;mov [d+edi], al inc edi
                jmp final
            negativ:
                mov edi, n 
                stosb
                lodsb
                jmp final
                
            final:
        
        loop repeta

        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

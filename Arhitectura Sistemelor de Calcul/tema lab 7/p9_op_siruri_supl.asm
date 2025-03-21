bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
; Se da un sir de octeti S de lungime l. Sa se construiasca sirul D de lungime l-1 astfel incat elementele din D sa reprezinte diferenta dintre fiecare 2 elemente consecutive din S.
; Exemplu:
; S: 1, 2, 4, 6, 10, 20, 25
; D: 1, 2, 2, 4, 10, 5

    s db 1, 2, 4, 6, 10, 20, 25
    ls equ $-s
    d resb ls-1
; our code starts here
segment code use32 class=code
    start:
    mov esi, 0
    mov ebp, 1
    mov edi, d
    mov ecx, ls
    repeta:
        mov al, byte[s+esi]
        mov bl, byte[s+ebp]
        sub al, bl
        mov [d+edi], al
        inc esi
        inc ebp
        inc edi
    loop repeta
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

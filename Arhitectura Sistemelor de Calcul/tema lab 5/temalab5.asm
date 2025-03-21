bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; (d-b)-a-(b-c)
    a db 5
    b dw 10
    c dd 3
    d dq 40
; our code starts here
segment code use32 class=code
    start:
        ; d-b
        ; se imparte quadwordul d in 2 worduri
        mov eax, dword[d]
        mov edx, dword[d+4]
        mov ebx, eax
        mov ecx, edx
        ; b word -> doubleword
        mov ax, [b]
        cwde
        mov edx, 0
        sub ebx, eax
        sbb ecx, edx ;rezultatul in ecx:ebx  = d-b
        
        ;(d-b)-a
        ;a byte -> doubleword
        
        mov al, [a]
        mov edx, 0
        cbw
        cwde ; a in eax
        sub ebx, eax 
        sbb ecx, edx ;rezultatul in ecx:ebx  = (d-b)-a
        
        ;(d-b)-a-b
        ;b word -> doubleword
        mov ax, [b]
        cwde
        mov edx, 0
        sub ebx, eax
        sbb ecx, edx ;ecx:edx=(d-b)-a-b
        
        ;(d-b)-a-b+c 
        mov eax, [c]
        mov edx, 0
        add eax, ebx
        adc edx, ecx  ; rez in edx:eax = (d-b)-a-b+c
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

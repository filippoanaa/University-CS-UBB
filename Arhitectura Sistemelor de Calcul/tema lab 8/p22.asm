bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    input db 11h, 22h, 33h, 44h, 55h, 77h
    len equ $-input
    src db 33h, 66h, 11h, 22h, 55h
    dst db 03h, 06h, 01h, 02h, 05h
    N equ $-dst
    output times len db 0
    
; our code starts here
segment code use32 class=code
    start:
        ;copiem input in output
        mov ecx, len
        cld
        mov esi, input
        mov edi, output
        rep movsb ;mov byte[output+edi], byte[input+esi] , inc esi, inc edi, dec ecx
        
        ;iteram pe output
        mov ecx, len
        mov esi, 0
        
    loop_1:
        push ecx
        mov ecx, N
        mov al, [output+esi]
        mov edi, src
        loop_2:
            scasb ; cmp al, byte[src+edi], inc edi
            je gasit       
            loop loop_2
        jmp continua
            
    gasit:
        mov ebx, N
        sub ebx, ecx    ;pozitia in sir la care a fost gasit elementul
        mov dl, [dst+ebx]
        mov [output+esi], dl
        
    continua:
        inc esi
        pop ecx
        loop loop_1
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

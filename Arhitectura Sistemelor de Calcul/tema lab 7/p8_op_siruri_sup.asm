bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
; Se da un sir de caractere S. Sa se construiasca sirul D care sa contina toate literele mari din sirul S.
; Exemplu:
; S: 'a', 'A', 'b', 'B', '2', '%', 'x', 'M'
; D: 'A', 'B', 'M
    s db 'a', 'A', 'b', 'B', '2', '%', 'x', 'M'
    ls equ $-s
    d resb ls

; our code starts here
segment code use32 class=code
    start:
    ; mov ecx, ls
    ; mov esi, 0 ;s
    ; mov edi, 0 ;d
    ; repeta:
        ; mov al, [s+esi]
        ; cmp al, 'A'
        ; jl fals
        ; cmp al, 'Z'
        ; jg fals
        
        ; mov [d+edi], al
        ; inc edi
        
        ; fals:
        ; inc esi
    ; loop repeta
    
    mov ecx, ls
    mov esi, s
    mov edi, d
    cld
    repeta:
        lodsb ;mov al, [s+esi] inc esi
        cmp al, 'A'
        jl fals
        cmp al, 'Z'
        jg fals
        
        stosb ;mov[d+edi], al inc edi
        
        fals:
        
    loop repeta
        
        
    
    
    
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

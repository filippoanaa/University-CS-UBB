bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
;Se da un sir de octeti S. Sa se construiasca un sir D1 care sa contina toate numerele pozitive si un sir D2 care sa contina toate numerele negative din S.

    s db 1, 5, 3, 8, 2, 9
    ls equ $-s
    d1 resb ls
    d2 resb ls

; our code starts here
segment code use32 class=code
    start:

    mov esi, 0 ;s
    mov edi, 0 ;indexul pt d1 
    mov ebp, 0 ;indexul pt d2
    
    main_loop:
       cmp esi, ls  ;verificam daca am ajuns la sf sirului
       jge end_main_loop ;daca da, se iese din bucla
       
       test esi, 1 ;verificam paritatea pozitiei
       jz pozitie_para ; daca zero flag este egal cu 0, atunci pozitia este para
       jmp pozitie_impara ;altfel este impara
       
    pozitie_para:
        mov al, [s+esi]  
        mov [d1+edi], al
        inc edi
        jmp next_iteration
        
    pozitie_impara:
        mov bl, [s+esi]
        mov [d2+ebp], bl
        inc ebp
        jmp next_iteration
        
    next_iteration:
        inc esi
        jmp main_loop
    
    end_main_loop:
    
       
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

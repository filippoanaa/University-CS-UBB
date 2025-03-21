bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
; Se dau doua siruri de caractere S1 si S2. Sa se construiasca sirul D prin concatenarea elementelor de pe pozitiile impare din S2 cu elementele de pe pozitiile pare din S1.
; Exemplu:
; S1: 'a', 'b', 'c', 'b', 'e', 'f'
; S2: '1', '2', '3', '4', '5'
; D: '1', '3', '5', 'b', 'b', 'f'
    s1 db 'a', 'b', 'c', 'b', 'e', 'f'
    ls1 equ $-s1
    s2 db '1', '2', '3', '4', '5'
    ls equ $-s2
    d resb ls
    

; our code starts here
segment code use32 class=code
    start:
    
    

    
        
        
        
       
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

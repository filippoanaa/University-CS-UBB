bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ;(a*b+2)/(a+7-c)+d+x
    ;fara semn
    a db 2
    b dw 10
    c db 4
    d dd 5
    x dq 6
    
; our code starts here
segment code use32 class=code
    start:
    ;a byte-> word
        mov al, [a]
        movzx ax, al 
        mul word[b]  ;dx:ax=a*b
        add ax, 2    
        adc dx, 0   ;dx:ax=a*b+2
        
        mov bl, [a] 
        add bl, 7 
        sub bl, [c] ;bl=a+7-c
        movzx bx, bl ;bx=a+7-c
        div bx ;dx:ax/bx =(a*b+2)/(a+7-c)
               ;catul in ax, restul in dx, ignoram restul 
        movzx eax, ax 
        movzx edx, dx  ;edx:eax=(a*b+2)/(a+7-c)+d
        add eax, [d]  ;eax=(a*b+2)/(a+7-c)+d  
        add eax, [x]
        adc edx, [x+4]
        
        
        
        
        
        
        
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf, scanf              ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import printf msvcrt.dll
import scanf msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
; Se dau doua numere naturale a si b (a, b: dword, definite in segmentul de date). Sa se calculeze suma lor si sa se afiseze in ;urmatorul format: "<a> + <b> = <result>"
; Exemplu: "1 + 2 = 3"
; Valorile vor fi afisate in format decimal (baza 10) cu semn.

    a dd 0
    b dd 0
    result dd 0
    format1 db 'a= ', 0
    format2 db 'b= ', 0
    readformat db '%d', 0
    printformat db '%d + %d = %d', 0
    


; our code starts here
segment code use32 class=code
    start:
        ;printf("a= ")
        push dword format1
        call [printf]
        add esp, 4*1
        
        ;scanf(%d, a)
        push dword a
        push dword readformat
        call [scanf]
        add esp, 4*2
        
        ;printf("b= ")
        push dword format2
        call [printf]
        add esp, 4*1
        
        ;scanf(%d, b)
        push dword b
        push dword readformat
        call [scanf]
        add esp, 4*2
        
        mov eax, [a]
        add eax, [b]
        mov [result], eax

        ;printf("%d + %d = %d", a, b, result)
        push dword [result]
        push dword [b]
        push dword [a]
        push dword printformat
        call [printf]
        add esp, 4*4
       
        
        
        
        
        
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

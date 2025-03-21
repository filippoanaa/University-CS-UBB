bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fread, fclose, printf 
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import fopen msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; 2)Se da un fisier text. Sa se citeasca continutul fisierului, sa se contorizeze numarul de consoane si sa se afiseze aceasta valoare. Numele fisierului text este definit in segmentul de date.
    nume_fisier db "text_consoane.txt", 0 
    mod_acces db "r", 0                                            
    descriptor dd -1
    len equ 100                                     
    text times (len+1) db 0 ; + 1 pentru null
    format db "Numarul de consoane este %d",0
    nrconsoane dd 0

; our code starts here
segment code use32 class=code
    start:
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp, 2*4
        
        mov [descriptor], eax
        
        push dword [descriptor]
        push dword len
        push dword 1
        push dword text
        call [fread]
        add esp, 4*4
        
        mov ecx , eax
        mov esi , text
        
        repeta:
            lodsb
            ; verif intai pt litere mici
            cmp al , 'z'
                jge continue
            cmp al , 'a'
                jle continue
            cmp al , 'e'
                je continue
            cmp al , 'i'
                je continue
            cmp al , 'o'
                je continue
            cmp al , 'u'
                je continue
            inc dword[nrconsoane] ; daca nu a fost egal cu una dintre vocale creste nr de consoane
            continue:
            ; verif apoi pt litere mari
            cmp al , 'Z'
                jge continue1
            cmp al , 'A'
                jle continue1
            cmp al , 'E'
                je continue1
            cmp al , 'I'
                je continue1
            cmp al , 'O'
                je continue1 
            cmp al , 'U'
                je continue1
            inc dword[nrconsoane]
            continue1: 
        loop repeta
        
        push dword [nrconsoane]
        push dword format
        call [printf]
        
        ; inchidere fisier
        push dword [descriptor]
        call [fclose]
        add esp, 4*1
    
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

extern exit, fopen, fread, fclose, printf              
import exit msvcrt.dll    
import fopen msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    nume_fisier db "nr_cifre_pare.txt", 0
    mod_acces db "r", 0
    descriptor dd -1
    len equ 100
    text times len db 0
    cifre_pare db "02468", 0
    afisare_format db "S-au citit %d cifre pare din fisier", 0
    ;Se da un fisier text. Sa se citeasca continutul fisierului, sa se contorizeze numarul de cifre pare si sa se afiseze aceasta valoare. Numele fisierului text este definit in segmentul de date.

; our code starts here
segment code use32 class=code
    start:
    ; deschidere fisier
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp, 2*4
        
        ; verificare continu fisier
        cmp eax, 0
        je final
        mov [descriptor], eax
        
        
        ; citire din fisier
        push dword [descriptor]
        push dword len
        push dword 1
        push dword text
        call [fread]
        add esp, 4*4
    
        
        ; numarare cifre pare
        mov esi, 0 ;pt a parcurge val din fisier
        mov ebx, 0 ;contorul pt cifre pare
  
        repeta:
                
            mov ecx, 5 ;nr cifre pare din cifre_pare
            mov edi, 0 
            ; comparam pe rand text[esi] cu cifre_pare[edi]
            numere_pare:
                mov dl, [cifre_pare+edi]
                cmp [text+esi], dl
                je cifra_para
                inc edi
            loop numere_pare
        
            jmp peste
            
            cifra_para:
                add ebx, 1
            
            peste:
                inc esi
                
        cmp byte[text + esi], 0
        je final


        ; afisare numarul de cifre pare in fisier
        afisare:
        push ebx
        push dword afisare_format
        call [printf]
        add esp, 2*4
        
    final:

    
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

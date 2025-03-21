bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

extern exit, fopen, fscanf, fclose, printf              
import exit msvcrt.dll    
import fopen msvcrt.dll
import fscanf msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    format1 db '%c', 0
    file_name db 'nr_cifre_pare.txt', 0
    acces_mode db 'r', 0
    descriptor dd -1
    format_afisare dd 'S-au citit %d cifre pare din fisier.', 0
    nr_cif dd 0
    a dd 0
    ;Se da un fisier text. Sa se citeasca continutul fisierului, sa se contorizeze numarul de cifre pare si sa se afiseze aceasta valoare. Numele fisierului text este definit in segmentul de date.

; our code starts here
segment code use32 class=code
    start:
    ;deschidem fisiserul
    push acces_mode
    push file_name
    call [fopen]
    add esp, 4*2
    
    cmp eax, 0
    je sfarsit
    mov [descriptor], eax
    
    citire:
        push a 
        push format1
        push dword[descriptor]
        call[fscanf]
        add esp, 4*3
        
        test eax, eax ;testam daca val din eax negativa       
                        ;daca da, atunci am citit tot din fisier si afisam, daca nu, continuam verificarea 
        js afisare
        jmp verificare_cifra
    
    verificare_cifra:
       cmp dword[a], '0'
       jl citire
       cmp dword[a], '9'
       jg citire
        
       ;convertim la cifra
       sub dword[a], '0'
       jmp verificare_par    
    
       
    verificare_par:
       push eax
       mov eax, [a]
       mov edx, 0 
       mov ebx, 2
       div ebx ;impartim cifra la 2, si comparam restul din edx pt a verifica daca e para
       cmp edx, 0
       jne nu_e_par
       inc dword[nr_cif]
       nu_e_par:
       pop eax
       jmp citire
        
    afisare:
        push dword[nr_cif]
        push dword format_afisare
        call [printf]
        add esp, 4*2
        
        
    sfarsit:  

    
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

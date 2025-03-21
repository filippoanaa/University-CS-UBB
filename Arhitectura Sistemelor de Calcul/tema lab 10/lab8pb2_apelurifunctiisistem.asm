bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf, scanf; tell nasm that exit exists even if we won't be defining it         
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import printf msvcrt.dll    
import scanf msvcrt.dll     

; our data is declared here (the variables needed by our program)                       
segment data use32 class=data
    ; 2)Sa se citeasca de la tastatura doua numere a si b (in baza 10) si sa se calculeze a/b. Catul impartirii se va salva in memorie in variabila "rezultat" (definita in segmentul de date). Valorile se considera cu semn.
	n dd 0       
    m dd 0
    rezultat dd 0
	message1  db "n=", 0  
    message2  db "m=", 0  
	format  db "%d", 0  

; our code starts here
segment code use32 class=code
    start:
        push dword message1 
        call [printf]      
        add esp, 4*1       
  
        push dword n       
        push dword format
        call [scanf]       
        add esp, 4 * 2 ;s a citit n    
                          
        push dword message2 
        call [printf]      
        add esp, 4*1       
        
        push dword m       
        push dword format
        call [scanf]       
        add esp, 4 * 2 ;s a citit m 

        mov edx, 0
        mov eax, [n]
        cdq
        idiv dword[m]
        mov [rezultat], eax;s a calc in rezultat n/m cu semn
        
        push dword [rezultat]
        push dword format
        call [printf]
        add esp, 2*4; afisam ca sa ne asiguram ca rezultatul e corect
        
        push dword 0 ; push the parameter for exit onto the stack     
        call [exit] ; call exit to terminate the program      
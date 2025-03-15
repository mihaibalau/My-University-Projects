bits 32 

global start        

extern exit, printf, fopen, fclose, scanf, gets       
import exit msvcrt.dll
import printf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import scanf msvcrt.dll
import gets msvcrt.dll
                     
extern find_maximum_value                     
global max_value

segment data use32 class=data
    elements_number resb 1
    max_value dd 0
    info_text db "Enter the string of unsigned numbers in base 10: ", 0
    print_format db "The max value is: %d" , 0
    string times 100 resb 1

segment code use32 class=code
    start:
        
        push dword info_text
        call [printf]
        add esp, 4
        
        push dword string
        call [gets]
        add esp, 4
        
        push string
        call find_maximum_value
        add esp, 4
        
        push dword [max_value]
        push dword print_format
        call [printf]
        add esp, 4*2
        
        push    dword 0
        call    [exit]
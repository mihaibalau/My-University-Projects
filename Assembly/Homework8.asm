bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a dd 280
    b dd 2
    s times 8 db 0 ; in reversed form from divisons
    s2 times 8 db 0 ; the output one

; our code starts here
segment code use32 class=code
    start:
        ; ...
        
        mov eax, [a]
        mov ebx, [b]
        add eax, ebx
        
        mov edi, s
        mov ecx, 8
        
    jecxz OutOfWhile ; will work untill we have the division equal to 0
        repeat:
            mov ebx, 16
            mov edx, 0
            div ebx
            
            add dl, '0'
            cmp dl, '9'
            jbe StoreDigit
            add dl, 7 ; Adjust for letters A-F
            
        StoreDigit:
            mov [edi], dl
            inc edi
            
        loop repeat
    OutOfWhile:
        
        mov ecx, 8
        mov edi, s2
        mov esi, s
        add esi, 7
        
    jecxz ReverseString
        repeat2:
            
            std
            lodsb
            cmp eax, '0'
            je Pass2
            
            cld
            stosb
            
        Pass2:
            
    loop repeat2
        ReverseString:
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

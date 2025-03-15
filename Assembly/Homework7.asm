bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, scanf
import scanf msvcrt.dll               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
extern fopen
import fopen msvcrt.dll
extern fwrite
import fwrite msvcrt.dll

                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    n dd 0
    f db '%', 'd', 0
    fn db "file.txt"
    m db "w"
    fd dd 0

; our code starts here
segment code use32 class=code
    start:
        ; Read n from keyboard
        ; Write in 'a.txt' n
        
        
        mov eax, 0
        push eax
        push dword f
        call [scanf]
        add esp, 2*4
        
        push dword m
        push dword fn
        
        cmp eax, 0
        je final
        
        call [fopen]
        
        mov [fd], eax
        add esp, 2*4
        
        push dword [n]
        push dword f
        push dword [fd]
        
        call [fwrite]
        add esp, 3*4
        
        final:
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

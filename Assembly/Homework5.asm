bits 32 
global start        

extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

segment data use32 class=data
    s1 db 'a', 'b', 'c', 'b', 'e', 'f'
    l1 equ $-s1
    s2 db '1', '2', '3', '4', '5'
    l2 equ $-s2
    d times (l1+l2)/2 db 0


segment code use32 class=code
    start:
    ; 16. Two character strings S1 and S2 are given. Obtain the string D by concatenating the
    ; elements found on odd positions in S2 and the elements found on even positions in S1.
    ; Example:
    ; S1: 'a', 'b', 'c', 'b', 'e', 'f'
    ; S2: '1', '2', '3', '4', '5'
    ; D: '1', '3', '5', 'b', 'b', 'f'
    
        mov ecx, l2 ; for loop
        mov esi, 0 ; for positions in d
        mov edi, 1 ; for positions in s2
        jecxz First
        repeat1:
            mov al, [s2 + edi - 1]
            test edi, 1
            jnz is_odd
                jmp end1
            is_odd:
                mov [d + esi], al
                inc esi
            end1:
                inc edi
        loop repeat1
        First:
        
        mov ecx, l1
        mov edi, 1 ; for positions in s1
        jecxz Second
        repeat2:
            mov al, [s1 + edi - 1]
            test edi, 1
            jz is_even
                jmp end2
            is_even:
                mov [d + esi], al
                inc esi
            end2:
                inc edi
        loop repeat2
        Second:
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

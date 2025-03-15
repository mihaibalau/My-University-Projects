bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

segment data use32 class=data
    s1 dd 'a', 'c', 'd', 'g', 'h'
    l1 equ ($-s1)/4
    s2 dd 'b', 'd', 'e', 'f'
    l2 equ ($-s2)/4
    d times l1+l2 dd 0

segment code use32 class=code
    start:
        ; 16. Being given two alphabetical ordered strings of characters, s1 and s2, build
        ; using merge sort the ordered string of bytes that contain all characters from s1 and s2.
    
        mov ecx, l1
        add ecx, l2 - 1
        
        mov esi, s1
        mov edx, 0
        mov edi, d
        
        lodsd 
        mov ebx, [s2 + edx]
        cld
        
        jecxz WhileTrue1 ; will work until we go through all the elements of one of the 2 strings
        repeat1:
            cmp eax, ebx ; which of the elements are greater
            jbe below_or_equal ; a<=b
                push eax
                mov eax, ebx
                stosd
                pop eax
                add edx, 4
                mov ebx, [s2 + edx]
                
                cmp edx, l2 * 4
                jae no_more_characters1
                    jmp end2
                no_more_characters1:
                    jmp out_of_while2
                end2:
                
                jmp end1
            below_or_equal:
                stosd
                lodsd
                
                cmp esi, s1 + l1 * 4
                jae no_more_characters2
                    jmp end3
                no_more_characters2:
                    jmp out_of_while1
                end3:
                
            end1:
                
        loop repeat1
        WhileTrue1:
        
        jmp end4
        out_of_while1:
            mov eax, ebx
            
            jecxz WhileTrue2
            repeat2:
                stosd
                add edx, 4
                mov eax, [s2 + edx]
            loop repeat2
            WhileTrue2:
            
            jmp end5
            
        out_of_while2:
        
            jecxz WhileTrue3
            repeat3:
                stosd
                lodsd
            loop repeat3
            WhileTrue3:
            
        end4:
        end5:
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

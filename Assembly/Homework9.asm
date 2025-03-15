bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf, scanf
import exit msvcrt.dll   
import printf msvcrt.dll 
import scanf msvcrt.dll  
                          

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a dd 0
    b dd 0
    s times 8 db 0 ; in reversed form from divisons
    s2 times 9 db 0 ; the output one
    InfoMessage db "Enter the values for a and b: ", 0
    OutputMessage db "The arithmetic average of a and b in base 16 is: %s", 0
    format db "%d %d"

; our code starts here
segment code use32 class=code
    start:
        ;  16. Read two numbers a and b (in base 10) from the keyboard. Calculate and print their arithmetic average in base 16
        push dword InfoMessage
        call [printf]
        add esp, 4 * 1
        
        push dword a
        push dword b
        push dword format
        call [scanf]
        add esp, 4 * 3
        
        mov eax, [a]
        mov ebx, [b]
        add eax, ebx
        mov ebx, 2
        mov edx, 0
        div ebx
        
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
            
            cld
            stosb
        
          
        loop repeat2
    ReverseString:
        
        
        push dword s2
        push dword OutputMessage
        call [printf]
        add esp, 4*2
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

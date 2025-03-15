bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fread, fclose, printf
import exit msvcrt.dll   
import fopen msvcrt.dll 
import fread msvcrt.dll  
import fclose msvcrt.dll  
import printf msvcrt.dll 

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ElementsNumber db 100
    s times 100 db 0
    FileName db 'read.txt', 0
    OpenType db 'r', 0
    OutputMessage db "y was found in file %d times and z %d times", 0
    ErrorMessage db "An error was encountered at opening file!", 0
    file_descriptor dd -1
    PrintFormat db "EAX: %d", 10, 0

; our code starts here
segment code use32 class=code
    start:
        push dword OpenType
        push dword FileName
        call [fopen]
        add esp, 4 * 2
        mov [file_descriptor], eax
        
        push dword eax
        push dword PrintFormat
        call [printf]
        add esp, 4 * 2

        cmp eax, 0
        je  ErrorExit
        
        push dword [file_descriptor]
        push dword ElementsNumber
        push dword 1
        push dword s
        call [fread]
        add esp, 4 * 4
        
        push dword eax
        push dword PrintFormat
        call [printf]
        add esp, 4 * 2
        
        mov ecx, eax
        mov esi, s
        mov ebx, 0
        mov edx, 0

    StrLoop:
    
        lodsb 

        cmp eax, 'y'
        je  Found_y
        cmp eax, 'z'
        je  Found_z

        jmp EndLoop

    Found_y:
        inc ebx
        jmp EndLoop

    Found_z:
        inc edx
        jmp EndLoop
        
    EndLoop:
    loop StrLoop

        
        push dword edx
        push dword ebx
        push dword OutputMessage
        call [printf]
        add esp, 4 * 3
        jmp FinishExit

    ErrorExit:
        push dword ErrorMessage
        call [printf]
        add esp, 4
        
    FinishExit:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
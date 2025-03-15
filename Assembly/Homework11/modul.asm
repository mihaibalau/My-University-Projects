bits 32
global find_maximum_value
extern max_value

segment code use32 class=code public

find_maximum_value:

    mov ebx, 0
    mov esi, [esp+4]

    mov eax, 0
    lodsb
    sub eax, '0'
    mov ebx, eax

    mov ecx, 99
    repeat:

        lodsb
        
        cmp eax, 0
        je out_of_loop
        
        cmp eax, ' '
        je compar_number
        
        sub eax, '0'
        mov edx, 0
        
        push eax
        mov eax, ebx
        mov ebx, 10
        mul ebx
        mov ebx, eax
        pop eax
        add ebx, eax
        
        jmp at_end
        compar_number:
      
            cmp ebx, [max_value]
            ja new_maximum_value
            
            jmp skip_it
            
            new_maximum_value:
                mov [max_value], ebx
                
            skip_it:
            lodsb
            sub eax, '0'
            mov ebx, eax
        
        at_end:

    loop repeat

    out_of_loop:

    cmp ebx, [max_value]
    ja new_maximum_value2

    jmp skip_it2

    new_maximum_value2:
        mov [max_value], ebx
        
    skip_it2:
    
    ret
bits 32

extern _convert_string


segment data public data use32

segment code public code use32
_convert_string:
    push ebp
    mov ebp, esp

    mov esi, [ebp + 8]
    mov edi, [ebp + 12]
    
    mov ecx, 100
    mov eax, 0
    mov ebx, 0b
    
    create_number:
    
        lodsb
        
        cmp eax, 10
        je out_of_loop
        
        cmp eax, ','
        je add_number
        
        cmp eax, '''
        je skip_all
        
        cmp eax, ' '
        je skip_all
        
        mul ebx, 2
        add ebx, eax
        
        add_number:
        
        mov eax, ebx
        mov ebx, 0b
        stosd
        
        skip_all:
    
    loop create_number
    
    out_of_loop:
    
    mov esp, ebp
    pop ebp
    
    ret
    



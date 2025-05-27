section .text
global _start

_start:
    push dword 4 ; número para calcular el factorial (hay que hardcodear)
    call factorial
    add esp, 4 

    add eax, '0'
    mov [result], al

    ; Imprimir el mensaje
    mov ecx, msg 
    mov edx, msg_len
    mov ebx, 1 
    mov eax, 4
    int 0x80

    ; Imprimir el resultado
    mov ecx, result
    mov edx, 1
    mov ebx, 1
    mov eax, 4
    int 0x80

    ; Salir del programa
    mov eax,1
    xor ebx,ebx
    int 0x80


factorial:

    cmp eax, 1
    je end_factorial
    push eax
    dec eax
    call factorial
    pop ebx
    mul ebx

end_factorial:
    ret

section .data
    msg db 'Factorial de 4 es: '
    msg_len equ $ - msg

section .bss
    result resb 1

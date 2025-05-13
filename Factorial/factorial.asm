
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

    push ebp
    mov ebp, esp

    mov eax, [ebp+8]

    cmp eax, 1 ;determina si el número es menor o igual a 1
    jbe base_case ; si es menor o igual a 1, salta a base_case

    dec eax
    push eax
    call factorial

    ; recupera el valor de eax
    ; y multiplica por el número original
    mov ebx, [ebp+8]
    mul ebx


    jmp end_factorial ; salta al final

base_case:
    mov eax, 1

end_factorial:
    mov esp, ebp
    pop ebp
    ret

section .data
    msg db 'Factorial de 4 es: '
    msg_len equ $ - msg

section .bss
    result resb 1

section .text
global min_max

min_max:
    enter 0, 0

    mov EAX, [EBP + 8] ; Load the first argument (array pointer) into eax
    mov EDX, [EBP + 12] ; Load the second argument (array size) into ecx
    cmp EAX, EDX
    jl skip1
    xchg EAX, EDX ; Swap if the first argument is greater than the second

skip1:
    mov ECX, [EBP + 16] ; Load the third argument (min) into ecx
    cmp ECX, EAX
    jl new_min
    cmp ECX, EDX
    jl store_result
    mov EDX, ECX ; Set max to min if min is greater than max
    jmp store_result

new_min:
    mov EAX, ECX ; Set min to the new value eax 
    

store_result:
    mov EBX, [EBP + 20] ; Load the fourth argument (max) into ebx
    mov [EBX], EAX ; Store the min value in the address pointed to by ebx
    mov EBX, [EBP + 24] ; Load the fifth argument (min) into ebx
    mov [EBX], EDX ; Store the max value in the address pointed to by ebx
    leave


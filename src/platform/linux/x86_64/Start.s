.text
.globl _start
.type _start, @function
_start:
    call Main
    movl %eax, %edi
    call Mini__Exit
    ud2
.size _start, .-_start

.section .note.GNU-stack,"",@progbits

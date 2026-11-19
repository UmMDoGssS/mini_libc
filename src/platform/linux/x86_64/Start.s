.text
.globl _start
.type _start, @function
_start:
    call Main
    movl %eax, %edi
    movl $60, %eax    # Linux x86-64 exit
    syscall
    ud2
.size _start, .-_start

.section .note.GNU-stack,"",@progbits

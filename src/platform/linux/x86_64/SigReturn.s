.text
.globl Mini__SysSigReturn
.type Mini__SysSigReturn, @function
Mini__SysSigReturn:
    # The handler's ret leaves %rsp just past the return address in the signal frame.
    movq $15, %rax  # rt_sigreturn
    syscall
    ud2
.size Mini__SysSigReturn, .-Mini__SysSigReturn

.section .note.GNU-stack,"",@progbits

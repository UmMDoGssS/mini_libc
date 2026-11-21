#ifndef LinuxX86_64SyscallH_
#define LinuxX86_64SyscallH_

#include "mini/Types.h"
#include "SyscallNumber.h"

static inline Mini__I64 Syscall6(
    SyscallNumber number,
    Mini__I64 arg1,
    Mini__I64 arg2,
    Mini__I64 arg3,
    Mini__I64 arg4,
    Mini__I64 arg5,
    Mini__I64 arg6
) {
    register Mini__I64 r10 __asm__("r10") = arg4;
    register Mini__I64 r8 __asm__("r8") = arg5;
    register Mini__I64 r9 __asm__("r9") = arg6;

    Mini__I64 result;

    // clang-format off: Keep the syscall formatting
    __asm__ volatile (
        "syscall"
        : "=a"(result)
        : "a"(number), "D"(arg1), "S"(arg2), "d"(arg3), "r"(r10), "r"(r8), "r"(r9)
        : "rcx", "r11", "memory", "cc"
    );
    // clang-format on

    return result;
}

#endif // LinuxX86_64SyscallH_

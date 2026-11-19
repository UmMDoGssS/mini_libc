#include "mini/TypesNoNamespace.h"
#include "platform/linux/x86_64/Syscall.h"

const I64 Stdout = 1;

int Main(void) {
    static const Char message[] = "Hello, mini_libc!\n";
    const I64 length = sizeof(message) - 1;
    I64 written = Syscall6(
        SyscallNumber__Write,
        Stdout,
        (IPtr)message,
        length,
        0,
        0,
        0
    );

    return written == length ? 0 : 1;
}

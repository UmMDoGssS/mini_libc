#include "mini/TypesNoNamespace.h"
#include "SyscallNoNamespace.h"

enum {
    WriteSyscall = 1,
    Stdout = 1,
};

int Main(void) {
    static const Char message[] = "Hello, mini_libc!\n";
    const I64 length = sizeof(message) - 1;
    I64 written = Syscall6(
        WriteSyscall,
        Stdout,
        (IPtr)message,
        length,
        0,
        0,
        0
    );

    return written == length ? 0 : 1;
}

#include "mini/TypesNoNamespace.h"
#include "mini/ExitNoNamespace.h"
#include "platform/linux/x86_64/Syscall.h"

const I32 OkExitCode = 0;
const I32 ErrExitCode = 1;

/// Exit group
[[noreturn]]
Void Exit(I32 status) {
    Syscall6(SyscallNumber__ExitGroup, status, 0, 0, 0, 0, 0);
    __builtin_trap();
}

#include "mini/TypesNoNamespace.h"
#include "../../platform/linux/x86_64/SyscallNoNamespace.h"
#include "../../platform/linux/x86_64/SyscallNumberNoNamespace.h"
#include "ExitNoNamespace.h"

const I32 OkExitCode = 0;
const I32 ErrExitCode = 1;

/// Exit group
[[noreturn]]
Void Exit(I32 status) {
    Syscall6(SyscallNumber__ExitGroup, status, 0, 0, 0, 0, 0);
    __builtin_trap();
}

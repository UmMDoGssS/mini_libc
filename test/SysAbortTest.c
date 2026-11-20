#include "mini/SysNoNamespace.h"
#include "mini/TypesNoNamespace.h"
#include "platform/linux/x86_64/Syscall.h"

enum { CoreLimit = 4, WaitSignalMask = 0x7f };

static Void HandleAbort(I32 sig) {
    if (sig != Sig__Abrt) {
        SysExit(2);
    }
    SysAbort();
}

int Main(void) {
    I64 child = Syscall6(SyscallNumber__Fork, 0, 0, 0, 0, 0, 0);
    if (child < 0) {
        return 1;
    }
    if (child == 0) {
        static const U64 core_limits[2] = { 0, 0 };
        static const SigAction action = { .handler.simple = HandleAbort };
        if (Syscall6(SyscallNumber__Setrlimit, CoreLimit, (IPtr) core_limits, 0, 0, 0, 0) != 0 ||
            SysSigAction(Sig__Abrt, &action, nullptr) != 0) {
            SysExit(3);
        }
        SysAbort();
    }

    I32 status;
    if (Syscall6(SyscallNumber__Wait4, child, (IPtr) &status, 0, 0, 0, 0) != child ||
        (status & WaitSignalMask) != Sig__Abrt) {
        return 4;
    }
    return OkExitCode;
}

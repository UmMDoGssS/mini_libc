#include "mini/SysNoNamespace.h"
#include "mini/TypesNoNamespace.h"
#include "platform/linux/x86_64/Syscall.h"

enum {
    NoSuchProcess = 3,
    InvalidArgument = 22,
    SigBlock = 0,
};

int Main(void) {
    I32 pid = SysGetProcId();
    I32 tid = SysGetThreadId();
    if (pid <= 0 || tid != pid) {
        return 1;
    }

    if (SysKill(pid, Sig__None) != 0 || SysThreadKill(pid, tid, Sig__None) != 0) {
        return 2;
    }
    if (SysKill(pid, -1) != -InvalidArgument ||
        SysThreadKill(pid, tid, Sig__RtMax + 1) != -InvalidArgument ||
        SysThreadKill(pid, 0, Sig__None) != -InvalidArgument) {
        return 3;
    }
    if (SysThreadKill(pid + 1, tid, Sig__None) != -NoSuchProcess) {
        return 4;
    }

    // Keep both test signals blocked so the kernel records their delivery.
    const Sig process_sig = Sig__Usr1;
    const Sig thread_sig = Sig__RtMax;
    const U64 mask = ((U64) 1 << (process_sig - 1)) | ((U64) 1 << (thread_sig - 1));
    if (Syscall6(SyscallNumber__RtSigprocmask, SigBlock, (IPtr) &mask, 0, sizeof(mask), 0, 0) != 0) {
        return 5;
    }
    if (SysKill(pid, process_sig) != 0 || SysThreadKill(pid, tid, thread_sig) != 0) {
        return 6;
    }
    U64 pending;
    if (Syscall6(SyscallNumber__RtSigpending, (IPtr) &pending, sizeof(pending), 0, 0, 0, 0) != 0 ||
        (pending & mask) != mask) {
        return 7;
    }

    return OkExitCode;
}

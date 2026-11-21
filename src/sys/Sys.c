#include "mini/Sys.h"
#include "mini/TypesNoNamespace.h"
#include "mini/SysNoNamespace.h"
#include "platform/linux/x86_64/Signal.h"
#include "platform/linux/x86_64/Syscall.h"
#include "platform/linux/x86_64/SyscallNumber.h"

I32 SysGetProcId(void) {
    return (I32) Syscall6(SyscallNumber__Getpid, 0, 0, 0, 0, 0, 0);
}

I32 SysGetThreadId(void) {
    return (I32) Syscall6(SyscallNumber__Gettid, 0, 0, 0, 0, 0, 0);
}

I32 SysKill(I32 pid, I32 sig) {
    return (I32) Syscall6(SyscallNumber__Kill, pid, sig, 0, 0, 0, 0);
}

I32 SysThreadKill(I32 pid, I32 tid, I32 sig) {
    return (I32) Syscall6(SyscallNumber__Tgkill, pid, tid, sig, 0, 0, 0);
}

I32 SysSigAction(I32 sig, const SigAction *action, SigAction *old_action) {
    KernelSigAction new_kernel_action;
    const KernelSigAction *new_action = nullptr;
    if (action != nullptr) {
        new_kernel_action.handler = action->handler;
        new_kernel_action.flags = action->flags | RestorerFlag;
        new_kernel_action.restorer = SysSigReturn;
        new_kernel_action.mask = action->mask;
        new_action = &new_kernel_action;
    }

    KernelSigAction old_kernel_action;
    I32 status = (I32) Syscall6(
        SyscallNumber__RtSigaction,
        sig,
        (IPtr) new_action,
        (IPtr) (old_action != nullptr ? &old_kernel_action : nullptr),
        sizeof(SigSet),
        0,
        0
    );
    if (status == 0 && old_action != nullptr) {
        old_action->handler = old_kernel_action.handler;
        old_action->flags = (U32) old_kernel_action.flags & ~(U32) RestorerFlag;
        old_action->mask = old_kernel_action.mask;
    }
    return status;
}

I32 SysProcMask(I32 how, const SigSet *set, SigSet *old_set) {
    return (I32) Syscall6(SyscallNumber__RtSigprocmask, how, (IPtr) set, (IPtr) old_set, sizeof(SigSet), 0, 0);
}

[[gnu::naked]]
void SysSigReturn(void) {
    // The handler's ret leaves the stack pointer just past the signal frame's return address.
    __asm__ volatile (
        "movq %0, %%rax\n\t"
        "syscall\n\t"
        "ud2"
        :
        : "i"(SyscallNumber__RtSigreturn)
    );
}

const I32 OkExitCode = 0;
const I32 ErrExitCode = 1;

void SysExit(I32 status) {
    Syscall6(SyscallNumber__ExitGroup, status, 0, 0, 0, 0, 0);
    __builtin_trap();
}

I32 SysRaise(I32 sig) {
    return SysThreadKill(SysGetProcId(), SysGetThreadId(), sig);
}

void SysAbort(void) {
    static _Atomic bool abort_started;
    static const SigAction sig_action = {
        .handler.simple = SigHandler__Default,
        .flags = 0,
        .mask = 0,
    };
    const SigSet set = (SigSet) 1 << (Sig__Abrt - 1);

    // Only the first caller attempts to run the installed handler.
    if (!__c11_atomic_exchange(&abort_started, true, __ATOMIC_RELAXED)) {
        (void) SysProcMask(SigMaskHow__Unblock, &set, nullptr);
        (void) SysRaise(Sig__Abrt);
    }

    (void) SysSigAction(Sig__Abrt, &sig_action, nullptr);
    (void) SysProcMask(SigMaskHow__Unblock, &set, nullptr);
    (void) SysRaise(Sig__Abrt);
    SysExit(128 + Sig__Abrt);
}

I64 SysRead(I32 fd, Any *buf, USize count) {
    return Syscall6(SyscallNumber__Read, fd, (I64) buf, count, 0, 0, 0);
}

I64 SysWrite(I32 fd, const Any *buf, USize count) {
    return Syscall6(SyscallNumber__Write, fd, (I64) buf, count, 0, 0, 0);
}

I64 SysLseek(I32 fd, I64 offset, I32 whence) {
    return Syscall6(SyscallNumber__Lseek, fd, offset, whence, 0, 0, 0);
}

I32 SysOpen(const char *path, I32 flags, U32 mode) {
    return SysOpenat(AtFdcwd, path, flags, mode);
}

const I32 AtFdcwd = -100;

I32 SysOpenat(I32 dirfd, const char *path, I32 flags, U32 mode) {
    return (I32) Syscall6(SyscallNumber__Openat, dirfd, (I64) path, flags, mode, 0, 0);
}

I32 SysCreat(const char *path, U32 mode) {
    return SysOpen(path, OpenFlag__WrOnly | OpenFlag__Creat | OpenFlag__Trunc, mode);
}

I32 SysClose(I32 fd) {
    return (I32) Syscall6(SyscallNumber__Close, fd, 0, 0, 0, 0, 0);
}

IPtr SysMmap(Any *address, USize length, I32 protection, I32 flags, I32 fd, I64 offset) {
    return Syscall6(SyscallNumber__Mmap, (IPtr) address, length, protection, flags, fd, offset);
}

I32 SysMunmap(Any *address, USize length) {
    return (I32) Syscall6(SyscallNumber__Munmap, (IPtr) address, length, 0, 0, 0, 0);
}

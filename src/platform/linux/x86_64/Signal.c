#include "mini/SysNoNamespace.h"
#include "mini/TypesNoNamespace.h"
#include "Syscall.h"

enum { RestorerFlag = 0x04000000 };

typedef struct KernelSigAction {
    SigHandler handler;
    U64 flags;
    Void (*restorer)(void);
    SigSet mask;
} KernelSigAction;

static_assert(sizeof(SigSet) == 8);
static_assert(sizeof(KernelSigAction) == 32);
static_assert(__builtin_offsetof(KernelSigAction, flags) == 8);
static_assert(__builtin_offsetof(KernelSigAction, restorer) == 16);
static_assert(__builtin_offsetof(KernelSigAction, mask) == 24);

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

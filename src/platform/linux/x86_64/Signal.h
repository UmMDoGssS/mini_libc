#ifndef LinuxX86_64SignalH_
#define LinuxX86_64SignalH_

#include "mini/Sys.h"

enum { RestorerFlag = 0x04000000 };

typedef struct KernelSigAction {
    Mini__SigHandler handler;
    Mini__U64 flags;
    void (*restorer)(void);
    Mini__SigSet mask;
} KernelSigAction;

static_assert(sizeof(Mini__SigSet) == 8);
static_assert(sizeof(KernelSigAction) == 32);
static_assert(__builtin_offsetof(KernelSigAction, flags) == 8);
static_assert(__builtin_offsetof(KernelSigAction, restorer) == 16);
static_assert(__builtin_offsetof(KernelSigAction, mask) == 24);

#endif // LinuxX86_64SignalH_

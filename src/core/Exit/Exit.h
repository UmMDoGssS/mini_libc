#ifndef Mini__IncludedExitH
#define Mini__IncludedExitH

#include "../../platform/linux/x86_64/Syscall.h"
#include "../../platform/linux/x86_64/SyscallNumber.h"

extern const Mini__I32 Mini__OkExitCode;
extern const Mini__I32 Mini__ErrExitCode;

[[noreturn]]
Mini__Void Mini__Exit(Mini__I32 status);

#endif // Mini__IncludedExitH

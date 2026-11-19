#ifndef Mini__IncludedExitH
#define Mini__IncludedExitH

#include "Types.h"

extern const Mini__I32 Mini__OkExitCode;
extern const Mini__I32 Mini__ErrExitCode;

[[noreturn]]
Mini__Void Mini__SysExit(Mini__I32 status);

#endif // Mini__IncludedExitH

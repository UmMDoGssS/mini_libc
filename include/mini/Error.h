#ifndef Mini__IncludedErrorH
#define Mini__IncludedErrorH

#include "Types.h"

[[noreturn]]
Mini__Void Mini__PanicAt(const Mini__Char *location, Mini__USize length);

#define Mini__PanicStringifyRaw(value) #value
#define Mini__PanicStringify(value) Mini__PanicStringifyRaw(value)
#define Mini__PanicLocation __FILE__ ":" Mini__PanicStringify(__LINE__) "\n"

// TODO: use signals to abort and allow custom error messages
#define Mini__Panic() Mini__PanicAt(Mini__PanicLocation, sizeof(Mini__PanicLocation) - 1)

#endif // Mini__IncludedErrorH

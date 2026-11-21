#ifndef Mini__IncludedErrorH
#define Mini__IncludedErrorH

#include "Types.h"
#include "Macros.h"

[[noreturn]]
Mini__Void Mini__PanicAt(const Mini__Char *location, Mini__USize length);

#define Mini__PanicLocation "Panic at " __FILE__ ":" Mini__StringifyMacro(__LINE__) "\n"

#define Mini__Panic() Mini__PanicAt(Mini__PanicLocation, sizeof(Mini__PanicLocation) - 1)

#endif // Mini__IncludedErrorH

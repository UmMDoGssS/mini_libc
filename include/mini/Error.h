#ifndef Mini__ErrorH_
#define Mini__ErrorH_

#include "Types.h"
#include "Macros.h"

#define Mini__PanicLocation_ "Panic at " __FILE__ ":" Mini__StringifyMacro(__LINE__) "\n"

[[noreturn]]
Mini__Void Mini__Panic_(const Mini__Char *location, Mini__USize length);

#define Mini__Panic() Mini__Panic_(Mini__PanicLocation, sizeof(Mini__PanicLocation) - 1)

#endif // Mini__ErrorH_

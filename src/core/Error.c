#include "mini/Error.h"
#include "mini/SysNoNamespace.h"
#include "mini/TypesNoNamespace.h"

static const I32 Stderr = 2;

void Mini__Panic_(const char *location, USize length) {
    (void) SysWrite(Stderr, location, length);
    SysAbort();
}

#include "mini/Error.h"
#include "mini/SysNoNamespace.h"
#include "mini/TypesNoNamespace.h"

static const I32 Stderr = 2;

Void Mini__PanicAt(const Char *location, USize length) {
    (Void) SysWrite(Stderr, location, length);
    SysAbort();
}

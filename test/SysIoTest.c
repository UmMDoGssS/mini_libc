#include "mini/SysNoNamespace.h"
#include "mini/TypesNoNamespace.h"

enum {
    NoEntry = 2,
    BadFileDescriptor = 9,
    FileExists = 17,
};

int Main(void) {
    static const Char message[] = "mini_libc";
    Char buffer[sizeof(message) - 1];

    I32 output = SysCreat("created", 0600);
    if (output < 0 || SysWrite(output, message, sizeof(buffer)) != sizeof(buffer)) {
        return 1;
    }

    I32 input = SysOpen("created", OpenFlag__RdOnly, 0);
    if (input < 0 || SysRead(input, buffer, sizeof(buffer)) != sizeof(buffer)) {
        return 2;
    }
    for (USize index = 0; index < sizeof(buffer); ++index) {
        if (buffer[index] != message[index]) {
            return 3;
        }
    }
    if (SysRead(input, buffer, sizeof(buffer)) != 0) {
        return 4;
    }

    I32 directory = SysOpen(".", OpenFlag__RdOnly, 0);
    if (directory < 0 || SysCreat("created", 0600) < 0) {
        return 5;
    }
    input = SysOpenat(directory, "created", OpenFlag__RdOnly, 0);
    if (input < 0 || SysRead(input, buffer, sizeof(buffer)) != 0) {
        return 6;
    }

    const I32 flags = OpenFlag__WrOnly | OpenFlag__Creat | OpenFlag__Excl;
    if (SysOpenat(AtFdcwd, "exclusive", flags, 0600) < 0 ||
        SysOpen("exclusive", flags, 0600) != -FileExists) {
        return 7;
    }
    if (SysOpen("missing", OpenFlag__RdOnly, 0) != -NoEntry ||
        SysOpenat(-1, "created", OpenFlag__RdOnly, 0) != -BadFileDescriptor ||
        SysRead(-1, buffer, sizeof(buffer)) != -BadFileDescriptor ||
        SysWrite(-1, message, sizeof(buffer)) != -BadFileDescriptor) {
        return 8;
    }

    return OkExitCode;
}

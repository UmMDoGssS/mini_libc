#include "mini/SysNoNamespace.h"
#include "mini/TypesNoNamespace.h"

enum {
    NoEntry = 2,
    BadFileDescriptor = 9,
    FileExists = 17,
    InvalidArgument = 22,
};

int Main(void) {
    static const char message[] = "mini_libc";
    char buffer[sizeof(message) - 1];

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

    const I64 length = sizeof(buffer);
    if (SysLseek(input, -2, SeekWhence__End) != length - 2 ||
        SysLseek(input, 1, SeekWhence__Cur) != length - 1 ||
        SysRead(input, buffer, 1) != 1 || buffer[0] != message[sizeof(buffer) - 1]) {
        return 5;
    }

    const I64 large_offset = (I64)1 << 33;
    if (SysLseek(input, large_offset, SeekWhence__Set) != large_offset ||
        SysLseek(input, 0, SeekWhence__Cur) != large_offset ||
        SysLseek(input, 0, SeekWhence__End) != length) {
        return 6;
    }
    if (SysLseek(-1, 0, SeekWhence__Set) != -BadFileDescriptor ||
        SysLseek(input, -1, SeekWhence__Set) != -InvalidArgument) {
        return 7;
    }

    I32 directory = SysOpen(".", OpenFlag__RdOnly, 0);
    if (directory < 0 || SysCreat("created", 0600) < 0) {
        return 8;
    }
    input = SysOpenat(directory, "created", OpenFlag__RdOnly, 0);
    if (input < 0 || SysRead(input, buffer, sizeof(buffer)) != 0) {
        return 9;
    }

    const I32 flags = OpenFlag__WrOnly | OpenFlag__Creat | OpenFlag__Excl;
    if (SysOpenat(AtFdcwd, "exclusive", flags, 0600) < 0 ||
        SysOpen("exclusive", flags, 0600) != -FileExists) {
        return 10;
    }
    if (SysOpen("missing", OpenFlag__RdOnly, 0) != -NoEntry ||
        SysOpenat(-1, "created", OpenFlag__RdOnly, 0) != -BadFileDescriptor ||
        SysRead(-1, buffer, sizeof(buffer)) != -BadFileDescriptor ||
        SysWrite(-1, message, sizeof(buffer)) != -BadFileDescriptor) {
        return 11;
    }

    if (SysClose(output) != 0 ||
        SysWrite(output, message, sizeof(buffer)) != -BadFileDescriptor ||
        SysClose(output) != -BadFileDescriptor ||
        SysClose(-1) != -BadFileDescriptor) {
        return 12;
    }

    return OkExitCode;
}

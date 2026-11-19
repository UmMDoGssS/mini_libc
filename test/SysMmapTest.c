#include "mini/SysNoNamespace.h"
#include "mini/TypesNoNamespace.h"
#include "platform/linux/x86_64/Syscall.h"

enum {
    PageSize = 4096,
    BadFileDescriptor = 9,
    OutOfMemory = 12,
    InvalidArgument = 22,
};

int Main(void) {
    const I32 protection = MmapProt__Read | MmapProt__Write;
    const I32 anonymous_flags = MmapFlag__Private | MmapFlag__Anonymous;
    IPtr address = SysMmap(nullptr, PageSize, protection, anonymous_flags, -1, 0);
    if (address < 0) {
        return 1;
    }

    U8 *memory = (U8 *)address;
    volatile U8 *bytes = memory;
    if (bytes[0] != 0 || bytes[PageSize - 1] != 0) {
        return 2;
    }
    bytes[0] = 42;
    bytes[PageSize - 1] = 73;
    if (bytes[0] != 42 || bytes[PageSize - 1] != 73) {
        return 3;
    }
    if (SysMunmap(memory + 1, PageSize) != -InvalidArgument ||
        SysMunmap(memory, PageSize) != 0) {
        return 4;
    }

    // mincore reports ENOMEM when the address has no mapping.
    U8 residency;
    if (Syscall6(SyscallNumber__Mincore, address, PageSize, (IPtr)&residency, 0, 0, 0) != -OutOfMemory) {
        return 5;
    }

    static const U8 marker = 91;
    I32 fd = SysOpen("mapped", OpenFlag__RdWr | OpenFlag__Creat | OpenFlag__Excl, 0600);
    if (fd < 0 || SysLseek(fd, PageSize, SeekWhence__Set) != PageSize ||
        SysWrite(fd, &marker, sizeof(marker)) != sizeof(marker)) {
        return 6;
    }

    address = SysMmap(nullptr, PageSize, MmapProt__Read, MmapFlag__Shared, fd, PageSize);
    if (address < 0 || *(const volatile U8 *)address != marker) {
        return 7;
    }
    if (SysMunmap((Any *)address, PageSize) != 0) {
        return 8;
    }
    if (SysMmap(nullptr, 0, protection, anonymous_flags, -1, 0) != -InvalidArgument ||
        SysMmap(nullptr, PageSize, MmapProt__Read, MmapFlag__Private, -1, 0) != -BadFileDescriptor) {
        return 9;
    }

    return OkExitCode;
}

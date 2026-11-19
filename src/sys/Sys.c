#include "mini/TypesNoNamespace.h"
#include "mini/SysNoNamespace.h"
#include "platform/linux/x86_64/Syscall.h"
#include "platform/linux/x86_64/SyscallNumber.h"

const I32 OkExitCode = 0;
const I32 ErrExitCode = 1;

[[noreturn]]
Void SysExit(I32 status) {
    Syscall6(SyscallNumber__ExitGroup, status, 0, 0, 0, 0, 0);
    __builtin_trap();
}

I64 SysRead(I32 fd, Any *buf, USize count) {
    return Syscall6(SyscallNumber__Read, fd, (I64) buf, count, 0, 0, 0);
}

I64 SysWrite(I32 fd, const Any *buf, USize count) {
    return Syscall6(SyscallNumber__Write, fd, (I64) buf, count, 0, 0, 0);
}

I64 SysLseek(I32 fd, I64 offset, I32 whence) {
    return Syscall6(SyscallNumber__Lseek, fd, offset, whence, 0, 0, 0);
}

I32 SysOpen(const Char *path, I32 flags, U32 mode) {
    return SysOpenat(AtFdcwd, path, flags, mode);
}

const I32 AtFdcwd = -100;

I32 SysOpenat(I32 dirfd, const Char *path, I32 flags, U32 mode) {
    return (I32) Syscall6(SyscallNumber__Openat, dirfd, (I64) path, flags, mode, 0, 0);
}

I32 SysCreat(const Char *path, U32 mode) {
    return SysOpen(path, OpenFlag__WrOnly | OpenFlag__Creat | OpenFlag__Trunc, mode);
}

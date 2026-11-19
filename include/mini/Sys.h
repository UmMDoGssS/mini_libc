#ifndef Mini__IncludedExitH
#define Mini__IncludedExitH

#include "Types.h"

extern const Mini__I32 Mini__OkExitCode;
extern const Mini__I32 Mini__ErrExitCode;

[[noreturn]]
Mini__Void Mini__SysExit(Mini__I32 status);

Mini__I64 Mini__SysRead(
    Mini__I32 fd,
    Mini__Any *buf,
    Mini__USize count
);

Mini__I64 Mini__SysWrite(
    Mini__I32 fd,
    const Mini__Any *buf,
    Mini__USize count
);

typedef enum {
    Mini__SeekWhence__Set = 0,
    Mini__SeekWhence__Cur = 1,
    Mini__SeekWhence__End = 2,
} Mini__SeekWhence;

Mini__I64 Mini__SysLseek(Mini__I32 fd, Mini__I64 offset, Mini__I32 whence);

typedef enum {
    Mini__OpenFlag__RdOnly  = 0,
    Mini__OpenFlag__WrOnly  = 1,
    Mini__OpenFlag__RdWr    = 2,
    Mini__OpenFlag__Creat   = 0100,
    Mini__OpenFlag__Excl    = 0200,
    Mini__OpenFlag__Trunc   = 01000,
    Mini__OpenFlag__Append  = 02000,
} Mini__OpenFlag;

Mini__I32 Mini__SysOpen(
    const Mini__Char *path,
    Mini__I32 flags,
    Mini__U32 mode
);

extern const Mini__I32 Mini__AtFdcwd;

Mini__I32 Mini__SysOpenat(
    Mini__I32 dirfd,
    const Mini__Char *path,
    Mini__I32 flags,
    Mini__U32 mode
);

Mini__I32 Mini__SysCreat(
    const Mini__Char *path,
    Mini__U32 mode
);

#endif // Mini__IncludedExitH

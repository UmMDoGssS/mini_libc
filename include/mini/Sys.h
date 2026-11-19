#ifndef Mini__IncludedExitH
#define Mini__IncludedExitH

#include "Types.h"

extern const Mini__I32 Mini__OkExitCode;
extern const Mini__I32 Mini__ErrExitCode;

[[noreturn]]
Mini__Void Mini__SysExit(Mini__I32 status);

[[nodiscard]]
Mini__I64 Mini__SysRead(
    Mini__I32 fd,
    Mini__Any *buf,
    Mini__USize count
);

[[nodiscard]]
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

[[nodiscard]]
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

[[nodiscard]]
Mini__I32 Mini__SysOpen(
    const Mini__Char *path,
    Mini__I32 flags,
    Mini__U32 mode
);

extern const Mini__I32 Mini__AtFdcwd;

[[nodiscard]]
Mini__I32 Mini__SysOpenat(
    Mini__I32 dirfd,
    const Mini__Char *path,
    Mini__I32 flags,
    Mini__U32 mode
);

[[nodiscard]]
Mini__I32 Mini__SysCreat(
    const Mini__Char *path,
    Mini__U32 mode
);

[[nodiscard]]
Mini__I32 Mini__SysClose(Mini__I32 fd);

typedef enum {
    Mini__MmapProt__None  = 0,
    Mini__MmapProt__Read  = 0x1,
    Mini__MmapProt__Write = 0x2,
    Mini__MmapProt__Exec  = 0x4,
} Mini__MmapProt;

typedef enum {
    Mini__MmapFlag__Shared    = 0x01,
    Mini__MmapFlag__Private   = 0x02,
    Mini__MmapFlag__Anonymous = 0x20,
} Mini__MmapFlag;

[[nodiscard]]
Mini__IPtr Mini__SysMmap(
    Mini__Any *address,
    Mini__USize length,
    Mini__I32 protection,
    Mini__I32 flags,
    Mini__I32 fd,
    Mini__I64 offset
);

[[nodiscard]]
Mini__I32 Mini__SysMunmap(Mini__Any *address, Mini__USize length);

#endif // Mini__IncludedExitH

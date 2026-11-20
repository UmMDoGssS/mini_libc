#ifndef Mini__IncludedSysH
#define Mini__IncludedSysH

#include "Types.h"

[[nodiscard]]
Mini__I32 Mini__SysGetProcId(void);

[[nodiscard]]
Mini__I32 Mini__SysGetThreadId(void);

// Native Linux x86-64 signal numbers. Every number from RtMin through RtMax is valid.
typedef enum Mini__Sig {
    Mini__Sig__None   = 0,
    Mini__Sig__Hup    = 1,
    Mini__Sig__Int    = 2,
    Mini__Sig__Quit   = 3,
    Mini__Sig__Ill    = 4,
    Mini__Sig__Trap   = 5,
    Mini__Sig__Abrt   = 6,
    Mini__Sig__Iot    = Mini__Sig__Abrt,
    Mini__Sig__Bus    = 7,
    Mini__Sig__Fpe    = 8,
    Mini__Sig__Kill   = 9,
    Mini__Sig__Usr1   = 10,
    Mini__Sig__Segv   = 11,
    Mini__Sig__Usr2   = 12,
    Mini__Sig__Pipe   = 13,
    Mini__Sig__Alrm   = 14,
    Mini__Sig__Term   = 15,
    Mini__Sig__StkFlt = 16,
    Mini__Sig__Chld   = 17,
    Mini__Sig__Cont   = 18,
    Mini__Sig__Stop   = 19,
    Mini__Sig__Tstp   = 20,
    Mini__Sig__Ttin   = 21,
    Mini__Sig__Ttou   = 22,
    Mini__Sig__Urg    = 23,
    Mini__Sig__Xcpu   = 24,
    Mini__Sig__Xfsz   = 25,
    Mini__Sig__VtAlrm = 26,
    Mini__Sig__Prof   = 27,
    Mini__Sig__Winch  = 28,
    Mini__Sig__Io     = 29,
    Mini__Sig__Poll   = Mini__Sig__Io,
    Mini__Sig__Pwr    = 30,
    Mini__Sig__Sys    = 31,
    Mini__Sig__Unused = Mini__Sig__Sys,
    Mini__Sig__RtMin  = 32,
    Mini__Sig__RtMax  = 64,
} Mini__Sig;

// Both signal wrappers return zero or a negative Linux errno.
// Mini__Sig__None checks the target and permissions without delivering a signal.
[[nodiscard]]
Mini__I32 Mini__SysKill(Mini__I32 pid, Mini__I32 sig);

// The target thread must belong to the process identified by pid.
[[nodiscard]]
Mini__I32 Mini__SysThreadKill(Mini__I32 pid, Mini__I32 tid, Mini__I32 sig);

// Signal number n uses bit n - 1.
typedef Mini__U64 Mini__SigSet;

typedef enum Mini__SigActionFlag : Mini__U32 {
    Mini__SigActionFlag__NoCldStop = 0x00000001,
    Mini__SigActionFlag__NoCldWait = 0x00000002,
    Mini__SigActionFlag__SigInfo   = 0x00000004,
    Mini__SigActionFlag__OnStack   = 0x08000000,
    Mini__SigActionFlag__Restart   = 0x10000000,
    Mini__SigActionFlag__NoDefer   = 0x40000000,
    Mini__SigActionFlag__ResetHand = 0x80000000,
} Mini__SigActionFlag;

typedef union Mini__SigHandler {
    Mini__Void (*simple)(Mini__I32 sig);
    // The kernel's info and context pointers are borrowed for the handler call.
    Mini__Void (*with_info)(Mini__I32 sig, Mini__Any *info, Mini__Any *context);
} Mini__SigHandler;

#define Mini__SigHandler__Default ((Mini__Void (*)(Mini__I32)) 0)
#define Mini__SigHandler__Ignore  ((Mini__Void (*)(Mini__I32)) 1)

typedef struct Mini__SigAction {
    // Use with_info with Mini__SigActionFlag__SigInfo, and simple otherwise.
    Mini__SigHandler handler;
    Mini__U32 flags;
    Mini__SigSet mask;
} Mini__SigAction;

// A null action queries the disposition. A null old_action skips the previous value.
// The runtime supplies the signal restorer. Returns zero or a negative Linux errno.
[[nodiscard]]
Mini__I32 Mini__SysSigAction(
    Mini__I32 sig,
    const Mini__SigAction *action,
    Mini__SigAction *old_action
);

typedef enum Mini__SigMaskHow {
    Mini__SigMaskHow__Block   = 0,
    Mini__SigMaskHow__Unblock = 1,
    Mini__SigMaskHow__SetMask = 2,
} Mini__SigMaskHow;

// Changes the calling thread's mask. A null set queries it and ignores how.
// A null old_set skips the previous mask. Returns zero or a negative Linux errno.
[[nodiscard]]
Mini__I32 Mini__SysProcMask(
    Mini__I32 how,
    const Mini__SigSet *set,
    Mini__SigSet *old_set
);

// Kernel signal-restorer entry point. A normal C call has no signal frame.
[[noreturn]]
Mini__Void Mini__SysSigReturn(void);

extern const Mini__I32 Mini__OkExitCode;
extern const Mini__I32 Mini__ErrExitCode;

[[noreturn]]
Mini__Void Mini__SysExit(Mini__I32 status);

Mini__I32 Mini__SysRaise(Mini__I32 sig);

[[noreturn]]
Mini__Void Mini__SysAbort(void);

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

#endif // Mini__IncludedSysH

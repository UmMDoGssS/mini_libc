/** @file
 * @brief Short aliases for Linux wrappers and their supporting types.
 *
 * Include this header to use the short names from `Sys.h`.
 */

#ifndef Mini__SysNoNamespaceH_
#define Mini__SysNoNamespaceH_

#include "Sys.h"

/** @copydoc Mini__SysGetProcId */
#define SysGetProcId Mini__SysGetProcId
/** @copydoc Mini__SysGetThreadId */
#define SysGetThreadId Mini__SysGetThreadId

/** @copydoc Mini__Sig__None */
#define Sig__None Mini__Sig__None
/** @copydoc Mini__Sig__Hup */
#define Sig__Hup Mini__Sig__Hup
/** @copydoc Mini__Sig__Int */
#define Sig__Int Mini__Sig__Int
/** @copydoc Mini__Sig__Quit */
#define Sig__Quit Mini__Sig__Quit
/** @copydoc Mini__Sig__Ill */
#define Sig__Ill Mini__Sig__Ill
/** @copydoc Mini__Sig__Trap */
#define Sig__Trap Mini__Sig__Trap
/** @copydoc Mini__Sig__Abrt */
#define Sig__Abrt Mini__Sig__Abrt
/** @copydoc Mini__Sig__Iot */
#define Sig__Iot Mini__Sig__Iot
/** @copydoc Mini__Sig__Bus */
#define Sig__Bus Mini__Sig__Bus
/** @copydoc Mini__Sig__Fpe */
#define Sig__Fpe Mini__Sig__Fpe
/** @copydoc Mini__Sig__Kill */
#define Sig__Kill Mini__Sig__Kill
/** @copydoc Mini__Sig__Usr1 */
#define Sig__Usr1 Mini__Sig__Usr1
/** @copydoc Mini__Sig__Segv */
#define Sig__Segv Mini__Sig__Segv
/** @copydoc Mini__Sig__Usr2 */
#define Sig__Usr2 Mini__Sig__Usr2
/** @copydoc Mini__Sig__Pipe */
#define Sig__Pipe Mini__Sig__Pipe
/** @copydoc Mini__Sig__Alrm */
#define Sig__Alrm Mini__Sig__Alrm
/** @copydoc Mini__Sig__Term */
#define Sig__Term Mini__Sig__Term
/** @copydoc Mini__Sig__StkFlt */
#define Sig__StkFlt Mini__Sig__StkFlt
/** @copydoc Mini__Sig__Chld */
#define Sig__Chld Mini__Sig__Chld
/** @copydoc Mini__Sig__Cont */
#define Sig__Cont Mini__Sig__Cont
/** @copydoc Mini__Sig__Stop */
#define Sig__Stop Mini__Sig__Stop
/** @copydoc Mini__Sig__Tstp */
#define Sig__Tstp Mini__Sig__Tstp
/** @copydoc Mini__Sig__Ttin */
#define Sig__Ttin Mini__Sig__Ttin
/** @copydoc Mini__Sig__Ttou */
#define Sig__Ttou Mini__Sig__Ttou
/** @copydoc Mini__Sig__Urg */
#define Sig__Urg Mini__Sig__Urg
/** @copydoc Mini__Sig__Xcpu */
#define Sig__Xcpu Mini__Sig__Xcpu
/** @copydoc Mini__Sig__Xfsz */
#define Sig__Xfsz Mini__Sig__Xfsz
/** @copydoc Mini__Sig__VtAlrm */
#define Sig__VtAlrm Mini__Sig__VtAlrm
/** @copydoc Mini__Sig__Prof */
#define Sig__Prof Mini__Sig__Prof
/** @copydoc Mini__Sig__Winch */
#define Sig__Winch Mini__Sig__Winch
/** @copydoc Mini__Sig__Io */
#define Sig__Io Mini__Sig__Io
/** @copydoc Mini__Sig__Poll */
#define Sig__Poll Mini__Sig__Poll
/** @copydoc Mini__Sig__Pwr */
#define Sig__Pwr Mini__Sig__Pwr
/** @copydoc Mini__Sig__Sys */
#define Sig__Sys Mini__Sig__Sys
/** @copydoc Mini__Sig__Unused */
#define Sig__Unused Mini__Sig__Unused
/** @copydoc Mini__Sig__RtMin */
#define Sig__RtMin Mini__Sig__RtMin
/** @copydoc Mini__Sig__RtMax */
#define Sig__RtMax Mini__Sig__RtMax
/** @copydoc Mini__Sig */
#define Sig Mini__Sig

/** @copydoc Mini__OkExitCode */
#define OkExitCode Mini__OkExitCode
/** @copydoc Mini__ErrExitCode */
#define ErrExitCode Mini__ErrExitCode

/** @copydoc Mini__SysExit */
#define SysExit Mini__SysExit

/** @copydoc Mini__SysRaise */
#define SysRaise Mini__SysRaise

/** @copydoc Mini__SysAbort */
#define SysAbort Mini__SysAbort

/** @copydoc Mini__SysKill */
#define SysKill Mini__SysKill
/** @copydoc Mini__SysThreadKill */
#define SysThreadKill Mini__SysThreadKill

/** @copydoc Mini__SigSet */
#define SigSet Mini__SigSet

/** @copydoc Mini__SigActionFlag__NoCldStop */
#define SigActionFlag__NoCldStop Mini__SigActionFlag__NoCldStop
/** @copydoc Mini__SigActionFlag__NoCldWait */
#define SigActionFlag__NoCldWait Mini__SigActionFlag__NoCldWait
/** @copydoc Mini__SigActionFlag__SigInfo */
#define SigActionFlag__SigInfo Mini__SigActionFlag__SigInfo
/** @copydoc Mini__SigActionFlag__OnStack */
#define SigActionFlag__OnStack Mini__SigActionFlag__OnStack
/** @copydoc Mini__SigActionFlag__Restart */
#define SigActionFlag__Restart Mini__SigActionFlag__Restart
/** @copydoc Mini__SigActionFlag__NoDefer */
#define SigActionFlag__NoDefer Mini__SigActionFlag__NoDefer
/** @copydoc Mini__SigActionFlag__ResetHand */
#define SigActionFlag__ResetHand Mini__SigActionFlag__ResetHand
/** @copydoc Mini__SigActionFlag */
#define SigActionFlag Mini__SigActionFlag

/** @copydoc Mini__SigHandler__Default */
#define SigHandler__Default Mini__SigHandler__Default
/** @copydoc Mini__SigHandler__Ignore */
#define SigHandler__Ignore Mini__SigHandler__Ignore
/** @copydoc Mini__SigHandler */
#define SigHandler Mini__SigHandler
/** @copydoc Mini__SigAction */
#define SigAction Mini__SigAction

/** @copydoc Mini__SigMaskHow__Block */
#define SigMaskHow__Block Mini__SigMaskHow__Block
/** @copydoc Mini__SigMaskHow__Unblock */
#define SigMaskHow__Unblock Mini__SigMaskHow__Unblock
/** @copydoc Mini__SigMaskHow__SetMask */
#define SigMaskHow__SetMask Mini__SigMaskHow__SetMask
/** @copydoc Mini__SigMaskHow */
#define SigMaskHow Mini__SigMaskHow

/** @copydoc Mini__SysSigAction */
#define SysSigAction Mini__SysSigAction
/** @copydoc Mini__SysProcMask */
#define SysProcMask Mini__SysProcMask

/** @copydoc Mini__SysRead */
#define SysRead Mini__SysRead

/** @copydoc Mini__SysWrite */
#define SysWrite Mini__SysWrite

/** @copydoc Mini__SeekWhence__Set */
#define SeekWhence__Set Mini__SeekWhence__Set
/** @copydoc Mini__SeekWhence__Cur */
#define SeekWhence__Cur Mini__SeekWhence__Cur
/** @copydoc Mini__SeekWhence__End */
#define SeekWhence__End Mini__SeekWhence__End
/** @copydoc Mini__SeekWhence */
#define SeekWhence Mini__SeekWhence

/** @copydoc Mini__SysSeek */
#define SysSeek Mini__SysSeek

/** @copydoc Mini__OpenFlag__RdOnly */
#define OpenFlag__RdOnly Mini__OpenFlag__RdOnly
/** @copydoc Mini__OpenFlag__WrOnly */
#define OpenFlag__WrOnly Mini__OpenFlag__WrOnly
/** @copydoc Mini__OpenFlag__RdWr */
#define OpenFlag__RdWr Mini__OpenFlag__RdWr
/** @copydoc Mini__OpenFlag__Creat */
#define OpenFlag__Creat Mini__OpenFlag__Creat
/** @copydoc Mini__OpenFlag__Excl */
#define OpenFlag__Excl Mini__OpenFlag__Excl
/** @copydoc Mini__OpenFlag__Trunc */
#define OpenFlag__Trunc Mini__OpenFlag__Trunc
/** @copydoc Mini__OpenFlag__Append */
#define OpenFlag__Append Mini__OpenFlag__Append
/** @copydoc Mini__OpenFlag */
#define OpenFlag Mini__OpenFlag

/** @copydoc Mini__SysOpen */
#define SysOpen Mini__SysOpen

/** @copydoc Mini__AtFdcwd */
#define AtFdcwd Mini__AtFdcwd

/** @copydoc Mini__SysOpenAt */
#define SysOpenAt Mini__SysOpenAt

/** @copydoc Mini__SysCreate */
#define SysCreate Mini__SysCreate

/** @copydoc Mini__SysClose */
#define SysClose Mini__SysClose

/** @copydoc Mini__MmapProt__None */
#define MmapProt__None Mini__MmapProt__None
/** @copydoc Mini__MmapProt__Read */
#define MmapProt__Read Mini__MmapProt__Read
/** @copydoc Mini__MmapProt__Write */
#define MmapProt__Write Mini__MmapProt__Write
/** @copydoc Mini__MmapProt__Exec */
#define MmapProt__Exec Mini__MmapProt__Exec
/** @copydoc Mini__MmapProt */
#define MmapProt Mini__MmapProt

/** @copydoc Mini__MmapFlag__Shared */
#define MmapFlag__Shared Mini__MmapFlag__Shared
/** @copydoc Mini__MmapFlag__Private */
#define MmapFlag__Private Mini__MmapFlag__Private
/** @copydoc Mini__MmapFlag__Anonymous */
#define MmapFlag__Anonymous Mini__MmapFlag__Anonymous
/** @copydoc Mini__MmapFlag */
#define MmapFlag Mini__MmapFlag

/** @copydoc Mini__SysMmap */
#define SysMmap Mini__SysMmap
/** @copydoc Mini__SysMunmap */
#define SysMunmap Mini__SysMunmap

#endif // Mini__SysNoNamespaceH_

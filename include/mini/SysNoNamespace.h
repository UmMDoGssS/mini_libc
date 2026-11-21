#ifndef Mini__SysNoNamespaceH_
#define Mini__SysNoNamespaceH_

#include "Sys.h"

#define SysGetProcId   Mini__SysGetProcId
#define SysGetThreadId Mini__SysGetThreadId

#define Sig__None   Mini__Sig__None
#define Sig__Hup    Mini__Sig__Hup
#define Sig__Int    Mini__Sig__Int
#define Sig__Quit   Mini__Sig__Quit
#define Sig__Ill    Mini__Sig__Ill
#define Sig__Trap   Mini__Sig__Trap
#define Sig__Abrt   Mini__Sig__Abrt
#define Sig__Iot    Mini__Sig__Iot
#define Sig__Bus    Mini__Sig__Bus
#define Sig__Fpe    Mini__Sig__Fpe
#define Sig__Kill   Mini__Sig__Kill
#define Sig__Usr1   Mini__Sig__Usr1
#define Sig__Segv   Mini__Sig__Segv
#define Sig__Usr2   Mini__Sig__Usr2
#define Sig__Pipe   Mini__Sig__Pipe
#define Sig__Alrm   Mini__Sig__Alrm
#define Sig__Term   Mini__Sig__Term
#define Sig__StkFlt Mini__Sig__StkFlt
#define Sig__Chld   Mini__Sig__Chld
#define Sig__Cont   Mini__Sig__Cont
#define Sig__Stop   Mini__Sig__Stop
#define Sig__Tstp   Mini__Sig__Tstp
#define Sig__Ttin   Mini__Sig__Ttin
#define Sig__Ttou   Mini__Sig__Ttou
#define Sig__Urg    Mini__Sig__Urg
#define Sig__Xcpu   Mini__Sig__Xcpu
#define Sig__Xfsz   Mini__Sig__Xfsz
#define Sig__VtAlrm Mini__Sig__VtAlrm
#define Sig__Prof   Mini__Sig__Prof
#define Sig__Winch  Mini__Sig__Winch
#define Sig__Io     Mini__Sig__Io
#define Sig__Poll   Mini__Sig__Poll
#define Sig__Pwr    Mini__Sig__Pwr
#define Sig__Sys    Mini__Sig__Sys
#define Sig__Unused Mini__Sig__Unused
#define Sig__RtMin  Mini__Sig__RtMin
#define Sig__RtMax  Mini__Sig__RtMax
#define Sig         Mini__Sig

#define OkExitCode  Mini__OkExitCode
#define ErrExitCode Mini__ErrExitCode

#define SysExit Mini__SysExit

#define SysRaise Mini__SysRaise

#define SysAbort Mini__SysAbort

#define SysKill       Mini__SysKill
#define SysThreadKill Mini__SysThreadKill

#define SigSet Mini__SigSet

#define SigActionFlag__NoCldStop Mini__SigActionFlag__NoCldStop
#define SigActionFlag__NoCldWait Mini__SigActionFlag__NoCldWait
#define SigActionFlag__SigInfo   Mini__SigActionFlag__SigInfo
#define SigActionFlag__OnStack   Mini__SigActionFlag__OnStack
#define SigActionFlag__Restart   Mini__SigActionFlag__Restart
#define SigActionFlag__NoDefer   Mini__SigActionFlag__NoDefer
#define SigActionFlag__ResetHand Mini__SigActionFlag__ResetHand
#define SigActionFlag            Mini__SigActionFlag

#define SigHandler__Default Mini__SigHandler__Default
#define SigHandler__Ignore  Mini__SigHandler__Ignore
#define SigHandler          Mini__SigHandler
#define SigAction           Mini__SigAction

#define SigMaskHow__Block   Mini__SigMaskHow__Block
#define SigMaskHow__Unblock Mini__SigMaskHow__Unblock
#define SigMaskHow__SetMask Mini__SigMaskHow__SetMask
#define SigMaskHow          Mini__SigMaskHow

#define SysSigAction  Mini__SysSigAction
#define SysProcMask   Mini__SysProcMask
#define SysSigReturn  Mini__SysSigReturn

#define SysRead Mini__SysRead

#define SysWrite Mini__SysWrite

#define SeekWhence__Set Mini__SeekWhence__Set
#define SeekWhence__Cur Mini__SeekWhence__Cur
#define SeekWhence__End Mini__SeekWhence__End
#define SeekWhence      Mini__SeekWhence

#define SysLseek Mini__SysLseek

#define OpenFlag__RdOnly Mini__OpenFlag__RdOnly
#define OpenFlag__WrOnly Mini__OpenFlag__WrOnly
#define OpenFlag__RdWr   Mini__OpenFlag__RdWr
#define OpenFlag__Creat  Mini__OpenFlag__Creat
#define OpenFlag__Excl   Mini__OpenFlag__Excl
#define OpenFlag__Trunc  Mini__OpenFlag__Trunc
#define OpenFlag__Append Mini__OpenFlag__Append
#define OpenFlag         Mini__OpenFlag

#define SysOpen Mini__SysOpen

#define AtFdcwd Mini__AtFdcwd

#define SysOpenat Mini__SysOpenat

#define SysCreat Mini__SysCreat

#define SysClose Mini__SysClose

#define MmapProt__None  Mini__MmapProt__None
#define MmapProt__Read  Mini__MmapProt__Read
#define MmapProt__Write Mini__MmapProt__Write
#define MmapProt__Exec  Mini__MmapProt__Exec
#define MmapProt        Mini__MmapProt

#define MmapFlag__Shared    Mini__MmapFlag__Shared
#define MmapFlag__Private   Mini__MmapFlag__Private
#define MmapFlag__Anonymous Mini__MmapFlag__Anonymous
#define MmapFlag            Mini__MmapFlag

#define SysMmap   Mini__SysMmap
#define SysMunmap Mini__SysMunmap

#endif // Mini__SysNoNamespaceH_

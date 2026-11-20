#include "mini/SysNoNamespace.h"
#include "mini/TypesNoNamespace.h"

enum { InvalidArgument = 22 };

static const SigSet ThreadMask = (U64) 1 << (Sig__RtMax - 1);
static const SigSet SignalBit = (U64) 1 << (Sig__Usr1 - 1);
static const SigSet HandlerMask = (U64) 1 << (Sig__Usr2 - 1);

static volatile I32 handled_signal;
static volatile Bool handler_mask_ok;
static volatile Bool info_args_ok;

static Void HandleSignal(I32 sig) {
    SigSet mask;
    handler_mask_ok = SysProcMask(SigMaskHow__SetMask, nullptr, &mask) == 0 &&
                      mask == (ThreadMask | SignalBit | HandlerMask);
    handled_signal = sig;
}

static Void HandleSignalWithInfo(I32 sig, Any *info, Any *context) {
    info_args_ok = info != nullptr && context != nullptr;
    handled_signal = sig;
}

int Main(void) {
    SigSet original_mask;
    SigSet old_mask;
    if (SysProcMask(-1, nullptr, &original_mask) != 0 ||
        SysProcMask(SigMaskHow__SetMask, &ThreadMask, &old_mask) != 0 ||
        old_mask != original_mask ||
        SysProcMask(-1, &SignalBit, nullptr) != -InvalidArgument) {
        return 1;
    }

    const SigAction action = {
        .handler.simple = HandleSignal,
        .flags = SigActionFlag__Restart,
        .mask = HandlerMask,
    };
    SigAction original_action;
    if (SysSigAction(Sig__Kill, &action, nullptr) != -InvalidArgument ||
        SysSigAction(Sig__Usr1, &action, &original_action) != 0) {
        return 2;
    }
    SigAction installed;
    if (SysSigAction(Sig__Usr1, nullptr, &installed) != 0 ||
        installed.handler.simple != HandleSignal ||
        installed.flags != action.flags || installed.mask != HandlerMask) {
        return 3;
    }

    I32 pid = SysGetProcId();
    if (pid <= 0 || SysProcMask(SigMaskHow__Block, &SignalBit, &old_mask) != 0 ||
        old_mask != ThreadMask || SysKill(pid, Sig__Usr1) != 0 || handled_signal != 0) {
        return 4;
    }
    if (SysProcMask(SigMaskHow__Unblock, &SignalBit, &old_mask) != 0 ||
        old_mask != (ThreadMask | SignalBit) || handled_signal != Sig__Usr1 || !handler_mask_ok) {
        return 5;
    }
    if (SysProcMask(SigMaskHow__SetMask, nullptr, &old_mask) != 0 || old_mask != ThreadMask) {
        return 6;
    }

    SigAction replacement = {
        .handler.with_info = HandleSignalWithInfo,
        .flags = SigActionFlag__SigInfo,
        .mask = 0,
    };
    if (SysSigAction(Sig__Usr1, &replacement, &replacement) != 0 ||
        replacement.handler.simple != HandleSignal ||
        replacement.flags != action.flags || replacement.mask != HandlerMask ||
        SysSigAction(Sig__Usr1, nullptr, &installed) != 0 ||
        installed.handler.with_info != HandleSignalWithInfo ||
        installed.flags != SigActionFlag__SigInfo || installed.mask != 0) {
        return 7;
    }
    handled_signal = 0;
    if (SysKill(pid, Sig__Usr1) != 0 || handled_signal != Sig__Usr1 || !info_args_ok) {
        return 8;
    }

    const SigAction ignore = { .handler.simple = SigHandler__Ignore };
    handled_signal = 0;
    if (SysSigAction(Sig__Usr1, &ignore, nullptr) != 0 ||
        SysKill(pid, Sig__Usr1) != 0 || handled_signal != 0) {
        return 9;
    }

    if (SysSigAction(Sig__Usr1, &original_action, nullptr) != 0 ||
        SysProcMask(SigMaskHow__SetMask, &original_mask, nullptr) != 0) {
        return 10;
    }
    return OkExitCode;
}

/** @file
 * @brief Direct Linux x86-64 wrappers for processes, signals, file I/O, and memory mappings.
 *
 * Fallible wrappers return negative Linux error numbers directly. They do not set `errno`.
 */

#ifndef Mini__SysH_
#define Mini__SysH_

#include "Types.h"

/** @brief Returns the process ID of the caller. */
[[nodiscard]]
Mini__I32 Mini__SysGetProcId(void);

/** @brief Returns the kernel thread ID of the calling thread. */
[[nodiscard]]
Mini__I32 Mini__SysGetThreadId(void);

/**
 * @brief Native Linux x86-64 signal numbers.
 *
 * Every signal number from Mini__Sig__RtMin through Mini__Sig__RtMax is valid.
 */
typedef enum Mini__Sig {
    Mini__Sig__None   = 0,               /**< Check the target without sending a signal. */
    Mini__Sig__Hup    = 1,               /**< Hangup. */
    Mini__Sig__Int    = 2,               /**< Interrupt. */
    Mini__Sig__Quit   = 3,               /**< Quit. */
    Mini__Sig__Ill    = 4,               /**< Illegal instruction. */
    Mini__Sig__Trap   = 5,               /**< Trace or breakpoint trap. */
    Mini__Sig__Abrt   = 6,               /**< Abort. */
    Mini__Sig__Iot    = Mini__Sig__Abrt, /**< Historical name for Mini__Sig__Abrt. */
    Mini__Sig__Bus    = 7,               /**< Bus error. */
    Mini__Sig__Fpe    = 8,               /**< Arithmetic exception. */
    Mini__Sig__Kill   = 9,               /**< Forced termination. Cannot be caught or blocked. */
    Mini__Sig__Usr1   = 10,              /**< First user-defined signal. */
    Mini__Sig__Segv   = 11,              /**< Invalid memory reference. */
    Mini__Sig__Usr2   = 12,              /**< Second user-defined signal. */
    Mini__Sig__Pipe   = 13,              /**< Write to a pipe without readers. */
    Mini__Sig__Alrm   = 14,              /**< Real-time interval timer expired. */
    Mini__Sig__Term   = 15,              /**< Termination request. */
    Mini__Sig__StkFlt = 16,              /**< Historical coprocessor stack fault. */
    Mini__Sig__Chld   = 17,              /**< Child process changed state. */
    Mini__Sig__Cont   = 18,              /**< Resume a stopped process. */
    Mini__Sig__Stop   = 19,              /**< Forced stop. Cannot be caught or blocked. */
    Mini__Sig__Tstp   = 20,              /**< Terminal stop request. */
    Mini__Sig__Ttin   = 21,              /**< Background terminal read. */
    Mini__Sig__Ttou   = 22,              /**< Background terminal write. */
    Mini__Sig__Urg    = 23,              /**< Urgent data available on a socket. */
    Mini__Sig__Xcpu   = 24,              /**< CPU time limit exceeded. */
    Mini__Sig__Xfsz   = 25,              /**< File size limit exceeded. */
    Mini__Sig__VtAlrm = 26,              /**< Virtual interval timer expired. */
    Mini__Sig__Prof   = 27,              /**< Profiling timer expired. */
    Mini__Sig__Winch  = 28,              /**< Terminal window size changed. */
    Mini__Sig__Io     = 29,              /**< Asynchronous I/O event. */
    Mini__Sig__Poll   = Mini__Sig__Io,   /**< Alternate name for Mini__Sig__Io. */
    Mini__Sig__Pwr    = 30,              /**< Power failure. */
    Mini__Sig__Sys    = 31,              /**< Bad system call. */
    Mini__Sig__Unused = Mini__Sig__Sys,  /**< Historical name for Mini__Sig__Sys. */
    Mini__Sig__RtMin  = 32,              /**< First real-time signal number. */
    Mini__Sig__RtMax  = 64,              /**< Last real-time signal number. */
} Mini__Sig;

/**
 * @brief Sends a process-directed signal using Linux `kill` target selection.
 * @param pid Process ID or Linux process-group selector.
 * @param sig Signal number. Mini__Sig__None checks the target and permissions without delivery.
 * @return Zero on success or a negative Linux error number.
 */
[[nodiscard]]
Mini__I32 Mini__SysKill(Mini__I32 pid, Mini__I32 sig);

/**
 * @brief Sends a signal to a specific thread.
 * @param pid Process ID of the thread's owner.
 * @param tid Kernel thread ID of a thread belonging to @p pid.
 * @param sig Signal number. Mini__Sig__None checks the target and permissions without delivery.
 * @return Zero on success or a negative Linux error number.
 */
[[nodiscard]]
Mini__I32 Mini__SysThreadKill(Mini__I32 pid, Mini__I32 tid, Mini__I32 sig);

/** @brief Signal mask in which signal number `n` uses bit `n - 1`. */
typedef Mini__U64 Mini__SigSet;

/** @brief Flags for installing a signal action. Combine them with bitwise OR. */
typedef enum Mini__SigActionFlag : Mini__U32 {
    Mini__SigActionFlag__NoCldStop = 0x00000001, /**< Suppress stop and resume notifications. */
    Mini__SigActionFlag__NoCldWait = 0x00000002, /**< Prevent exited children becoming zombies. */
    Mini__SigActionFlag__SigInfo   = 0x00000004, /**< Select Mini__SigHandler::with_info. */
    Mini__SigActionFlag__OnStack   = 0x08000000, /**< Use an alternate stack when available. */
    Mini__SigActionFlag__Restart   = 0x10000000, /**< Restart eligible interrupted syscalls. */
    Mini__SigActionFlag__NoDefer   = 0x40000000, /**< Skip automatic blocking of this signal. */
    Mini__SigActionFlag__ResetHand = 0x80000000, /**< Restore the default action on entry. */
} Mini__SigActionFlag;

/** @brief Handler forms selected by Mini__SigActionFlag__SigInfo. */
typedef union Mini__SigHandler {
    /** @brief Receives the delivered signal number. */
    void (*simple)(Mini__I32 sig);

    /**
     * @brief Receives the signal number, kernel signal information, and saved user context.
     *
     * The `info` and `context` pointers are borrowed for the duration of the handler call.
     */
    void (*with_info)(Mini__I32 sig, Mini__Any *info, Mini__Any *context);
} Mini__SigHandler;

/** @brief Value for `handler.simple` that selects the kernel's default disposition. */
#define Mini__SigHandler__Default ((void (*)(Mini__I32)) 0)

/** @brief Value for `handler.simple` that tells the kernel to ignore the signal. */
#define Mini__SigHandler__Ignore  ((void (*)(Mini__I32)) 1)

/** @brief Disposition and handler settings for one signal. */
typedef struct Mini__SigAction {
    /** @brief Use `with_info` with Mini__SigActionFlag__SigInfo and `simple` otherwise. */
    Mini__SigHandler handler;

    /** @brief Bitwise OR of Mini__SigActionFlag values, or zero. */
    Mini__U32 flags;

    /** @brief Additional signals to block while the handler runs. */
    Mini__SigSet mask;
} Mini__SigAction;

/**
 * @brief Queries or changes the process-wide disposition of a signal.
 * @param sig Signal number whose disposition to query or change.
 * @param[in] action New action, or null to leave the disposition alone.
 * @param[out] old_action Receives the previous action on success, or null to skip it.
 * @return Zero on success or a negative Linux error number.
 *
 * The runtime supplies the signal restorer. Both pointers may refer to the same object.
 */
[[nodiscard]]
Mini__I32 Mini__SysSigAction(
    Mini__I32 sig,
    const Mini__SigAction *action,
    Mini__SigAction *old_action
);

/** @brief Operations that change the calling thread's signal mask. */
typedef enum Mini__SigMaskHow {
    Mini__SigMaskHow__Block   = 0, /**< Add the supplied signals to the blocked set. */
    Mini__SigMaskHow__Unblock = 1, /**< Remove the supplied signals from the blocked set. */
    Mini__SigMaskHow__SetMask = 2, /**< Replace the blocked set with the supplied set. */
} Mini__SigMaskHow;

/**
 * @brief Queries or changes the calling thread's blocked signal set.
 * @param how Operation from Mini__SigMaskHow. Ignored when @p set is null.
 * @param[in] set Signal set for the operation, or null to query without changing the mask.
 * @param[out] old_set Receives the previous mask on success, or null to skip it.
 * @return Zero on success or a negative Linux error number.
 */
[[nodiscard]]
Mini__I32 Mini__SysProcMask(Mini__I32 how, const Mini__SigSet *set, Mini__SigSet *old_set);

/** @brief Conventional successful exit status, zero. */
extern const Mini__I32 Mini__OkExitCode;

/** @brief Conventional generic failure exit status, one. */
extern const Mini__I32 Mini__ErrExitCode;

/**
 * @brief Terminates the process, including all its threads.
 * @param status Exit status. A waiting parent can observe the low eight bits.
 */
[[noreturn]]
void Mini__SysExit(Mini__I32 status);

/**
 * @brief Sends a signal to the calling thread.
 * @param sig Signal number.
 * @return Zero on success or a negative Linux error number.
 */
[[nodiscard]]
Mini__I32 Mini__SysRaise(Mini__I32 sig);

/**
 * @brief Terminates the process using Mini__Sig__Abrt.
 *
 * The first caller unblocks the signal and attempts to run the installed handler. If that
 * attempt returns, or a later caller enters, the runtime restores the default disposition and
 * raises the signal again. If execution continues, it exits with status `128 + SIGABRT`.
 */
[[noreturn]]
void Mini__SysAbort(void);

/**
 * @brief Reads up to a requested number of bytes from a file descriptor.
 * @param fd Open file descriptor.
 * @param[out] buf Writable destination buffer of at least @p count bytes.
 * @param count Maximum number of bytes to read.
 * @return Number of bytes read, zero at end of file or on a successful zero-byte read, or a
 *         negative Linux error number. A successful read may be shorter than @p count.
 */
[[nodiscard]]
Mini__I64 Mini__SysRead(Mini__I32 fd, Mini__Any *buf, Mini__USize count);

/**
 * @brief Writes up to a requested number of bytes to a file descriptor.
 * @param fd Open file descriptor.
 * @param[in] buf Readable source buffer of at least @p count bytes.
 * @param count Number of bytes to write.
 * @return Number of bytes written or a negative Linux error number. A successful write may be
 *         shorter than @p count.
 */
[[nodiscard]]
Mini__I64 Mini__SysWrite(Mini__I32 fd, const Mini__Any *buf, Mini__USize count);

/** @brief Origins for offsets passed to Mini__SysSeek. */
typedef enum {
    Mini__SeekWhence__Set = 0, /**< Offset from the start of the file. */
    Mini__SeekWhence__Cur = 1, /**< Offset from the current position. */
    Mini__SeekWhence__End = 2, /**< Offset from the end of the file. */
} Mini__SeekWhence;

/**
 * @brief Changes the current offset of a seekable file descriptor.
 * @param fd Open, seekable file descriptor.
 * @param offset Signed byte displacement relative to @p whence.
 * @param whence Origin from Mini__SeekWhence.
 * @return New byte offset from the start of the file or a negative Linux error number.
 */
[[nodiscard]]
Mini__I64 Mini__SysSeek(Mini__I32 fd, Mini__I64 offset, Mini__I32 whence);

/**
 * @brief Access modes and flags for Mini__SysOpen and Mini__SysOpenAt.
 *
 * Choose one access mode and combine it with any required flags using bitwise OR.
 */
typedef enum {
    Mini__OpenFlag__RdOnly = 0,     /**< Open for reading only. */
    Mini__OpenFlag__WrOnly = 1,     /**< Open for writing only. */
    Mini__OpenFlag__RdWr   = 2,     /**< Open for reading and writing. */
    Mini__OpenFlag__Creat  = 0100,  /**< Create the file if it does not exist. */
    Mini__OpenFlag__Excl   = 0200,  /**< With Mini__OpenFlag__Creat, fail if the path exists. */
    Mini__OpenFlag__Trunc  = 01000, /**< Truncate an existing regular file opened for writing. */
    Mini__OpenFlag__Append = 02000, /**< Position each write at the end of the file. */
} Mini__OpenFlag;

/**
 * @brief Opens a path, resolving relative paths from the current working directory.
 * @param[in] path Null-terminated path.
 * @param flags Access mode and optional flags from Mini__OpenFlag.
 * @param mode Permission bits when creating a file, subject to the process umask.
 * @return A new file descriptor to close with Mini__SysClose or a negative Linux error number.
 */
[[nodiscard]]
Mini__I32 Mini__SysOpen(const char *path, Mini__I32 flags, Mini__U32 mode);

/** @brief Directory selector for resolving relative paths from the current working directory. */
extern const Mini__I32 Mini__AtFdcwd;

/**
 * @brief Opens a path relative to a directory descriptor.
 * @param dir_fd Directory descriptor or Mini__AtFdcwd. Ignored for an absolute @p path.
 * @param[in] path Null-terminated path.
 * @param flags Access mode and optional flags from Mini__OpenFlag.
 * @param mode Permission bits when creating a file, subject to the process umask.
 * @return A new file descriptor to close with Mini__SysClose or a negative Linux error number.
 */
[[nodiscard]]
Mini__I32 Mini__SysOpenAt(Mini__I32 dir_fd, const char *path, Mini__I32 flags, Mini__U32 mode);

/**
 * @brief Opens a file for writing, creating it if needed or truncating it if it exists.
 * @param[in] path Null-terminated path. Relative paths use the current working directory.
 * @param mode Permission bits when creating a file, subject to the process umask.
 * @return A new file descriptor to close with Mini__SysClose or a negative Linux error number.
 */
[[nodiscard]]
Mini__I32 Mini__SysCreate(const char *path, Mini__U32 mode);

/**
 * @brief Closes an open file descriptor.
 * @param fd File descriptor to release.
 * @return Zero on success or a negative Linux error number.
 */
[[nodiscard]]
Mini__I32 Mini__SysClose(Mini__I32 fd);

/** @brief Access protections for a memory mapping. Combine permissions with bitwise OR. */
typedef enum {
    Mini__MmapProt__None  = 0,   /**< Forbid access. */
    Mini__MmapProt__Read  = 0x1, /**< Allow reads. */
    Mini__MmapProt__Write = 0x2, /**< Allow writes. */
    Mini__MmapProt__Exec  = 0x4, /**< Allow execution. */
} Mini__MmapProt;

/** @brief Sharing and backing flags for memory mappings. */
typedef enum {
    Mini__MmapFlag__Shared    = 0x01, /**< Share updates with other mappings of the region. */
    Mini__MmapFlag__Private   = 0x02, /**< Keep writes private to this mapping. */
    Mini__MmapFlag__Anonymous = 0x20, /**< Use zero-filled memory without a backing file. */
} Mini__MmapFlag;

/**
 * @brief Maps file-backed or anonymous memory into the process address space.
 * @param address Address hint, or null for a kernel-selected address.
 * @param length Nonzero mapping length in bytes.
 * @param protection Access protections from Mini__MmapProt.
 * @param flags Mini__MmapFlag__Shared or Mini__MmapFlag__Private, optionally combined with
 *              Mini__MmapFlag__Anonymous.
 * @param fd Backing file descriptor. Pass `-1` for an anonymous mapping.
 * @param offset Page-aligned byte offset into the backing file. Pass zero for an anonymous map.
 * @return Mapped address as a Mini__IPtr on success or a negative Linux error number. Check
 *         for an error before converting to a pointer. Release the mapping with Mini__SysMunmap.
 */
[[nodiscard]]
Mini__IPtr Mini__SysMmap(
    Mini__Any *address,
    Mini__USize length,
    Mini__I32 protection,
    Mini__I32 flags,
    Mini__I32 fd,
    Mini__I64 offset
);

/**
 * @brief Unmaps the pages covered by an address range.
 * @param address Page-aligned start of the range.
 * @param length Nonzero length in bytes. Every page intersecting the range is unmapped.
 * @return Zero on success or a negative Linux error number.
 */
[[nodiscard]]
Mini__I32 Mini__SysMunmap(Mini__Any *address, Mini__USize length);

#endif // Mini__SysH_

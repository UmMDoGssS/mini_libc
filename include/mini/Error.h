/** @file
 * @brief Panic and typed results for recoverable errors.
 */

#ifndef Mini__ErrorH_
#define Mini__ErrorH_

#include "Types.h"
#include "Macros.h"

#define Mini__PanicLocation_ "Panic at " __FILE__ ":" Mini__StringifyMacro(__LINE__) "\n"

[[noreturn]]
void Mini__Panic_(const char *location, Mini__USize length);

/**
 * @brief Attempts to write the expansion's file and line to standard error, then aborts.
 * @see Mini__SysAbort
 */
#define Mini__Panic() Mini__Panic_(Mini__PanicLocation_, sizeof(Mini__PanicLocation_) - 1)

/**
 * @brief Names the result type defined for a success and error type pair.
 * @param T Single-token success type name.
 * @param E Single-token error type name.
 * @see Mini__DefineRes
 */
#define Mini__Res(T, E) \
    Mini__ConcatMacro(Mini__Res_, Mini__ConcatMacro(T, Mini__ConcatMacro(_, E)))

/**
 * @brief Accesses the read-only method table for a result type.
 * @param T Single-token success type name.
 * @param E Single-token error type name.
 *
 * - `MakeOk(value)` constructs a result containing a success value of type @p T.
 * - `MakeErr(error)` constructs a result containing an error value of type @p E.
 * - `IsOk(self)` tests whether the result contains a success value.
 * - `IsErr(self)` tests whether the result contains an error value.
 * - `GetOk(self)` returns a read-only pointer to the success value, or `nullptr` on an error.
 * - `GetErr(self)` returns a read-only pointer to the error value, or `nullptr` on success.
 * - `Unwrap(self)` returns the success value by value and panics on an error.
 * - `UnwrapOr(self, fallback)` returns the success value or the supplied fallback by value.
 *
 * Pass a non-null pointer to an initialized result as `self`. Pointers returned by `GetOk`
 * and `GetErr` borrow the payload and are valid while the result lives and holds that variant.
 * The call to `UnwrapOr` evaluates its fallback argument even when the result contains a
 * success value. `Unwrap` reports the location of the Mini__DefineRes expansion when it
 * panics.
 * @see Mini__DefineRes
 */
#define Mini__ResMth(T, E) \
    Mini__ConcatMacro(Mini__ResMth_, Mini__ConcatMacro(T, Mini__ConcatMacro(_, E)))

/**
 * @brief Defines a result type and its method table for a success and error type pair.
 * @param T Single-token success type name.
 * @param E Single-token error type name.
 *
 * Invoke once per pair in each translation unit that uses it, at file scope and with a
 * trailing semicolon. A shared header can provide the definition to multiple translation
 * units. Use typedefs for types spelled with multiple tokens.
 *
 * @code{.c}
 * #include <mini/Error.h>
 * Mini__DefineRes(Mini__USize, Mini__I32);
 *
 * void Example(void) {
 *     Mini__Res(Mini__USize, Mini__I32) res =
 *         Mini__ResMth(Mini__USize, Mini__I32).MakeOk(42);
 *     Mini__USize size = Mini__ResMth(Mini__USize, Mini__I32).Unwrap(&res);
 *     (void) size;
 * }
 * @endcode
 * @see Mini__Res, Mini__ResMth
 */
#define Mini__DefineRes(T, E)                                                                 \
    Mini__DeclareSumType(Mini__Res(T, E), (T, Ok, ok), (E, Err, err))                         \
                                                                                              \
    /* MakeOk(T val) -> Self */                                                               \
    static inline Mini__Res(T, E) Mini__ConcatMacro(Mini__ResMth(T, E), __MakeOk_)(T val) {   \
        return (Mini__Res(T, E)) {                                                            \
            .tag_ = Mini__ConcatMacro(Mini__Res(T, E), __Ok_),                                \
            .ok_ = val,                                                                       \
        };                                                                                    \
    }                                                                                         \
                                                                                              \
    /* MakeErr(T val) -> Self */                                                              \
    static inline Mini__Res(T, E) Mini__ConcatMacro(Mini__ResMth(T, E), __MakeErr_)(E err) {  \
        return (Mini__Res(T, E)) {                                                            \
            .tag_ = Mini__ConcatMacro(Mini__Res(T, E), __Err_),                               \
            .err_ = err,                                                                      \
        };                                                                                    \
    }                                                                                         \
                                                                                              \
    /* IsOk(self) -> bool */                                                                  \
    static inline bool Mini__ConcatMacro(Mini__ResMth(T, E), __IsOk_)(                        \
        const Mini__Res(T, E) *self                                                           \
    ) {                                                                                       \
        return self->tag_ == Mini__ConcatMacro(Mini__Res(T, E), __Ok_);                       \
    }                                                                                         \
                                                                                              \
    /* IsErr(self) -> bool */                                                                 \
    static inline bool Mini__ConcatMacro(Mini__ResMth(T, E), __IsErr_)(                       \
        const Mini__Res(T, E) *self                                                           \
    ) {                                                                                       \
        return self->tag_ == Mini__ConcatMacro(Mini__Res(T, E), __Err_);                      \
    }                                                                                         \
                                                                                              \
    /* GetOk(self) -> const T * */                                                            \
    static inline const T *Mini__ConcatMacro(Mini__ResMth(T, E), __GetOk_)(                   \
        const Mini__Res(T, E) *self                                                           \
    ) {                                                                                       \
        return Mini__ConcatMacro(Mini__ResMth(T, E), __IsOk_)(self) ? &self->ok_ : nullptr;   \
    }                                                                                         \
                                                                                              \
    /* GetErr(self) -> const E * */                                                           \
    static inline const E *Mini__ConcatMacro(Mini__ResMth(T, E), __GetErr_)(                  \
        const Mini__Res(T, E) *self                                                           \
    ) {                                                                                       \
        return Mini__ConcatMacro(Mini__ResMth(T, E), __IsErr_)(self) ? &self->err_ : nullptr; \
    }                                                                                         \
                                                                                              \
    /* Unwrap(self) -> T */                                                                   \
    static inline T Mini__ConcatMacro(Mini__ResMth(T, E), __Unwrap_)(                         \
        const Mini__Res(T, E) *self                                                           \
    ) {                                                                                       \
        if (Mini__ConcatMacro(Mini__ResMth(T, E), __IsErr_)(self)) {                          \
            Mini__Panic();                                                                    \
        }                                                                                     \
                                                                                              \
        return self->ok_;                                                                     \
    }                                                                                         \
                                                                                              \
    /* UnwrapOr(self, T val) -> T */                                                          \
    static inline T Mini__ConcatMacro(Mini__ResMth(T, E), __UnwrapOr_)(                       \
        const Mini__Res(T, E) *self,                                                          \
        T val                                                                                 \
    ) {                                                                                       \
        if (Mini__ConcatMacro(Mini__ResMth(T, E), __IsErr_)(self)) {                          \
            return val;                                                                       \
        }                                                                                     \
                                                                                              \
        return self->ok_;                                                                     \
    }                                                                                         \
                                                                                              \
    [[maybe_unused]] static const struct {                                                    \
        [[nodiscard]]                                                                         \
        Mini__Res(T, E) (*MakeOk)(T val);                                                     \
        [[nodiscard]]                                                                         \
        Mini__Res(T, E) (*MakeErr)(E err);                                                    \
                                                                                              \
        [[nodiscard, gnu::nonnull(1)]]                                                        \
        bool (*IsOk)(const Mini__Res(T, E) *self);                                            \
        [[nodiscard, gnu::nonnull(1)]]                                                        \
        bool (*IsErr)(const Mini__Res(T, E) *self);                                           \
                                                                                              \
        [[nodiscard, gnu::nonnull(1)]]                                                        \
        const T *(*GetOk)(const Mini__Res(T, E) *self);                                       \
        [[nodiscard, gnu::nonnull(1)]]                                                        \
        const E *(*GetErr)(const Mini__Res(T, E) *self);                                      \
                                                                                              \
        [[nodiscard, gnu::nonnull(1)]]                                                        \
        T (*Unwrap)(const Mini__Res(T, E) *self);                                             \
        [[nodiscard, gnu::nonnull(1)]]                                                        \
        T (*UnwrapOr)(const Mini__Res(T, E) *self, T val);                                    \
    } Mini__ResMth(T, E) = {                                                                  \
        .MakeOk   = Mini__ConcatMacro(Mini__ResMth(T, E), __MakeOk_),                         \
        .MakeErr  = Mini__ConcatMacro(Mini__ResMth(T, E), __MakeErr_),                        \
        .IsOk     = Mini__ConcatMacro(Mini__ResMth(T, E), __IsOk_),                           \
        .IsErr    = Mini__ConcatMacro(Mini__ResMth(T, E), __IsErr_),                          \
        .GetOk    = Mini__ConcatMacro(Mini__ResMth(T, E), __GetOk_),                          \
        .GetErr   = Mini__ConcatMacro(Mini__ResMth(T, E), __GetErr_),                         \
        .Unwrap   = Mini__ConcatMacro(Mini__ResMth(T, E), __Unwrap_),                         \
        .UnwrapOr = Mini__ConcatMacro(Mini__ResMth(T, E), __UnwrapOr_),                       \
    }

#endif // Mini__ErrorH_

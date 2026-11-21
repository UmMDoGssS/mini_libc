/** @file
 * @brief Panic, typed results, and optional values.
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

/**
 * @brief Names the option type defined for a payload type.
 * @param T Single-token payload type name.
 * @see Mini__DefineOpt
 */
#define Mini__Opt(T) Mini__ConcatMacro(Mini__Opt_, T)

/**
 * @brief Accesses the read-only method table for an option type.
 * @param T Single-token payload type name.
 *
 * - `MakeSome(value)` constructs an option containing a value of type @p T.
 * - `MakeNone()` constructs an empty option.
 * - `IsSome(self)` tests whether the option contains a value.
 * - `IsNone(self)` tests whether the option is empty.
 * - `GetSome(self)` returns a read-only pointer to the payload, or `nullptr` if empty.
 * - `Unwrap(self)` returns the payload by value and panics if empty.
 * - `UnwrapOr(self, fallback)` returns the payload or the fallback by value.
 *
 * Pass a non-null pointer to an initialized option as `self`. `GetSome` borrows the payload
 * while the option lives and holds `Some`. `UnwrapOr` always evaluates the fallback argument.
 * `Unwrap` reports the location of the Mini__DefineOpt expansion when it panics.
 * @see Mini__DefineOpt
 */
#define Mini__OptMth(T) Mini__ConcatMacro(Mini__OptMth_, T)

/**
 * @brief Defines an option type and its method table for a payload type.
 * @param T Single-token payload type name.
 *
 * Invoke once per type in each translation unit that uses it, at file scope with a trailing
 * semicolon. A shared header can provide the definition to multiple translation units.
 * Use a typedef for types spelled with multiple tokens. A zero-initialized option is `None`.
 *
 * @code{.c}
 * #include <mini/Error.h>
 * Mini__DefineOpt(Mini__USize);
 *
 * void Example(void) {
 *     Mini__Opt(Mini__USize) opt = Mini__OptMth(Mini__USize).MakeSome(42);
 *     Mini__USize size = Mini__OptMth(Mini__USize).UnwrapOr(&opt, 0);
 *     (void) size;
 * }
 * @endcode
 * @see Mini__Opt, Mini__OptMth
 */
#define Mini__DefineOpt(T)                                                                       \
    Mini__DeclareSumType(Mini__Opt(T), (Mini__Byte, None, none), (T, Some, some))                \
                                                                                                 \
    /* MakeSome(T val) -> Self */                                                                \
    static inline Mini__Opt(T) Mini__ConcatMacro(Mini__OptMth(T), __MakeSome_)(T val) {          \
        return (Mini__Opt(T)) {                                                                  \
            .tag_ = Mini__ConcatMacro(Mini__Opt(T), __Some_),                                    \
            .some_ = val,                                                                        \
        };                                                                                       \
    }                                                                                            \
                                                                                                 \
    /* MakeNone() -> Self */                                                                     \
    static inline Mini__Opt(T) Mini__ConcatMacro(Mini__OptMth(T), __MakeNone_)(void) {           \
        return (Mini__Opt(T)) {                                                                  \
            .tag_ = Mini__ConcatMacro(Mini__Opt(T), __None_),                                    \
            .none_ = 0,                                                                          \
        };                                                                                       \
    }                                                                                            \
                                                                                                 \
    /* IsSome(self) -> bool */                                                                   \
    static inline bool Mini__ConcatMacro(Mini__OptMth(T), __IsSome_)(const Mini__Opt(T) *self) { \
        return self->tag_ == Mini__ConcatMacro(Mini__Opt(T), __Some_);                           \
    }                                                                                            \
                                                                                                 \
    /* IsNone(self) -> bool */                                                                   \
    static inline bool Mini__ConcatMacro(Mini__OptMth(T), __IsNone_)(const Mini__Opt(T) *self) { \
        return self->tag_ == Mini__ConcatMacro(Mini__Opt(T), __None_);                           \
    }                                                                                            \
                                                                                                 \
    /* GetSome(self) -> T* */                                                                    \
    static inline const T *Mini__ConcatMacro(Mini__OptMth(T), __GetSome_)(                       \
        const Mini__Opt(T) *self                                                                 \
    ) {                                                                                          \
        return Mini__ConcatMacro(Mini__OptMth(T), __IsSome_)(self) ? &self->some_ : nullptr;     \
    }                                                                                            \
                                                                                                 \
    /* Unwrap(self) -> T */                                                                      \
    static inline T Mini__ConcatMacro(Mini__OptMth(T), __Unwrap_)(const Mini__Opt(T) *self) {    \
        if (!Mini__ConcatMacro(Mini__OptMth(T), __IsSome_)(self)) {                              \
            Mini__Panic();                                                                       \
        }                                                                                        \
                                                                                                 \
        return self->some_;                                                                      \
    }                                                                                            \
                                                                                                 \
    /* UnwrapOr(self, T val) -> T */                                                             \
    static inline T Mini__ConcatMacro(Mini__OptMth(T), __UnwrapOr_)(                             \
        const Mini__Opt(T) *self,                                                                \
        T val                                                                                    \
    ) {                                                                                          \
        return Mini__ConcatMacro(Mini__OptMth(T), __IsSome_)(self) ? self->some_ : val;          \
    }                                                                                            \
                                                                                                 \
    [[maybe_unused]] static const struct {                                                       \
        [[nodiscard]]                                                                            \
        Mini__Opt(T) (*MakeSome)(T val);                                                         \
        [[nodiscard]]                                                                            \
        Mini__Opt(T) (*MakeNone)(void);                                                          \
                                                                                                 \
        [[nodiscard, gnu::nonnull(1)]]                                                           \
        bool (*IsSome)(const Mini__Opt(T) *self);                                                \
        [[nodiscard, gnu::nonnull(1)]]                                                           \
        bool (*IsNone)(const Mini__Opt(T) *self);                                                \
                                                                                                 \
        [[nodiscard, gnu::nonnull(1)]]                                                           \
        const T *(*GetSome)(const Mini__Opt(T) *self);                                           \
        [[nodiscard, gnu::nonnull(1)]]                                                           \
        T (*Unwrap)(const Mini__Opt(T) *self);                                                   \
        [[nodiscard, gnu::nonnull(1)]]                                                           \
        T (*UnwrapOr)(const Mini__Opt(T) *self, T val);                                          \
    } Mini__OptMth(T) = {                                                                        \
        .MakeSome = Mini__ConcatMacro(Mini__OptMth(T), __MakeSome_),                             \
        .MakeNone = Mini__ConcatMacro(Mini__OptMth(T), __MakeNone_),                             \
        .IsSome   = Mini__ConcatMacro(Mini__OptMth(T), __IsSome_),                               \
        .IsNone   = Mini__ConcatMacro(Mini__OptMth(T), __IsNone_),                               \
        .GetSome  = Mini__ConcatMacro(Mini__OptMth(T), __GetSome_),                              \
        .Unwrap   = Mini__ConcatMacro(Mini__OptMth(T), __Unwrap_),                               \
        .UnwrapOr = Mini__ConcatMacro(Mini__OptMth(T), __UnwrapOr_),                             \
    }

#endif // Mini__ErrorH_

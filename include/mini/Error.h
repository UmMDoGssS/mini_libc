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
 * @see Mini__DefineResult
 */
#define Mini__Result(T, E) \
    Mini__ConcatMacro(Mini__Result_, Mini__ConcatMacro(T, Mini__ConcatMacro(_, E)))

/**
 * @brief Accesses the read-only method table for a result type.
 * @param T Single-token success type name.
 * @param E Single-token error type name.
 *
 * - `MakeOk(value)` constructs a result containing a success value of type @p T.
 * - `MakeErr(error)` constructs a result containing an error value of type @p E.
 * - `IsOk(self)` tests whether the result contains a success value.
 * - `IsErr(self)` tests whether the result contains an error value.
 * - `Unwrap(self)` returns the success value by value and panics on an error.
 * - `UnwrapOr(self, fallback)` returns the success value or the supplied fallback by value.
 *
 * Pass a non-null pointer to an initialized result as `self`. The methods borrow the pointer
 * for the duration of the call. The call to `UnwrapOr` evaluates its fallback argument even
 * when the result contains a success value. `Unwrap` reports the location of the
 * Mini__DefineResult expansion when it panics.
 * @see Mini__DefineResult
 */
#define Mini__ResultMth(T, E) \
    Mini__ConcatMacro(Mini__ResultMth_, Mini__ConcatMacro(T, Mini__ConcatMacro(_, E)))

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
 * Mini__DefineResult(Mini__USize, Mini__I32);
 *
 * void Example(void) {
 *     Mini__Result(Mini__USize, Mini__I32) result =
 *         Mini__ResultMth(Mini__USize, Mini__I32).MakeOk(42);
 *     Mini__USize size = Mini__ResultMth(Mini__USize, Mini__I32).Unwrap(&result);
 *     (void) size;
 * }
 * @endcode
 * @see Mini__Result, Mini__ResultMth
 */
#define Mini__DefineResult(T, E)                                                                   \
    Mini__DeclareSumType(Mini__Result(T, E), (T, Ok, ok), (E, Err, err))                           \
                                                                                                   \
    /* MakeOk(T val) -> Self */                                                                    \
    static inline Mini__Result(T, E) Mini__ConcatMacro(Mini__ResultMth(T, E), __MakeOk_)(T val) {  \
        return (Mini__Result(T, E)) {                                                              \
            .tag_ = Mini__ConcatMacro(Mini__Result(T, E), __Ok_),                                  \
            .ok_ = val,                                                                            \
        };                                                                                         \
    }                                                                                              \
                                                                                                   \
    /* MakeErr(T val) -> Self */                                                                   \
    static inline Mini__Result(T, E) Mini__ConcatMacro(Mini__ResultMth(T, E), __MakeErr_)(E err) { \
        return (Mini__Result(T, E)) {                                                              \
            .tag_ = Mini__ConcatMacro(Mini__Result(T, E), __Err_),                                 \
            .err_ = err,                                                                           \
        };                                                                                         \
    }                                                                                              \
                                                                                                   \
    /* IsOk(self) -> bool */                                                                       \
    static inline bool Mini__ConcatMacro(Mini__ResultMth(T, E), __IsOk_)(                          \
        Mini__Result(T, E) *self                                                                   \
    ) {                                                                                            \
        return self->tag_ == Mini__ConcatMacro(Mini__Result(T, E), __Ok_);                         \
    }                                                                                              \
                                                                                                   \
    /* IsErr(self) -> bool */                                                                      \
    static inline bool Mini__ConcatMacro(Mini__ResultMth(T, E), __IsErr_)(                         \
        Mini__Result(T, E) *self                                                                   \
    ) {                                                                                            \
        return self->tag_ == Mini__ConcatMacro(Mini__Result(T, E), __Err_);                        \
    }                                                                                              \
                                                                                                   \
    /* Unwrap(self) -> T */                                                                        \
    static inline T Mini__ConcatMacro(Mini__ResultMth(T, E), __Unwrap_)(                           \
        Mini__Result(T, E) *self                                                                   \
    ) {                                                                                            \
        if (Mini__ConcatMacro(Mini__ResultMth(T, E), __IsErr_)(self)) {                            \
            Mini__Panic();                                                                         \
        }                                                                                          \
                                                                                                   \
        return self->ok_;                                                                          \
    }                                                                                              \
                                                                                                   \
    /* UnwrapOr(self, T val) -> T */                                                               \
    static inline T Mini__ConcatMacro(Mini__ResultMth(T, E), __UnwrapOr_)(                         \
        Mini__Result(T, E) *self,                                                                  \
        T val                                                                                      \
    ) {                                                                                            \
        if (Mini__ConcatMacro(Mini__ResultMth(T, E), __IsErr_)(self)) {                            \
            return val;                                                                            \
        }                                                                                          \
                                                                                                   \
        return self->ok_;                                                                          \
    }                                                                                              \
                                                                                                   \
    [[maybe_unused]] static const struct {                                                         \
        [[nodiscard]]                                                                              \
        Mini__Result(T, E) (*MakeOk)(T val);                                                       \
        [[nodiscard]]                                                                              \
        Mini__Result(T, E) (*MakeErr)(E err);                                                      \
                                                                                                   \
        [[nodiscard, gnu::nonnull(1)]]                                                             \
        bool (*IsOk)(Mini__Result(T, E) *self);                                                    \
        [[nodiscard, gnu::nonnull(1)]]                                                             \
        bool (*IsErr)(Mini__Result(T, E) *self);                                                   \
                                                                                                   \
        [[nodiscard, gnu::nonnull(1)]]                                                             \
        T (*Unwrap)(Mini__Result(T, E) *self);                                                     \
        [[nodiscard, gnu::nonnull(1)]]                                                             \
        T (*UnwrapOr)(Mini__Result(T, E) *self, T val);                                            \
    } Mini__ResultMth(T, E) = {                                                                    \
        .MakeOk   = Mini__ConcatMacro(Mini__ResultMth(T, E), __MakeOk_),                           \
        .MakeErr  = Mini__ConcatMacro(Mini__ResultMth(T, E), __MakeErr_),                          \
        .IsOk     = Mini__ConcatMacro(Mini__ResultMth(T, E), __IsOk_),                             \
        .IsErr    = Mini__ConcatMacro(Mini__ResultMth(T, E), __IsErr_),                            \
        .Unwrap   = Mini__ConcatMacro(Mini__ResultMth(T, E), __Unwrap_),                           \
        .UnwrapOr = Mini__ConcatMacro(Mini__ResultMth(T, E), __UnwrapOr_),                         \
    }

#endif // Mini__ErrorH_

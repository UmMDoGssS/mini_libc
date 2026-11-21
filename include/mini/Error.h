#ifndef Mini__ErrorH_
#define Mini__ErrorH_

#include "Types.h"
#include "Macros.h"

#define Mini__PanicLocation_ "Panic at " __FILE__ ":" Mini__StringifyMacro(__LINE__) "\n"

[[noreturn]]
Mini__Void Mini__Panic_(const Mini__Char *location, Mini__USize length);

#define Mini__Panic() Mini__Panic_(Mini__PanicLocation_, sizeof(Mini__PanicLocation_) - 1)

// Use single-token type names for T and E. Give multi-token types a typedef.
#define Mini__ResultType(T, E) \
    Mini__ConcatMacro(Mini__ResultType_, Mini__ConcatMacro(T, Mini__ConcatMacro(_, E)))

#define Mini__ResultMethods(T, E) \
    Mini__ConcatMacro(Mini__ResultMethod_, Mini__ConcatMacro(T, Mini__ConcatMacro(_, E)))

// A failing Unwrap reports the location of this macro's expansion.
#define Mini__DefineResultType(T, E)                                                   \
    Mini__DeclareSumType(                                                              \
        Mini__ResultType(T, E),                                                        \
        (T, Ok, ok),                                                                   \
        (E, Err, err)                                                                  \
    )                                                                                  \
                                                                                       \
    /* IsOk(self) -> Bool */                                                           \
    static inline Mini__Bool Mini__ConcatMacro(Mini__ResultMethods(T, E), __IsOk_)(    \
        Mini__ResultType(T, E) *self                                                   \
    ) {                                                                                \
        return self->tag_ == Mini__ConcatMacro(Mini__ResultType(T, E), __Ok_);         \
    }                                                                                  \
                                                                                       \
    /* IsErr(self) -> Bool */                                                          \
    static inline Mini__Bool Mini__ConcatMacro(Mini__ResultMethods(T, E), __IsErr_)(   \
        Mini__ResultType(T, E) *self                                                   \
    ) {                                                                                \
        return self->tag_ == Mini__ConcatMacro(Mini__ResultType(T, E), __Err_);        \
    }                                                                                  \
                                                                                       \
    /* Unwrap(self) -> T */                                                            \
    static inline T Mini__ConcatMacro(Mini__ResultMethods(T, E), __Unwrap_)(           \
        Mini__ResultType(T, E) *self                                                   \
    ) {                                                                                \
        if (Mini__ConcatMacro(Mini__ResultMethods(T, E), __IsErr_)(self)) {            \
            Mini__Panic();                                                             \
        }                                                                              \
                                                                                       \
        return self->ok_;                                                              \
    }                                                                                  \
                                                                                       \
    /* UnwrapOr(self, T val) -> T */                                                   \
    static inline T Mini__ConcatMacro(Mini__ResultMethods(T, E), __UnwrapOr_)(         \
        Mini__ResultType(T, E) *self,                                                  \
        T val                                                                          \
    ) {                                                                                \
        if (Mini__ConcatMacro(Mini__ResultMethods(T, E), __IsErr_)(self)) {            \
            return val;                                                                \
        }                                                                              \
                                                                                       \
        return self->ok_;                                                              \
    }                                                                                  \
                                                                                       \
    [[maybe_unused]] static const struct {                                             \
        [[nodiscard, gnu::nonnull(1)]]                                                 \
        Mini__Bool (*IsOk)(Mini__ResultType(T, E) *self);                              \
        [[nodiscard, gnu::nonnull(1)]]                                                 \
        Mini__Bool (*IsErr)(Mini__ResultType(T, E) *self);                             \
        [[nodiscard, gnu::nonnull(1)]]                                                 \
        T (*Unwrap)(Mini__ResultType(T, E) *self);                                     \
        [[nodiscard, gnu::nonnull(1)]]                                                 \
        T (*UnwrapOr)(Mini__ResultType(T, E) *self, T val);                            \
    } Mini__ResultMethods(T, E) = {                                                    \
        .IsOk     = Mini__ConcatMacro(Mini__ResultMethods(T, E), __IsOk_),             \
        .IsErr    = Mini__ConcatMacro(Mini__ResultMethods(T, E), __IsErr_),            \
        .Unwrap   = Mini__ConcatMacro(Mini__ResultMethods(T, E), __Unwrap_),           \
        .UnwrapOr = Mini__ConcatMacro(Mini__ResultMethods(T, E), __UnwrapOr_),         \
    };

#endif // Mini__ErrorH_

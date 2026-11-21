#ifndef Mini__ErrorH_
#define Mini__ErrorH_

#include "Types.h"
#include "Macros.h"

#define Mini__PanicLocation_ "Panic at " __FILE__ ":" Mini__StringifyMacro(__LINE__) "\n"

[[noreturn]]
void Mini__Panic_(const char *location, Mini__USize length);

#define Mini__Panic() Mini__Panic_(Mini__PanicLocation_, sizeof(Mini__PanicLocation_) - 1)

// Use single-token type names for T and E. Give multi-token types a typedef.
#define Mini__Result(T, E) \
    Mini__ConcatMacro(Mini__Result_, Mini__ConcatMacro(T, Mini__ConcatMacro(_, E)))

#define Mini__ResultMth(T, E) \
    Mini__ConcatMacro(Mini__ResultMth_, Mini__ConcatMacro(T, Mini__ConcatMacro(_, E)))

// A failing Unwrap reports the location of this macro's expansion.
#define Mini__DefineResult(T, E)                                                                   \
    Mini__DeclareSumType(Mini__Result(T, E), (T, Ok, ok), (E, Err, err))                           \
                                                                                                   \
    /* MakeOk(T val) -> Self */                                                                    \
    static inline Mini__Result(T, E) Mini__ConcatMacro(Mini__ResultMth(T, E), __MakeOk_)(T val) {  \
        return (Mini__Result(T, E)) { .tag_ = Mini__ConcatMacro(Mini__Result(T, E), __Ok_),        \
            .ok_ = val };                                                                          \
    }                                                                                              \
                                                                                                   \
    /* MakeErr(T val) -> Self */                                                                   \
    static inline Mini__Result(T, E) Mini__ConcatMacro(Mini__ResultMth(T, E), __MakeErr_)(E err) { \
        return (Mini__Result(T, E)) { .tag_ = Mini__ConcatMacro(Mini__Result(T, E), __Err_),       \
            .err_ = err };                                                                         \
    }                                                                                              \
                                                                                                   \
    /* IsOk(self) -> bool */                                                                       \
    static inline bool Mini__ConcatMacro(Mini__ResultMth(T, E), __IsOk_)(                          \
        Mini__Result(T, E) * self                                                                  \
    ) {                                                                                            \
        return self->tag_ == Mini__ConcatMacro(Mini__Result(T, E), __Ok_);                         \
    }                                                                                              \
                                                                                                   \
    /* IsErr(self) -> bool */                                                                      \
    static inline bool Mini__ConcatMacro(Mini__ResultMth(T, E), __IsErr_)(                         \
        Mini__Result(T, E) * self                                                                  \
    ) {                                                                                            \
        return self->tag_ == Mini__ConcatMacro(Mini__Result(T, E), __Err_);                        \
    }                                                                                              \
                                                                                                   \
    /* Unwrap(self) -> T */                                                                        \
    static inline T Mini__ConcatMacro(Mini__ResultMth(T, E), __Unwrap_)(                           \
        Mini__Result(T, E) * self                                                                  \
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
        Mini__Result(T, E) * self,                                                                 \
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
        [[nodiscard, gnu::nonnull(1)]] bool (*IsOk)(Mini__Result(T, E) * self);                    \
        [[nodiscard, gnu::nonnull(1)]] bool (*IsErr)(Mini__Result(T, E) * self);                   \
        [[nodiscard, gnu::nonnull(1)]] T (*Unwrap)(Mini__Result(T, E) * self);                     \
        [[nodiscard, gnu::nonnull(1)]]                                                             \
        T (*UnwrapOr)(Mini__Result(T, E) * self, T val);                                           \
    } Mini__ResultMth(T, E) = {                                                                    \
        .MakeOk = Mini__ConcatMacro(Mini__ResultMth(T, E), __MakeOk_),                             \
        .MakeErr = Mini__ConcatMacro(Mini__ResultMth(T, E), __MakeErr_),                           \
        .IsOk = Mini__ConcatMacro(Mini__ResultMth(T, E), __IsOk_),                                 \
        .IsErr = Mini__ConcatMacro(Mini__ResultMth(T, E), __IsErr_),                               \
        .Unwrap = Mini__ConcatMacro(Mini__ResultMth(T, E), __Unwrap_),                             \
        .UnwrapOr = Mini__ConcatMacro(Mini__ResultMth(T, E), __UnwrapOr_),                         \
    }

#endif // Mini__ErrorH_

#include "mini/ErrorNoNamespace.h"

DefineOpt(Mini__USize);

typedef Mini__USize *SizePtr;
Mini__DefineOpt(SizePtr);

int Main(void) {
    const Opt(Mini__USize) some = OptMth(Mini__USize).MakeSome(42);
    const Opt(Mini__USize) none = OptMth(Mini__USize).MakeNone();
    const Opt(Mini__USize) empty = {};

    if (!OptMth(Mini__USize).IsSome(&some) || OptMth(Mini__USize).IsNone(&some) ||
        OptMth(Mini__USize).IsSome(&none) || !OptMth(Mini__USize).IsNone(&none) ||
        !OptMth(Mini__USize).IsNone(&empty)) {
        return 1;
    }

    const Mini__USize *payload = OptMth(Mini__USize).GetSome(&some);
    if (payload != &some.some_ || *payload != 42 || OptMth(Mini__USize).GetSome(&none) != nullptr ||
        OptMth(Mini__USize).GetSome(&empty) != nullptr) {
        return 2;
    }

    if (OptMth(Mini__USize).Unwrap(&some) != 42 || OptMth(Mini__USize).UnwrapOr(&some, 7) != 42 ||
        OptMth(Mini__USize).UnwrapOr(&none, 7) != 7) {
        return 3;
    }

    const Mini__Opt(SizePtr) some_null = Mini__OptMth(SizePtr).MakeSome(nullptr);
    const SizePtr *ptr_payload = Mini__OptMth(SizePtr).GetSome(&some_null);
    if (ptr_payload == nullptr || *ptr_payload != nullptr) {
        return 4;
    }

    return 0;
}

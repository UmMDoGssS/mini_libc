#include "ResultTestFixture.h"

int Main(void) {
    TestResult ok;
    MakeOk(&ok);

    TestResult err = Mini__ResultMth(ResultPayload, Mini__I32).MakeErr(7);

    if (!Mini__ResultMth(ResultPayload, Mini__I32).IsOk(&ok) ||
        Mini__ResultMth(ResultPayload, Mini__I32).IsErr(&ok) ||
        Mini__ResultMth(ResultPayload, Mini__I32).IsOk(&err) ||
        !Mini__ResultMth(ResultPayload, Mini__I32).IsErr(&err)) {
        return 1;
    }

    ResultPayload fallback;
    for (Mini__USize index = 0; index < sizeof(fallback.bytes); ++index) {
        fallback.bytes[index] = (Mini__Byte) (index + 1);
    }

    ResultPayload unwrapped = Mini__ResultMth(ResultPayload, Mini__I32).Unwrap(&ok);
    ResultPayload ok_or = Mini__ResultMth(ResultPayload, Mini__I32).UnwrapOr(&ok, fallback);
    ResultPayload err_or = Mini__ResultMth(ResultPayload, Mini__I32).UnwrapOr(&err, fallback);

    for (Mini__USize index = 0; index < sizeof(fallback.bytes); ++index) {
        Mini__Byte expected = (Mini__Byte) index;
        if (unwrapped.bytes[index] != expected || ok_or.bytes[index] != expected ||
            err_or.bytes[index] != (Mini__Byte) (index + 1)) {
            return 2;
        }
    }

    return 0;
}

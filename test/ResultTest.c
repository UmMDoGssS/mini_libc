#include "ResultTestFixture.h"

int Main(void) {
    TestResult ok;
    MakeOk(&ok);

    const TestResult *ok_view = &ok;
    const TestResult err = Mini__ResultMth(ResultPayload, Mini__I32).MakeErr(7);

    if (!Mini__ResultMth(ResultPayload, Mini__I32).IsOk(ok_view) ||
        Mini__ResultMth(ResultPayload, Mini__I32).IsErr(ok_view) ||
        Mini__ResultMth(ResultPayload, Mini__I32).IsOk(&err) ||
        !Mini__ResultMth(ResultPayload, Mini__I32).IsErr(&err)) {
        return 1;
    }

    const ResultPayload *ok_payload = Mini__ResultMth(ResultPayload, Mini__I32).GetOk(ok_view);
    const Mini__I32 *err_payload = Mini__ResultMth(ResultPayload, Mini__I32).GetErr(&err);
    if (ok_payload != &ok.ok_ || err_payload != &err.err_ || *err_payload != 7 ||
        Mini__ResultMth(ResultPayload, Mini__I32).GetOk(&err) != nullptr ||
        Mini__ResultMth(ResultPayload, Mini__I32).GetErr(ok_view) != nullptr) {
        return 2;
    }

    ResultPayload fallback;
    for (Mini__USize index = 0; index < sizeof(fallback.bytes); ++index) {
        fallback.bytes[index] = (Mini__Byte) (index + 1);
    }

    ResultPayload unwrapped = Mini__ResultMth(ResultPayload, Mini__I32).Unwrap(ok_view);
    ResultPayload ok_or = Mini__ResultMth(ResultPayload, Mini__I32).UnwrapOr(ok_view, fallback);
    ResultPayload err_or = Mini__ResultMth(ResultPayload, Mini__I32).UnwrapOr(&err, fallback);

    for (Mini__USize index = 0; index < sizeof(fallback.bytes); ++index) {
        Mini__Byte expected = (Mini__Byte) index;
        if (ok_payload->bytes[index] != expected || unwrapped.bytes[index] != expected ||
            ok_or.bytes[index] != expected || err_or.bytes[index] != (Mini__Byte) (index + 1)) {
            return 3;
        }
    }

    return 0;
}

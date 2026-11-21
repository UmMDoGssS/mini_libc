#include "ResultTestFixture.h"

void MakeOk(TestResult *result) {
    ResultPayload payload;
    for (Mini__USize index = 0; index < sizeof(payload.bytes); ++index) {
        payload.bytes[index] = (Mini__Byte) index;
    }
    *result = Mini__ResultMth(ResultPayload, Mini__I32).MakeOk(payload);
}

#include "ResultTestFixture.h"

void MakeOk(TestResult *result) {
    result->tag_ = Mini__ResultType_ResultPayload_Mini__I32__Ok_;
    for (Mini__USize index = 0; index < sizeof(result->ok_.bytes); ++index) {
        result->ok_.bytes[index] = (Mini__Byte) index;
    }
}

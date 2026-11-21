#include "ResTestFixture.h"

void MakeOk(TestRes *res) {
    ResPayload payload;
    for (Mini__USize index = 0; index < sizeof(payload.bytes); ++index) {
        payload.bytes[index] = (Mini__Byte) index;
    }
    *res = Mini__ResMth(ResPayload, Mini__I32).MakeOk(payload);
}

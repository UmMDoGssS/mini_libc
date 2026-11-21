#ifndef Mini__ResTestFixtureH_
#define Mini__ResTestFixtureH_

#include "mini/ErrorNoNamespace.h"

typedef struct ResPayload {
    Mini__Byte bytes[1024];
} ResPayload;

DefineRes(ResPayload, Mini__I32);
typedef Res(ResPayload, Mini__I32) TestRes;

void MakeOk(TestRes *res);

#endif // Mini__ResTestFixtureH_

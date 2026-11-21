#ifndef Mini__ResultTestFixtureH_
#define Mini__ResultTestFixtureH_

#include "mini/ErrorNoNamespace.h"

typedef struct ResultPayload {
    Mini__Byte bytes[1024];
} ResultPayload;

DefineResult(ResultPayload, Mini__I32);
typedef Result(ResultPayload, Mini__I32) TestResult;

void MakeOk(TestResult *result);

#endif // Mini__ResultTestFixtureH_

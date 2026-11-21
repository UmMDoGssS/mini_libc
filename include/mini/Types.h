#ifndef Mini__TypesH_
#define Mini__TypesH_

#include "Macros.h"

typedef __INT8_TYPE__   Mini__I8;
typedef __INT16_TYPE__  Mini__I16;
typedef __INT32_TYPE__  Mini__I32;
typedef __INT64_TYPE__  Mini__I64;

typedef __UINT8_TYPE__  Mini__U8;
typedef __UINT16_TYPE__ Mini__U16;
typedef __UINT32_TYPE__ Mini__U32;
typedef __UINT64_TYPE__ Mini__U64;

typedef __SIZE_TYPE__    Mini__USize;
typedef __PTRDIFF_TYPE__ Mini__ISize;

typedef __UINTPTR_TYPE__ Mini__UPtr;
typedef __INTPTR_TYPE__  Mini__IPtr;

typedef float  Mini__F32;
typedef double Mini__F64;

static_assert(sizeof(Mini__F32) == 4, "Invalid F32");
static_assert(sizeof(Mini__F64) == 8, "Invalid F64");

typedef void Mini__Any; // Pointer must be kept explicit (Mini__Any*)
typedef unsigned char Mini__Byte;

#endif // Mini__TypesH_

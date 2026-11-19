#ifndef Mini__IncludedTypesH
#define Mini__IncludedTypesH

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

typedef char Mini__Char;
typedef bool Mini__Bool;
typedef void Mini__Void;
typedef void Mini__Any; // Pointer must be kept explicit (Mini__Any*)

#ifdef UsingMini

#define I8 Mini__I8
#define I16 Mini__I16
#define I32 Mini__I32
#define I64 Mini__I64

#define U8 Mini__U8
#define U16 Mini__U16
#define U32 Mini__U32
#define U64 Mini__U64

#define USize Mini__USize
#define ISize Mini__ISize

#define UPtr Mini__UPtr
#define IPtr Mini__IPtr

#define F32 Mini__F32
#define F64 Mini__F64

#define Char Mini__Char
#define Bool Mini__Bool
#define Void Mini__Void
#define Any Mini__Any

#endif // UsingMini

#endif // Mini__IncludedTypesH

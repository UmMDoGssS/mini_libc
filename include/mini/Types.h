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

typedef char Mini__Char;
typedef bool Mini__Bool;
typedef void Mini__Void;
typedef void Mini__Any; // Pointer must be kept explicit (Mini__Any*)
typedef unsigned char Mini__Byte;

#define Mini__MangleTagName_(Name, Tag) \
    Mini__ConcatMacro(Name, \
        Mini__ConcatMacro(Tag, _))))

#define Mini__MangleVarName_(Var) Mini__ConcatMacro(Var, _)

#define Mini__GetTag_(Type, Tag, Var) Tag

#define Mini__MakeTagField_(Name, Tuple) \
    Mini__MangleTagName_(Name, Mini__GetTag_ Tuple),

#define Mini__MakeVarField_(Name, Tuple) \
    Mini__MakeVarFieldImpl_ Tuple

#define Mini__MakeVarFieldImpl_(Type, Tag, Var) \
    Type Mini__MangleVarName_(Var);

#define Mini__Eval(...) \
    Mini__Eval1_(Mini__Eval1_(Mini__Eval1_(__VA_ARGS__)))
#define Mini__Eval1_(...) \
    Mini__Eval2_(Mini__Eval2_(Mini__Eval2_(__VA_ARGS__)))
#define Mini__Eval2_(...) \
    Mini__Eval3_(Mini__Eval3_(Mini__Eval3_(__VA_ARGS__)))

#define Mini__Eval3_(...) __VA_ARGS__

#define Mini__Parens_ ()

#define Mini__ForEachAgain_() Mini__ForEachImpl_

#define Mini__ForEachImpl_(Macro, Name, First, ...) \
    Macro(Name, First) \
    __VA_OPT__(Mini__ForEachAgain_ Mini__Parens_ \
        (Macro, Name, __VA_ARGS__))

#define Mini__ForEach_(Macro, Name, ...) \
    __VA_OPT__(Mini__Eval( \
        Mini__ForEachImpl_(Macro, Name, __VA_ARGS__)))

#define Mini__DeclareSumType(Name, ...) \
    typedef struct Name { \
        enum { \
            Mini__ForEach_(Mini__MakeTagField_, Name, __VA_ARGS__) \
        } tag_; \
        union { \
            Mini__Byte sum_type_dummy_; \
            Mini__ForEach_(Mini__MakeVarField_, Name, __VA_ARGS__) \
        }; \
    } Name;

#endif // Mini__TypesH_

#ifndef Mini__MacrosH_
#define Mini__MacrosH_

#define Mini__ConcatMacro_(A, B) A##B
#define Mini__ConcatMacro(A, B)  Mini__ConcatMacro_(A, B)

#define Mini__StringifyMacro_(X) #X
#define Mini__StringifyMacro(X)  Mini__StringifyMacro_(X)

#define Mini__UnwrapMacro(...) __VA_ARGS__

// DeclareSumType macro

#define Mini__MangleTagName_(Name, Tag) \
    Mini__ConcatMacro(Name, Mini__ConcatMacro(__, Mini__ConcatMacro(Tag, _)))

#define Mini__MangleVarName_(Var) Mini__ConcatMacro(Var, _)

#define Mini__GetTag_(Type, Tag, Var) Tag

#define Mini__MakeTagField_(Name, Tuple) Mini__MangleTagName_(Name, Mini__GetTag_ Tuple),

#define Mini__MakeVarField_(Name, Tuple) Mini__MakeVarFieldImpl_ Tuple

#define Mini__MakeVarFieldImpl_(Type, Tag, Var) Type Mini__MangleVarName_(Var);

#define Mini__Eval_(...)  Mini__Eval1_(Mini__Eval1_(Mini__Eval1_(__VA_ARGS__)))
#define Mini__Eval1_(...) Mini__Eval2_(Mini__Eval2_(Mini__Eval2_(__VA_ARGS__)))
#define Mini__Eval2_(...) Mini__Eval3_(Mini__Eval3_(Mini__Eval3_(__VA_ARGS__)))

#define Mini__Eval3_(...) __VA_ARGS__

#define Mini__Parens_ ()

#define Mini__ForEachAgain_() Mini__ForEachImpl_

#define Mini__ForEachImpl_(Macro, Name, First, ...) \
    Macro(Name, First) __VA_OPT__(Mini__ForEachAgain_ Mini__Parens_(Macro, Name, __VA_ARGS__))

#define Mini__ForEach_(Macro, Name, ...) \
    __VA_OPT__(Mini__Eval_(Mini__ForEachImpl_(Macro, Name, __VA_ARGS__)))

#define Mini__DeclareSumType(Name, ...)                                       \
    typedef struct Name {                                                     \
        enum { Mini__ForEach_(Mini__MakeTagField_, Name, __VA_ARGS__) } tag_; \
        union {                                                               \
            Mini__Byte sum_type_dummy_;                                       \
            Mini__ForEach_(Mini__MakeVarField_, Name, __VA_ARGS__)            \
        };                                                                    \
    } Name;

#endif // Mini__MacrosH_

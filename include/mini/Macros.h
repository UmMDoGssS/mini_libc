/** @file
 * @brief Preprocessing helpers and tagged union declarations.
 */

#ifndef Mini__MacrosH_
#define Mini__MacrosH_

#define Mini__ConcatMacro_(A, B) A##B

/**
 * @brief Expands two arguments and pastes their adjoining tokens.
 * @param A Left argument.
 * @param B Right argument.
 * @return The pasted token for two single-token arguments. The paste must form a valid token.
 */
#define Mini__ConcatMacro(A, B)  Mini__ConcatMacro_(A, B)

#define Mini__StringifyMacro_(X) #X

/**
 * @brief Expands an argument and converts the resulting tokens to a string literal.
 * @param X Argument to expand and stringify.
 */
#define Mini__StringifyMacro(X)  Mini__StringifyMacro_(X)

/**
 * @brief Substitutes the variadic arguments as a token sequence.
 *
 * Place the parentheses of a tuple directly after the macro name to expose the tuple contents.
 * For example, `Mini__UnwrapMacro(a, b)` expands to `a, b`.
 */
#define Mini__UnwrapMacro(...) __VA_ARGS__

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

/**
 * @brief Declares a typedef and struct for a tagged union.
 * @param Name Identifier used for both the struct tag and the typedef.
 *
 * Pass one or more `(Type, Tag, Var)` triples after @p Name. Each triple defines an enumerator
 * `Name__Tag_` and a union member `Var_` of the specified type. Set `tag_` to the matching
 * enumerator when storing a payload and inspect it before reading the union. Include
 * `<mini/Types.h>` before expanding this macro so the generated struct can use Mini__Byte.
 *
 * @code{.c}
 * #include <mini/Types.h>
 * Mini__DeclareSumType(Value, (Mini__I32, Integer, integer), (Mini__F32, Real, real))
 * Value value = { .tag_ = Value__Integer_, .integer_ = 42 };
 * @endcode
 */
#define Mini__DeclareSumType(Name, ...)                                       \
    typedef struct Name {                                                     \
        enum { Mini__ForEach_(Mini__MakeTagField_, Name, __VA_ARGS__) } tag_; \
        union {                                                               \
            Mini__Byte sum_type_dummy_;                                       \
            Mini__ForEach_(Mini__MakeVarField_, Name, __VA_ARGS__)            \
        };                                                                    \
    } Name;

#endif // Mini__MacrosH_

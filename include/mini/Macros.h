#ifndef Mini__MacrosH_
#define Mini__MacrosH_

#define Mini__ConcatMacro_(A, B) A##B
#define Mini__ConcatMacro(A, B) Mini__Concat_(A, B)

#define Mini__StringifyMacro_(X) #X
#define Mini__StringifyMacro(X) Mini__Stringify_(X)

#define Mini__UnwrapMacro(...) __VA_ARGS__

#endif // Mini__MacrosH_

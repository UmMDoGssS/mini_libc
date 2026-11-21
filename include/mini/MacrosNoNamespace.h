#ifndef Mini__MacrosNoNamespaceH_
#define Mini__MacrosNoNamespaceH_

#define ConcatMacro(A, B) Mini__Concat_(A, B)
#define StringifyMacro(X) Mini__Stringify_(X)
#define UnwrapMacro(...) __VA_ARGS__

#endif // Mini__MacrosNoNamespaceH_

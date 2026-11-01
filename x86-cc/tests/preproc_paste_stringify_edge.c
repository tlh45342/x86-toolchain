#define CAT_RAW(a,b) a ## b
#define CAT(a,b) CAT_RAW(a,b)
#define STR_RAW(x) #x
#define STR(x) STR_RAW(x)
#define A hello
#define EMPTY()
#define SELF SELF
CAT(foo,1)
CAT(12,34)
CAT(+, +)
CAT(foo,)
STR(A)
STR()
EMPTY()
SELF

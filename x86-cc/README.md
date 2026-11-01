# x86-cc 0.0.29

`x86-cc` is the incremental C compiler for the x86 project.

The long-term target is a useful C11-oriented compiler/toolchain capable of
producing native x86-64 Linux ELF programs.  Development is intentionally
incremental: each language feature is introduced with focused regression tests
and previously working tests remain part of the suite.

## Phase 0 - compiler seed

Version 0.0.1 established the first compiler/toolchain shape:

- 16-bit 8086 flat-binary output.
- `org 0x1000` standalone test programs.
- `AX` as the integer return-value register.
- `x86-as` as the assembler backend.
- `-S` assembly output.
- constant `return` expressions with a small `+` / `-` shortcut.

The original Phase 0 tests remain in the suite:

- `return42.c`
- `add_constants.c`

## Phase 1A - additive expression parser

Version 0.0.2 replaces the original one-off expression shortcut with the first
recursive-descent expression parser.

Current grammar:

    expression  := additive
    additive    := unary { ('+' | '-') unary }
    unary       := ('+' | '-') unary | primary
    primary     := INTEGER | '(' expression ')'

This provides:

- integer literals
- additive `+` and `-`
- left-associative additive chains
- parenthesized expressions
- nested parentheses
- unary `+` and unary `-`

Expressions are still constant-folded at compile time.  Locals, comparisons,
control flow, functions, pointers, ELF64 C output and preprocessing are later
phases.

## Phase 1B - multiplicative expressions and precedence

Version 0.0.3 adds the multiplicative precedence level.

Current grammar:

    expression     := additive
    additive       := multiplicative { ('+' | '-') multiplicative }
    multiplicative := unary { ('*' | '/' | '%') unary }
    unary          := ('+' | '-') unary | primary
    primary        := INTEGER | '(' expression ')'

This adds:

- multiplication `*`
- division `/`
- remainder `%`
- left-associative multiplicative chains
- multiplicative precedence over additive expressions
- parentheses that override normal precedence
- mixed and nested arithmetic expressions

The test suite includes deliberately different results for `2 + 3 * 4` (14)
and `(2 + 3) * 4` (20), so precedence is tested independently of the common
42-result examples.

## Usage

    x86-cc hello.c -o hello.bin
    x86-cc -S hello.c -o hello.asm
    x86-cc --version

## Current test philosophy

Tests are deliberately small and capability-named.  Each test should prove one
new language rule or prove that an existing rule works in a more demanding
context.  As the compiler grows, old tests stay active as regressions.

See `ROADMAP.md` for the planned development ladder.


## Phase 1C - Scalar Locals and Assignment

Version 0.0.4 adds stack-backed local `int` variables, identifier lookup,
initialization, assignment, multiple locals, and additive expressions that
load local values. Locals occupy 16-bit stack slots addressed from BP.
Phase 0 through 1B constant-only programs retain their established output.

Phase 1C deliberately does not yet generate runtime `*`, `/`, or `%` when a
local participates in the expression; those operators remain supported by the
constant-expression path from Phase 1B. This keeps the local-storage milestone
separate from additional x86 runtime arithmetic code generation.

## Phase 1D - Runtime Multiplicative Integration and Diagnostics

Version 0.0.5 connects the Phase 1B multiplicative grammar to the Phase 1C
stack-backed local-expression code generator. Runtime expressions involving
locals can now use `*`, `/`, and `%`, while preserving normal multiplicative
precedence and parenthesized overrides.

The runtime 16-bit code path uses the 8086 `MUL` and `DIV` instructions.
Phase 1D division and remainder tests intentionally use non-negative operands;
full signed `int` division semantics are deferred to the scalar-type work where
signedness is modeled explicitly.

Phase 1D also establishes negative compiler tests for undeclared identifiers,
duplicate local declarations, malformed expressions, missing parentheses, and
missing semicolons. These are compile-failure tests: success means x86-cc
correctly rejects the source.

With 0.0.5, the Phase 1 family has an integrated arithmetic/local-variable
foundation suitable for beginning Phase 2 comparisons and control flow.

## Phase 2A - Equality and Relational Expressions

Version 0.0.6 begins Phase 2 by adding equality and relational expressions.
The expression precedence ladder is now:

    expression     := equality
    equality       := relational { ('==' | '!=') relational }
    relational     := additive { ('<' | '<=' | '>' | '>=') additive }
    additive       := multiplicative { ('+' | '-') multiplicative }
    multiplicative := unary { ('*' | '/' | '%') unary }
    unary          := ('+' | '-') unary | primary
    primary        := INTEGER | IDENTIFIER | '(' expression ')'

Comparison expressions produce canonical C truth values: exactly `0` or `1`.
Constant-only comparisons are folded at compile time. Stack-backed comparisons
use `CMP` plus signed conditional branches, so values such as `-1 < 1` are
already tested on the runtime local-variable path.

Phase 2A intentionally stops before statements consume those truth values.
`if`/`else` and block control flow are the next boundary.

## Phase 2B - Compound Statements and if/else

Version 0.0.7 introduces the compiler's first statement-level control flow.
It adds `if`, optional `else`, compound statements (`{ ... }`), nested
conditionals, and the normal C dangling-`else` rule (an `else` binds to the
nearest unmatched `if`).

Conditions consume any expression using C zero/nonzero truth semantics; a
comparison is not required. Returns inside conditional branches jump to one
shared function epilogue so stack restoration remains correct.

Phase 2B deliberately does not add loops or lexical block scope. Local `int`
variables still use the existing function-local stack model. Those are kept as
separate milestones so the first control-flow step remains auditable.

## Phase 2D - for loops

Version 0.0.9 adds `for` statement control flow on top of the Phase 2C loop machinery.

Supported shape:

    for (initializer; condition; increment) statement

The initializer may be an assignment (or empty), the condition is tested using C zero/nonzero truth semantics, and the increment is an assignment expression emitted at the loop continue point. `break` exits the nearest loop and `continue` correctly targets the increment clause for `for`, while continuing to target the condition for `while`. Nested `for` loops and mixed `for`/`while` loops are covered by regression tests.

Phase 2D deliberately does not add `++`/`--`, comma expressions, or full lexical block scope. Those are separate language steps.

## Phase 2E - Logical expressions and short-circuit evaluation

Version 0.0.10 adds C logical negation `!`, logical AND `&&`, and logical OR
`||`. Logical operators produce canonical `0` or `1` results and follow the
normal precedence order: unary `!` binds tightly, equality/relational
expressions bind above `&&`, and `&&` binds above `||`.

`&&` and `||` use true short-circuit control flow. The right operand of `&&`
is skipped when the left operand is zero; the right operand of `||` is skipped
when the left operand is nonzero. Regression tests deliberately put a divide
by zero on the skipped side to prove the VM never executes that code.

Phase 2E keeps logical expressions separate from later lexical block scope and
function work. The existing `if`, `while`, and `for` statements consume the new
logical expressions without special cases.

## Phase 2F - Lexical block scope and shadowing

Version 0.0.11 makes compound statements establish real lexical scopes for
local `int` names.  An inner block may shadow an outer local, lookup chooses
the nearest active declaration, and the inner name disappears when the block
ends.  Redeclaration in the same scope remains an error.

`for` initializer declarations now receive their C-style loop scope: a name
declared by `for (int i = ...; ...; ...)` is visible in the condition,
increment, and loop body, but not after the `for` statement.  Such a loop-local
may shadow an outer local without changing the outer object.

The current implementation keeps frame allocation deliberately simple: each
source declaration reserves one 16-bit stack slot for the function, while the
symbol table controls which declarations are visible at each source location.
This separates lexical name lifetime from later stack-slot reuse/optimization.

Phase 2F completes the planned Phase 2 comparison/control-flow/scope climb.
Functions and calls can now be introduced on top of a symbol model that already
understands nested lexical visibility.


## Phase 3A - zero-argument functions and calls [0.0.12]

Phase 3 begins interprocedural code generation. Version 0.0.12 adds multiple `int name(void)` function definitions and direct zero-argument calls such as `answer()`. Each function owns a BP-based stack frame and a shared per-function return epilogue. Calls return scalar `int` values in AX. The generated standalone image enters through `_start`, calls `main`, and halts after `main` returns. Forward calls are supported because x86-as resolves labels in its normal two-pass assembly. Parameters, arguments, recursion guarantees, externs, and a platform ABI are deliberately deferred.

## Phase 3B - function parameters and arguments [0.0.13]

Version 0.0.13 adds named `int` parameters and direct-call argument lists.
Arguments are expressions and may themselves contain function calls.  The
current 16-bit compiler uses a deliberately small internal stack calling
convention: argument values are evaluated and pushed left-to-right, `CALL`
pushes the return address, the callee establishes its BP frame, and parameters
are addressed at positive BP offsets.  The caller removes argument words after
the call while preserving the returned value in AX.

Phase 3B regression tests cover two- and three-parameter functions, expression
arguments, local-variable arguments, parameters mixed with callee locals, and
nested calls such as `add(add(10,10), add(11,11))`.  Wrong argument counts and
duplicate parameter names are rejected.

This is still a project-internal 16-bit convention, not yet a promise of an
external ABI.  Recursion, prototypes/externs, and the eventual x86-64 SysV ABI
remain later milestones.


## Phase 3C - recursion and recursive frame composition [0.0.14]

Version 0.0.14 validates recursive calls on the Phase 3A/3B stack-frame and
argument model. A function may call itself directly, and functions may call
each other recursively. Each invocation receives its own BP-based frame,
parameters remain at positive BP offsets, locals remain at negative offsets,
and AX carries each result back through the recursive call chain.

Regression tests cover a recursive sum, recursion with a per-invocation local,
a deeper 21-level recursive call chain, and mutual recursion. This phase adds
no new surface syntax: it deliberately proves that the function machinery
already built is re-entrant before later function/linkage features are added.

The calling convention remains project-internal and 16-bit. Prototypes are
introduced in Phase 3D; externs, separate translation units, and the eventual
x86-64 SysV ABI remain later milestones.


## Phase 3D - function prototypes and signature validation [0.0.15]

Version 0.0.15 introduces function declarations/prototypes and a small
translation-unit function symbol pass.  The compiler accepts both named and
unnamed prototype parameters:

    int add(int a, int b);
    int other(int, int);

Compatible prototypes may be repeated, and a definition may appear before or
after its prototype.  Since the only supported scalar type is currently `int`,
function compatibility is an arity check.  Conflicting prototypes and duplicate
definitions are rejected.  Function definitions must name their parameters,
while prototypes may omit those names.

The current output remains one standalone 16-bit flat image.  Therefore a
function that is actually called must also be defined in the same translation
unit.  A prototype without a local definition is not yet an external-linkage
mechanism; that boundary belongs to later ELF object/linker work.

Regression tests combine prototypes with ordinary calls and recursion, and add
focused diagnostics for conflicting declarations, duplicate definitions,
unresolved calls, and unnamed parameters in a definition.

## Phase 4A - pointers, address-of, and dereference [0.0.16]

Phase 4 begins the compiler's object/address model. Version 0.0.16 adds local
`int *` objects, unary address-of for local objects (`&x`), dereference of a
named pointer (`*p`), pointer reassignment, and indirect assignment (`*p = e`).
Pointers are 16-bit addresses in the current real-mode model and local object
addresses are formed relative to BP.

This phase is deliberately narrow. It does not yet add pointer parameters,
pointer arithmetic, arrays, `char *`, multiple indirection, or general typed
pointer-valued expressions. Those build on the value-versus-address distinction
established and VM-tested here.

## Phase 4B - explicit lvalues and rvalues [0.0.17]

Version 0.0.17 makes the location/value split explicit inside expression code
generation.  An assignable expression can now be compiled as an lvalue
(address/location) when an address or store target is required, while ordinary
expression use still produces the rvalue stored at that location.

This phase deliberately stays within the existing `int` / `int *` type model.
It composes address-of and dereference (`*(&x)`, `&*p`), uses the same lvalue
path for indirect stores, and tracks whether a generated expression is an
integer value or an `int *` value.  Pointer/scalar initializer and assignment
mismatches are rejected.  Direct named-local stores remain BP-relative as a
code-size optimization; semantically they are still lvalue stores.

New Phase 4B tests cover dereference-of-address, address-of-dereference,
composed indirect stores, and copying through two pointer lvalues.  Diagnostics
also reject taking the address of an rvalue and initializing an `int *` from a
plain integer object.

Deferred from 4B: pointer parameters, pointer arithmetic, arrays, `char *`,
pointer-to-pointer types, structures, and the 64-bit object model.


## Phase 4C - pointer parameters across function boundaries [0.0.18]

Version 0.0.18 carries the Phase 4 pointer model through the Phase 3 function
call machinery. Function declarations and definitions may now use `int *`
parameters, and pointer arguments are type-checked against the function
signature before a call is emitted.

Examples now supported include:

    int read_value(int *p) { return *p; }

    int set42(int *p) {
        *p = 42;
        return 0;
    }

Pointer parameters are ordinary callee objects backed by the existing positive
BP parameter offsets. Loading a pointer parameter yields its address value;
dereferencing it uses the existing Phase 4B lvalue/rvalue machinery. Multiple
pointer parameters and recursive calls carrying pointer values are covered by
regression tests.

Function prototypes may use named or unnamed pointer parameters, such as
`int fetch(int *p);` or `int fetch(int *);`. Signature compatibility now checks
parameter pointer/scalar type as well as arity. Passing a scalar to an `int *`
parameter, passing a pointer to an `int` parameter, or defining a function with
a pointer/scalar signature that conflicts with its prototype is rejected.

Phase 4C deliberately does not add pointer arithmetic, arrays, `char *`,
multiple indirection, pointer return types, or a platform ABI. The next natural
step is array objects and indexing, built on the now-proven lvalue and pointer
call-boundary model.

## Phase 4D - arrays and indexed lvalues (0.0.19)

Phase 4D adds fixed-size local `int` arrays and `a[index]` as both an rvalue and
an lvalue. Array elements are contiguous 16-bit words, so runtime indices are
scaled by two before being added to the array base address. A bare local array
expression decays to `int *`, allowing the array to be passed to the pointer
parameters introduced in Phase 4C.

This checkpoint intentionally does not yet implement general pointer arithmetic,
pointer subscripting, array initializers, `char` arrays, strings, or `sizeof`.

## Phase 4E - scaled int pointer arithmetic (0.0.20)

Phase 4E exposes the pointer arithmetic that Phase 4D already used internally for
array indexing. `int *` plus or minus an integer advances by `sizeof(int)`, which
is two bytes in the current 16-bit target model. Integer-plus-pointer is also
accepted. This makes `*(a + i)` a first-class spelling of the same address
calculation underlying `a[i]`.

Supported in this phase:

- `pointer + integer`
- `pointer - integer`
- `integer + pointer`
- runtime integer offsets
- dereference of pointer-arithmetic expressions
- array decay feeding pointer arithmetic

Pointer-plus-pointer and scalar-minus-pointer are rejected. Pointer difference
(`p - q`) is deliberately deferred until the compiler has a suitable signed
integer/result model for it.


## Phase 4F - char objects, pointers, and byte arrays [0.0.22]

Phase 4F crosses the byte boundary. It adds local `char` objects, `char *`,
fixed-size local `char` arrays, byte loads/stores, char-pointer parameters, and
byte-scaled pointer arithmetic. `int * + 1` still advances two bytes; `char * + 1`
advances one byte. Array-to-pointer decay preserves the element type. String
literals remain deliberately deferred so this phase proves the byte object model
without also introducing compiler-managed static storage.


## Phase 4G - String literals and static data (0.0.22)

Phase 4G introduces compiler-owned NUL-terminated string literal storage. A string literal expression has type `char *` in the current deliberately small type model and evaluates to the address of a generated static-data label. Literals can initialize `char *` locals, cross `char *` function-call boundaries, participate in byte-scaled pointer arithmetic, and be walked until the terminating NUL. Multiple literals receive distinct compiler-generated labels.

This phase deliberately does not add globals, writable string-array initialization, libc, `printf`, or the preprocessor. Those remain later boundaries.
### Phase 4G correction — long literal emission

String-pool data is emitted in `db` groups of at most 16 bytes so long literals are preserved by the current x86-as flat-binary directive path. The runtime `string_strlen` fence post intentionally spans more than 16 bytes.



## Phase 4H - generalized pointer subscripting (0.0.23)

Phase 4H closes the remaining indexing gap between arrays and pointers. Indexed
lvalues/rvalues now accept both local array objects and typed pointer values, so
`p[i]` uses the same address model as `*(p + i)`. `int *` indices scale by two
bytes and `char *` indices scale by one byte. Pointer parameters can be indexed
directly, and indexed pointer expressions can be assignment targets.

This phase deliberately does not add pointer-to-pointer types, arrays of pointers,
or `argc`/`argv`; those remain the next pointer-depth boundary.


## Phase 4I - pointer depth and double pointers

x86-cc 0.0.24 extends the compact type model from a boolean pointer flag to pointer depth 0..2. This enables `int **` and `char **`, address-of pointer objects, double dereference, double-pointer parameters, and pointer-valued subscripting such as `pp[0]`. Pointer arithmetic continues to scale by the size of the pointee: a depth-two pointer advances by the 16-bit pointer size (2 bytes), while `char *` still advances by one byte. Triple pointers remain intentionally deferred.


## Phase 4J - arrays of pointers (0.0.25)

Phase 4J completes the Phase 4 pointer/array composition by allowing local arrays whose elements are pointers.

- `int *items[N]` and `char *words[N]`.
- Pointer elements occupy one 16-bit pointer slot each.
- `items[i]` and `words[i]` are typed pointer lvalues and may be read or assigned.
- Bare pointer arrays decay one level: `int *[N] -> int **` and `char *[N] -> char **`.
- Decayed pointer arrays may cross function boundaries through existing double-pointer parameters.
- Runtime indexing uses the 16-bit pointer size (2 bytes).
- Base-type mismatches remain diagnosed; arrays of `T **` are deferred because decay would require `T ***`.

This closes Phase 4's object/pointer/array/string climb. The next major chapter can introduce aggregate types (`struct`, `.`, and later `->`) without leaving an unfinished single/double-pointer array model behind.


## Phase 5 overview - aggregate types

Phase 5 deliberately changes subjects after the completed Phase 4 pointer,
array, and string climb.  The chapter builds aggregates in the same incremental
style, reusing the lvalue/address machinery instead of treating structures as a
special code-generation island.

Planned checkpoints:

- **5A - named struct definitions, local struct objects, and `.` member access.**
  Start with `int` members so layout and member lvalues are independently proven.
- **5B - struct pointers and `->`.**  Compose member offsets with the existing
  pointer/dereference model.
- **5C - typed members.**  Add `char`, `T *`, and other already-supported scalar
  member types while preserving member type through loads, stores, and address-of.
- **5D - arrays of structs and indexed aggregate lvalues.**  Make `a[i].member`
  another composition of indexing plus member selection.
- **5E - struct pointers across function boundaries.**  Extend function-signature
  metadata so named struct pointer types can be checked at calls and prototypes.
- **5F - aggregate copy/assignment.**  Introduce whole-object `a = b` only after
  layout, addressability, and typed member access are already stable.

Passing/returning whole structs by value, nested structs, unions, bit-fields,
packing controls, and the eventual x86-64 ABI are intentionally outside the
initial Phase 5 climb unless a later checkpoint makes one of them the cleanest
next dependency.

## Phase 5A - struct objects and dot-member access (0.0.26)

Phase 5A introduces the first aggregate object model:

```c
struct Pair {
    int a;
    int b;
};

int main(void) {
    struct Pair p;
    p.a = 10;
    p.b = 32;
    return p.a + p.b;
}
```

The compiler records named structure layouts, allocates local structure storage
as contiguous 16-bit words, and turns `p.member` into the address of `p` plus a
compile-time member offset.  That address then flows through the existing lvalue
load/store machinery established in Phase 4.

The 5A contract is intentionally narrow: structure members are `int`, structure
objects are local, and whole-structure assignment is rejected.  Structure
pointers and `->` are the next checkpoint rather than being folded into this one.


## Phase 5B - struct pointers and arrow-member access (0.0.27)

Phase 5B composes the Phase 5A aggregate layout model with the existing pointer
and lvalue machinery. Local pointers to named structures are now supported:

```c
struct Pair { int a; int b; };

int main(void) {
    struct Pair p;
    struct Pair *q = &p;
    q->a = 10;
    q->b = 32;
    return q->a + q->b;
}
```

The compiler preserves the named structure identity on structure-pointer values
so `struct A *` is not interchangeable with `struct B *`. `q->member` loads the
structure base address from `q`, adds the compile-time member offset, and then
reuses the existing lvalue load/store path. Structure-pointer locals may be
initialized, copied, and retargeted with compatible addresses.

This checkpoint intentionally keeps structure-pointer parameters/prototypes for
Phase 5E. Double pointers to structures, pointer arithmetic on structure
pointers, whole-structure dereference as an rvalue, and whole-object copy remain
deferred.


## Phase 5C - typed struct members (0.0.28)

Phase 5C makes a structure member more than a name and an ordinal. Each member
now carries a base type, pointer depth, byte offset, and storage width.

Current member forms are deliberately narrow:

```c
struct Item {
    char tag;
    int value;
    int *number;
    char *text;
};
```

Layout is deterministic and packed for this compiler stage: scalar `char`
occupies one byte; `int` and pointers occupy two bytes. Member access through
both `.` and `->` preserves the member type, so byte members use byte
loads/stores and pointer members remain typed pointer expressions.

Examples now supported include `x.tag`, `x.number = &n`, `*x.number`,
`x.text = "text"`, `*x.text`, and their `p->member` equivalents.

Still deferred: nested struct members, arrays as struct members, pointer depth
greater than one inside a struct, whole-struct copy, arrays of structs, and
struct pointers in function signatures.

## Blackjack target (0.0.29)

Version 0.0.29 adds the first operating-system target to the 16-bit compiler:

    x86-cc --blackjack program.c -o program.bin

The target emits org 0, enters through _start, calls main, and exits through
Blackjack INT 60h. The initial target runtime provides bj_write, bj_mem_kb,
and bj_shutdown for the first C userspace utilities. Standalone compiler output
remains unchanged when --blackjack is not selected.

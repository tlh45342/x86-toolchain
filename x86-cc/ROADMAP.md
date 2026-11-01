# x86-cc development roadmap

This roadmap records the intended development order.  It is a guide, not a
claim of current C11 conformance.

## Phase 0 - seed [DONE]

- compiler driver
- `-S`
- x86-as backend
- flat 16-bit test binary
- `return INTEGER`
- first additive constant expression

## Phase 1 - expressions and scalar locals

### Phase 1A - additive expressions [0.0.2]

- primary integer expressions
- parentheses and nesting
- unary `+` / `-`
- additive `+` / `-`
- chaining and left associativity

### Phase 1B - multiplicative expressions and precedence [0.0.3]

- `*`
- `/`
- `%`
- multiplicative before additive
- parentheses override precedence
- mixed/chained expression tests

### Phase 1C - scalar locals and assignment [0.0.4]

- local `int` declarations
- initialization
- assignment
- multiple locals
- identifier lookup
- initial lvalue/value distinction

### Phase 1D - runtime multiplicative integration and diagnostics [0.0.5]

- runtime `*`, `/`, `%` over local values
- multiplicative precedence with runtime operands
- expressions in initializers
- expressions on assignment RHS
- malformed expression diagnostics
- undeclared identifiers
- missing delimiters

## Phase 2 - comparisons and control flow

### Phase 2A - equality and relational expressions [0.0.6]

- `==` and `!=`
- `<`, `<=`, `>`, `>=`
- comparison precedence below arithmetic
- canonical boolean results `0` / `1`
- constant-folded and runtime-local comparison paths
- signed runtime relational branches

### Phase 2B - conditional and compound statements [0.0.7]

- `if`
- `else`
- compound statements `{ ... }`
- zero/nonzero condition consumption
- nested conditional flow
- dangling-`else` binds to nearest unmatched `if`
- shared return epilogue

### Phase 2C - while loops [0.0.8]

- `while`
- `break` / `continue`
- nearest-loop binding
- nested loops

### Phase 2D - for loops [0.0.9]

- `for (init; condition; increment)`
- `break` / `continue`
- `continue` targets the increment clause
- nested and mixed loop forms

### Phase 2E - logical expressions [0.0.10]

- unary logical `!`
- logical `&&`
- logical `||`
- canonical boolean `0` / `1`
- `&&` precedence above `||`
- true short-circuit evaluation
- integration with `if`, `while`, and `for`

### Phase 2F - lexical block scope [0.0.11]

- compound blocks establish lexical scopes
- nearest active declaration wins lookup
- inner locals may shadow outer locals
- same-scope duplicate declarations remain errors
- names disappear when their block ends
- `for (int i = ...; ...; ...)` initializer scope
- for-init locals may shadow outer locals

**Phase 2 complete.**

Later phases add richer functions/SysV AMD64 ABI, scalar types, pointers,
arrays, strings, `sizeof`, casts, typedefs, structures, enums, object/linkage
semantics, preprocessing and `#include`, target headers, runtime/libc, variadic
functions, and increasingly complete C11 coverage.

Preprocessing is tracked separately from language grammar, but it is considered
a fundamental usability goal for the x86 C environment rather than an optional
late add-on.


## Current checkpoint

- Phase 0: complete - compiler seed
- Phase 1A: complete - additive expressions
- Phase 1B: complete - multiplicative constant expressions and precedence
- Phase 1C: complete in 0.0.4 - scalar locals, initialization, assignment,
  identifier lookup, stack-backed storage, and additive local expressions
- Phase 1D: complete in 0.0.5 - runtime multiplicative expressions, precedence
  integration, and focused compile-failure diagnostics
- Phase 1: complete for the current 16-bit arithmetic/local-variable contract
- Phase 2A: complete in 0.0.6 - equality and relational expressions, arithmetic/comparison precedence, canonical boolean results, and runtime local comparisons
- Phase 2B: complete in 0.0.7 - `if` / `else`, compound statements, nested conditionals, and zero/nonzero condition consumption
- Phase 2C: complete in 0.0.8 - `while`, `break`, `continue`, and nested-loop control
- Phase 2D: complete in 0.0.9 - `for` loops and mixed/nested loop control
- Phase 2E: complete in 0.0.10 - `!`, `&&`, `||`, precedence, canonical boolean values, and short-circuit evaluation
- Phase 2F: complete in 0.0.11 - lexical block scope, shadowing, and for-initializer scope
- Phase 2: complete - comparisons, conditionals, loops, logical short-circuiting, and lexical scope
- Phase 3A: complete in 0.0.12 - zero-argument functions and direct calls
- Phase 3B: complete in 0.0.13 - integer parameters and arguments
- Phase 3C: complete in 0.0.14 - recursion and recursive frame composition
- Phase 3D: complete in 0.0.15 - function prototypes and signature validation
- Phase 3: complete for the current internal 16-bit function model
- Phase 4A: complete in 0.0.16 - local pointers, address-of, dereference, and indirect store
- Phase 4B: complete in 0.0.17 - explicit lvalue/rvalue address generation and pointer/scalar tracking
- Current checkpoint: Phase 4C - pointer parameters across function boundaries


## Phase 3A - zero-argument functions and calls [0.0.12]

Phase 3 begins interprocedural code generation. Version 0.0.12 adds multiple `int name(void)` function definitions and direct zero-argument calls such as `answer()`. Each function owns a BP-based stack frame and a shared per-function return epilogue. Calls return scalar `int` values in AX. The generated standalone image enters through `_start`, calls `main`, and halts after `main` returns. Forward calls are supported because x86-as resolves labels in its normal two-pass assembly. Parameters, arguments, recursion guarantees, externs, and a platform ABI are deliberately deferred.


## Phase 3B - function parameters and arguments [0.0.13]

- named `int` parameters
- argument expressions
- two- and three-argument calls
- parameters visible as callee objects
- parameters mixed with local variables
- nested calls as arguments
- caller stack cleanup with AX return preservation
- wrong-arity diagnostics
- duplicate-parameter diagnostics

The calling convention remains deliberately internal to the 16-bit compiler
while the language/call model is being developed.  A platform ABI comes later.


## Phase 3C - recursion and recursive frame composition [0.0.14]

- direct recursion
- recursive calls with parameters
- per-invocation locals across recursion
- deeper recursive call chains
- mutual recursion
- no new C surface syntax; this is a stack-frame/call-model validation phase

Phase 3C deliberately proves re-entrant function frames before prototypes,
extern linkage, separate translation units, or a platform ABI are introduced.


## Phase 3D - function prototypes and signature validation [0.0.15]

- function declarations/prototypes before or after definitions
- named or unnamed `int` parameters in prototypes
- repeated compatible prototypes
- prototype/definition arity consistency
- duplicate-definition diagnostics
- missing parameter-name diagnostics on definitions
- unresolved-call diagnostics for the current standalone flat-image model
- prototypes compose with recursion and the existing call-frame machinery

Phase 3D adds a small translation-unit function-symbol pass.  All currently
supported parameter and return types are `int`, so signature compatibility is
currently an arity check.  A prototype may omit parameter names because those
names are not objects in a function body; a definition must name its parameters.

The compiler still emits one standalone 16-bit flat image, so a function that is
actually called must have a definition in the same translation unit.  External
resolution is deliberately deferred until ELF objects and the linker are part of
the compiler path.

**Phase 3 complete for the current internal 16-bit function model.**

## Phase 4A - pointers, address-of, and dereference [0.0.16]

Phase 4 starts the object/address climb. The first checkpoint adds local `int *`
objects, `&local`, `*pointer`, pointer retargeting, and `*pointer = expression`.
The goal is to prove the compiler can distinguish an object's stored value from
its address before arrays, strings, pointer parameters, and structures depend
on that distinction.

Deferred from 4A: pointer parameters, pointer arithmetic, arrays, `char *`,
multiple indirection, and general pointer-expression typing.

## Phase 4B - explicit lvalues and rvalues [0.0.17]

Introduce an explicit location-versus-value model before adding more pointer
syntax.  Named objects and dereferenced pointer expressions can be treated as
lvalues (addresses/store targets); normal expression use produces rvalues.
Address-of and dereference now compose, so expressions such as `*(&x)` and
`&*p` are meaningful within the current `int` / `int *` model.

This phase also begins lightweight expression-type tracking so pointer/scalar
mismatches are diagnosed instead of silently generating word operations.
Direct BP-relative local stores are retained as a compact implementation of a
known lvalue, avoiding needless growth of existing 8086 loop bodies.

## Phase 4C - pointer parameters across function boundaries [0.0.18]

- `int *` parameters in function definitions
- named or unnamed `int *` parameters in prototypes
- pointer arguments crossing caller/callee boundaries
- pointer parameters participate in dereference and indirect store
- multiple pointer parameters
- pointer values survive recursive calls
- signature compatibility includes pointer/scalar parameter type
- call-site diagnostics for pointer/scalar argument mismatch

The existing internal 16-bit calling convention is unchanged. Pointer values are
still 16-bit addresses in this model and occupy the same one-word argument slots
as scalar `int` values; the function signature determines how the callee and
compiler interpret each slot.

Next natural checkpoint: array objects and indexing, then pointer arithmetic.


## Phase 4D - local int arrays and indexing [0.0.19]

- fixed-size local `int a[N]` objects
- contiguous word storage in the function frame
- constant and runtime `a[index]` reads
- indexed lvalues: `a[index] = expression`
- index scaling by `sizeof(int)` (2 bytes in the current 16-bit model)
- bare array expressions decay to `int *` for function arguments
- arrays compose with loops and the Phase 4C pointer-parameter model
- diagnostics for zero-sized arrays, scalar subscripting, and whole-array assignment

Phase 4D deliberately keeps indexing attached to actual local array objects. General
`int *` arithmetic and pointer subscripting are the next natural step; `char`, strings,
multidimensional arrays, initializers, and `sizeof` remain later checkpoints.

## Phase 4E - scaled int pointer arithmetic [0.0.20]

Expose the address arithmetic already implicit in Phase 4D indexing. For the
current `int`/`int *` model, pointer movement is scaled by two bytes.

Acceptance fence posts:

- `p + 1` advances one `int`, not one byte.
- `p - 1` retreats one `int`.
- `1 + p` is equivalent to `p + 1`.
- `*(a + i)` composes pointer arithmetic with the Phase 4B lvalue/rvalue model.
- runtime integer offsets work.
- pointer + pointer and scalar - pointer are diagnosed.

Pointer subtraction, `char *`, byte scaling, strings, and multidimensional
arrays remain later phases.


## Phase 4F - char objects, pointers, and byte arrays [0.0.21]

Phase 4F crosses the byte boundary. It adds local `char` objects, `char *`,
fixed-size local `char` arrays, byte loads/stores, char-pointer parameters, and
byte-scaled pointer arithmetic. `int * + 1` still advances two bytes; `char * + 1`
advances one byte. Array-to-pointer decay preserves the element type. String
literals remain deliberately deferred so this phase proves the byte object model
without also introducing compiler-managed static storage.


### Phase 4G - string literals and compiler-owned static data - COMPLETE IN 0.0.22

- Parse double-quoted string literals in expressions.
- Emit NUL-terminated bytes in a compiler-owned static-data pool.
- Literal expressions produce `char *` values.
- Reuse existing char-pointer calls, byte dereference, and pointer walking.
- Validate multiple literals and reject passing a string literal to `int *`.

Next natural checkpoint: decide the narrow boundary for character/string conveniences versus the next object-model feature; do not fold libc or preprocessing into Phase 4G.
**Phase 4G correction:** emit string bytes in assembler-safe 16-byte `db` chunks; the 42-byte strlen test guards this boundary.



## Phase 4H - generalized pointer subscripting [0.0.24]

- `int *p`: read and write `p[i]` with two-byte element scaling.
- `char *p`: read and write `p[i]` with one-byte element scaling.
- pointer parameters support direct indexed access.
- runtime scalar indices are accepted.
- `p[i]` and `*(p + i)` are validated as equivalent address operations.
- pointer-valued indices are diagnosed.

Next natural checkpoint: pointer-to-pointer types, especially `char **`, before
arrays of pointers and the eventual `argc`/`argv` program-entry model.


### Phase 4I - pointer depth and double pointers (0.0.24)

- [x] Represent pointer depth through two levels.
- [x] `int **` and `char **` locals.
- [x] Address-of pointer objects (`&p`).
- [x] Double dereference (`**pp`) for reads and stores.
- [x] Double-pointer parameters and argument validation.
- [x] Pointer-valued subscripting (`pp[i]`) with pointer-size scaling.
- [ ] Triple pointers.
- [ ] Arrays of pointers.
- [ ] `main(int argc, char **argv)` startup/ABI integration.

Natural next checkpoint: arrays of pointers and argv-shaped data, then command-line entry semantics.


### Phase 4J - arrays of pointers (0.0.25)

- [x] Local `int *a[N]` arrays.
- [x] Local `char *a[N]` arrays.
- [x] Typed pointer-element indexed reads and stores.
- [x] Pointer-array decay (`T *[N]` -> `T **`).
- [x] Double-pointer function calls using decayed pointer arrays.
- [x] Runtime pointer-array indexing with two-byte pointer scaling.
- [x] Reject base-type mismatches and arrays requiring pointer depth three.

Phase 4 is complete at this boundary. Natural next chapter: aggregate types, beginning with `struct` objects and member access.


## Phase 5 - aggregate types

The aggregate chapter begins only after Phase 4 has closed the pointer/array
model.  The intended dependency order is:

### Phase 5A - named structs, local objects, and `.` [0.0.26]

- [x] Parse named top-level `struct Name { int ...; };` definitions.
- [x] Record deterministic declaration-order member layout.
- [x] Allocate local `struct Name object;` storage in the stack frame.
- [x] Read `object.member` as an rvalue.
- [x] Write `object.member` as an lvalue.
- [x] Compose member access with ordinary scalar expressions and multi-function translation units.
- [x] Diagnose unknown struct types, unknown members, duplicate members, and whole-struct assignment.
- [ ] Struct pointers / `->`.
- [ ] Non-`int` member types.
- [ ] Arrays of structs.
- [ ] Whole-object copy.

### Phase 5B - struct pointers and `->` [0.0.27]

- [x] Local `struct Name *` pointer objects.
- [x] Address-of local structure objects.
- [x] `p->member` reads and writes through compile-time member offsets.
- [x] Compatible structure-pointer initialization, copy, and retargeting.
- [x] Preserve named structure identity for local pointer type checks.
- [x] Diagnose `.` on a structure pointer, `->` on a structure object, incompatible named structure pointers, and `struct T **`.
- [ ] Structure-pointer parameters/prototypes (Phase 5E).
- [ ] Structure-pointer arithmetic.
- [ ] Whole-structure dereference as an rvalue.

Natural next checkpoint: typed structure members (`char`, scalar pointers, and their member lvalues) in Phase 5C.

### Phase 5C - typed members

Carry the already-proven scalar type model (`char`, pointer depth, base type)
into structure members, including address-of and typed member assignment.

### Phase 5D - arrays of structs

Make `a[i].member` and related indexed aggregate lvalues a direct composition of
the Phase 4 indexing model and the Phase 5 member-offset model.

### Phase 5E - struct pointers across function boundaries

Teach function signatures to retain the named structure identity of pointer
parameters so `struct A *` and `struct B *` are not interchangeable.

### Phase 5F - aggregate assignment/copy

Add `a = b` for compatible structure objects once object size/layout and
addressability are stable.  This is the first deliberate whole-object move.

Whole structs passed or returned by value, unions, bit-fields, nested aggregate
layout, packing controls, and platform ABI details remain later work.


### Phase 5C - typed struct members [0.0.28]

- [x] `char` members
- [x] `int *` members
- [x] `char *` members
- [x] byte-aware deterministic member offsets
- [x] byte load/store for scalar `char` members
- [x] preserve pointer/base type through `.`
- [x] preserve pointer/base type through `->`
- [x] reject incompatible pointer-member assignments
- [x] keep nested members, member arrays, and member `T **` outside this phase

Next planned checkpoint: Phase 5D, arrays of structs and `a[i].member`.

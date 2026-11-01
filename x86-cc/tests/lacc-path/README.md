# LACC-inspired x86-cc test path

Source reference: O:\src\lacc-master\test\c89
Compiler: O:\x86\toolchain\x86-cc\x86-cc.exe
Test sources: tests\lacc-path
Build outputs: tests\build\lacc-path

## Ground rules
- Tests here are independently authored, not copied verbatim from LACC.
- Compile success is not execution success. A runtime PASS requires x86-run HLT with AX=002A.
- Preserve failures as regressions. Fix a shared code-generation/type rule, not the test.
- Keep compiler source and test artifacts separate.

## First-pass compile inventory (2026-10-15)
| Test | LACC inspiration | Result | Next action |
|---|---|---|---|
| 00_smoke.c | baseline | COMPILE PASS | add emulator smoke |
| 01_compound_16.c | compound-assignment-basic.c | COMPILE FAIL | isolate &= and \\|= from other operations |
| 02_shift_16.c | shift-assign.c | COMPILE FAIL | inspect <<= and >>= parsing |
| 03_reverse_index.c | array-reverse-index.c | COMPILE FAIL | inspect subscript expression grammar |
| 04_pointer_difference.c | pointer-diff.c | COMPILE FAIL | inspect pointer subtraction and scaling |
| 05_wide_shift_compound.c | shift-assign.c | COMPILE FAIL | address after 16-bit shift compound |

## Existing verified coverage
- 32-bit local arrays, pointer indexing, global arrays, computed-lvalue multiplication: x86-run AX=002A.
- 32-bit array +=, -=, ^= and global scalar +=, -=, ^=, *=: x86-run AX=002A.
- wide32 compile suite 9/9; optimization execution suite 11 programs at O0/O1.

## Next paths
1. **Compound operators:** split &=, |=, <<=, >>= into isolated tests; verify scalar, indexed, dereferenced, and global lvalues.
2. **Pointer arithmetic:** element-size scaling, subtraction, one-past-the-end (without dereference), and address comparison.
3. **Expression correctness:** assignment values, nested assignment, side effects, and array decay.
4. **Integer semantics:** promotions, signed versus unsigned comparisons/division, and truncation.
5. **Language surface:** map C89 LACC cases into supported, partial, unsupported, or deliberately deferred; do not conflate C99/C11 with C89.

Do not enable Blackjack login merely because compile-only tests pass.

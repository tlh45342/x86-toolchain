# Blackjack 32-bit arithmetic regression suite

This suite is **original Blackjack project work**. The test cases, expected
results, names, and harness are authored specifically for the x86-cc 8086
compiler and Blackjack's 16-bit ABI. Do not copy third-party test source into
this suite.

Run `make test-wide32` from `O:/x86/toolchain/x86-cc`.

## Concepts to verify

1. **Literal parsing:** decimal and hexadecimal constants above 65535,
   including `U`, `L`, and `UL` suffixes; reject values outside supported types.
2. **Width and promotion:** `unsigned int` is 16 bits, `unsigned long` is
   32 bits; mixed operations preserve the 32-bit value.
3. **32-bit bitwise operations:** XOR, AND, OR, and complement affect both
   halves of the value.
4. **32-bit multiplication:** the low 32 bits of a product are preserved,
   including unsigned wraparound.
5. **Shifts:** shifts cross the 16-bit word boundary and distinguish logical
   from arithmetic right shifts.
6. **End-to-end hash:** byte mixing for Blackjack's educational bj1 verifier.

## Verification levels

The current `test_wide32.py` only tests whether compilation to assembly
succeeds. It does not prove execution semantics. A subsequent runtime suite
must execute each result and assert the complete 32-bit value; no test should
be reported as an arithmetic PASS based on compilation alone.

## Research context

LACC's C89 corpus at `O:/src/lacc-master/test/c89` helped identify relevant
language concepts: integer literal typing, unsigned promotions, shift counts,
and mixed-width expressions. It is a **reference for coverage ideas only**;
Blackjack's tests are independently authored and tailored to our target.

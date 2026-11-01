# x86-as 0.0.24

A deliberately small NASM-like assembler for the x86 VM project.

Primary legacy target: 8086/8088, 16-bit flat binaries. Version 0.0.24 preserves the deliberately small x86-64/ELF64 path and begins a systematic 8086 encoding-completion campaign. This is not intended to be a full NASM clone. It is intended to give the project a native assembler that grows with the ISA and can be cross-checked against NASM.

## CLI

```
x86-as -f bin input.asm -o output.bin
x86-as -m64 -f bin input.asm -o output.bin
x86-as -m64 -f elf64 input.asm -o output.o
x86-as --version
```

## Phase-1 syntax

Directives/preprocessor: `cpu 8086`, `bits 16`, `org`, labels, `equ`, `db`, `dw`, `times`, `%macro`/`%endmacro` with `%1` arguments. Expressions support numeric/character literals, symbols, `$`, `$$`, parentheses, `+ - * / %`, shifts, and bitwise `& ^ |`. `db` accepts both single- and double-quoted byte strings and mixed lists, for example `db "GUPPY BOOT1", 13, 10, 0` or `db 'EFI PART'`. Single-character literals such as `'0'` may also be used in instruction expressions (`mov al, '0'`).

Initial instructions include the forms currently useful to firmware/tests: MOV reg immediate, MOV segment/register, MOV register/memory 8/16-bit, INT, IRET, HLT, NOP, CLI/STI/CLD, ADD/SUB/XOR/OR register forms, immediate ADD/SUB, CMP accumulator/immediate, PUSH/POP, INC/DEC, CALL/RET, JMP near/short/far, JZ/JNZ short.

Conditional branches are deliberately strict 8086 rel8. If a target is out of range, x86-as errors instead of silently emitting a later `0F 8x` near-Jcc encoding.

## Tests

```
make test-x86
make test-nasm
make test-compare
```

`test-x86` checks native output against expected byte strings. `test-nasm` verifies that NASM accepts the same test corpus. `test-compare` assembles every case with both assemblers and requires byte-for-byte equality.

This gives us three useful failure classes: x86-as encoding bug, source not actually valid for NASM/8086, or deliberate encoding-policy difference that needs to be resolved.


## 0.0.20

Adds complete 8086 INC operand coverage used by current boot code:

- `inc r16` (`40+rw`)
- `inc r/m8` (`FE /0`) including `inc byte [mem]`
- `inc r/m16` (`FF /0`) including `inc word [mem]`

Memory operands require an explicit `byte` or `word` size when the width cannot be inferred.


## 0.0.21 — x86-64 Phase 1A seed

Begins the x86-64 path without changing the existing 8086 default.

- Adds CLI target mode `-m64`.
- Adds `bits 64` validation: 64-bit source requires `-m64`.
- Keeps `-f bin` as the only output format in this phase; ELF64 is intentionally deferred.
- Adds the first 64-bit encodings needed for a Linux syscall proof:
  - `mov r64, imm64` for RAX/RCX/RDX/RBX/RSP/RBP/RSI/RDI (`REX.W + B8+rd + imm64`)
  - `xor r64, r64` for the same base registers (`REX.W + 31 /r`)
  - `syscall` (`0F 05`)
- Adds regression test `028_m64_seed.asm` with exact expected bytes.

The existing 16-bit assembler remains the default and the complete 001-027 regression inventory must continue to pass. This phase intentionally does **not** add ELF output, relocations, extended registers R8-R15, or general 64-bit addressing yet.

## 0.0.22 — x86-64 Phase 1B ELF64 relocatable seed

Adds the first genuine ELF64 object-file output while preserving the existing flat-binary paths.

- Adds `-m64 -f elf64`.
- `-m64` remains the machine/instruction mode; `-f elf64` remains the output format.
- `-f elf64` without `-m64` is rejected in this phase.
- Adds minimal NASM-like `section .text` and `global` handling for ELF64 sources.
- Emits a real ELF64 little-endian `ET_REL` object for `EM_X86_64`.
- Emits `.text`, `.symtab`, `.strtab`, and `.shstrtab` section tables.
- Emits global symbols such as `_start` into `.symtab`.
- Adds regression test `029_elf64_seed.asm`, which parses the object directly and verifies the ELF magic, class, machine, type, section table, `.text` bytes, and `_start` symbol.

This remains deliberately small: only `.text` is supported and there are no relocations yet. Relocations/data sections belong to the next ELF64 increment rather than being hidden inside this seed.

## 0.0.23 — x86-64 Phase 1B.1 relocation seed

Adds the first ELF64 relocation needed by the future x86 linker.

- Adds `lea r64, [rel symbol]` for the base x86-64 registers in ELF64 mode.
- Emits RIP-relative LEA as `REX.W + 8D /r + rel32`.
- Emits `.rela.text` as an ELF64 `SHT_RELA` section.
- Emits `R_X86_64_PC32` relocations with the ABI-correct `-4` addend for RIP-relative displacement fields.
- Keeps `.symtab`, `.strtab`, and `.shstrtab` coherent with the relocation section links.
- Adds regression test `030_elf64_relocation.asm`.
- The regression test parses the ELF object directly and verifies the `.text` bytes, symbol values, relocation offset, symbol index, relocation type, and addend.

For this intentionally small phase, a `[rel symbol]` relocation target must be declared `global`, and ELF64 still supports only `.text`. Undefined externals, local-symbol relocations, `.rodata`/`.data`, and additional relocation types are deferred until the linker path requires them.


## 0.0.24 — 8086 encoding completion Phase 35: Group-1 immediates

Closes the complete 8086 Group-1 immediate encoding family rather than adding another isolated mnemonic.

- Completes all eight `/digit` operations: `ADD`, `OR`, `ADC`, `SBB`, `AND`, `SUB`, `XOR`, and `CMP`.
- Covers `80 /n ib` byte register and memory operands.
- Covers `83 /n ib` word register and memory operands when the immediate fits a signed byte.
- Covers `81 /n iw` word register and memory operands for full 16-bit immediates.
- Adds the previously missing `XOR` Group-1 immediate path.
- Normalizes non-accumulator `AND r16, imm8` to the same `83 /4 ib` policy used by the other Group-1 operations.
- Adds `031_group1_immediate.asm`, a 48-form matrix: each of the eight operations is tested as byte-register, word-register/small, word-register/large, byte-memory, word-memory/small, and word-memory/large.

This phase deliberately does not broaden the ISA beyond Group-1 immediates. Register/memory arithmetic rows, shifts/rotates, Group-3 unary/multiply/divide, and the addressing torture matrix remain later completion packs.

## 0.0.25 — 8086 encoding completion Phase 36: arithmetic/logical register ↔ r/m rows

Closes the four primary ModR/M opcode rows for all eight arithmetic/logical families: `ADD`, `OR`, `ADC`, `SBB`, `AND`, `SUB`, `XOR`, and `CMP`.

- Covers `r/m8, r8` and `r/m16, r16`.
- Covers `r8, r/m8` and `r16, r/m16`.
- Covers both register and memory r/m operands.
- Preserves explicit `byte` / `word` memory typing in either operand direction.
- Removes an older special-case `AND` immediate path that intercepted typed memory source operands before the general family encoder could handle them.
- Adds `032_group1_regmem.asm`, a 48-form matrix covering all eight families across register/register and both memory directions for byte and word operands.

Together with Phase 35, the primary 8086 arithmetic/logical rows and the Group-1 immediate rows are now fenced by family-wide exact-byte tests. Shift/rotate Group-2 remains the next completion pack.

## Phase 37 - 8086 Group-2 rotate/shift closure (0.0.26)

The original 8086 Group-2 family is now fenced across byte/word register and
memory operands for count `1` and `CL`: `ROL`, `ROR`, `RCL`, `RCR`, `SHL`/`SAL`,
`SHR`, and `SAR`.  This closes the defined D0/D1/D2/D3 `/digit` encodings.
The C0/C1 immediate-count forms are 80186+ and remain outside the 8086 baseline.
Test: `033_group2_shift_rotate.asm`.


## Phase 38 - 8086 Group-3 unary/multiply/divide closure (0.0.27)

The original 8086 Group-3 `F6/F7` family is now fenced across byte/word
register and explicitly-sized memory operands.  `TEST /0` immediate plus
`NOT /2`, `NEG /3`, `MUL /4`, `IMUL /5`, `DIV /6`, and `IDIV /7` are
covered.  The `/1` encoding remains undefined and is intentionally not exposed.
Memory operands for one-operand Group-3 instructions require `byte` or `word`
so the assembler does not guess between `F6` and `F7`.
Test: `034_group3_unary_mul_div.asm`.

## Phase 39 - 8086 stack-family closure (0.0.28)

The original 8086 stack family is now fenced as a complete unit.

- Covers compact `PUSH r16` (`50+rw`) and `POP r16` (`58+rw`) for all eight 16-bit GPRs.
- Covers `PUSH r/m16` (`FF /6`) and `POP r/m16` (`8F /0`) memory forms, including direct, indexed/BP-based addressing, displacement, and segment override cases.
- Covers `PUSH ES/CS/SS/DS` and the legal `POP ES/SS/DS` segment-register forms.
- Covers `PUSHF` and `POPF`.
- Explicitly regression-tests that `POP CS` is rejected because no such 8086 instruction encoding exists.
- Explicitly regression-tests that `PUSH imm` is rejected because immediate PUSH is an 80186+ extension and remains outside the 8086 completion fence.

The implementation audit found the required 8086 stack encodings were already present; Phase 39 therefore closes the family primarily by systematic exact-byte and boundary tests rather than adding duplicate encoder paths.

Tests: `035_stack_family.asm`, `036_push_immediate_8086_fail.asm`, and `037_pop_cs_fail.asm`.


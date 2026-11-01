# x86-objdump

Project-native inspection tool for current x86 artifacts.

It supports:

- 16-bit flat binaries, with optional load-address adjustment;
- Blackjack16 `BJO1` relocatable objects;
- BJO1 symbol tables (defined and undefined symbols);
- BJO1 relocation tables (`PC16` and `ABS16`);
- disassembly of the object's text payload.

Examples:

    x86-objdump --adjust-vma 0x8000 kernel.bin
    x86-objdump main.o

For a BJO1 object, the symbol and relocation sections are useful for proving
what the compiler/assembler emitted before linking. The final Blackjack16
output is currently a flat binary, so it does not retain a symbol table.

Tests:

    make test
    make test-x86
    make test-ndisasm
    make test-compare

`test-compare` canonicalizes whitespace/case and compares decoded
instructions with NASM's `ndisasm` when available.

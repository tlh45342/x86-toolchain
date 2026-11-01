# x86-ld

`x86-ld` is the project-native linker for the x86 toolchain.

## Supported paths

### Blackjack16 / BJO1

The Blackjack16 path accepts multiple `BJO1` relocatable objects from
`x86-as` and `x86-cc`, builds a global symbol table, resolves cross-object
references, applies `PC16` and `ABS16` relocations, and emits a 16-bit flat
binary.

Typical use:

    x86-ld -m blackjack16 -Ttext 0x8000 entry.o main.o helper.o -o kernel.bin

The regression suite includes ASM-to-C relocation, ABS16 relocation, and
mixed C/ASM execution in the x86 VM.

### ELF64

The ELF64 path accepts multiple x86-64 `ET_REL` objects, places their
`.text` sections, resolves global symbols, applies `R_X86_64_PC32`
relocations, and emits a static ELF64 `ET_EXEC` with one read/execute
`PT_LOAD` segment.

Typical use:

    x86-ld -m elf_x86_64 start.o helper.o -o hello

The ELF64 path intentionally does not yet support `.data`, `.bss`,
archives, linker scripts, libc/dynamic linking, or relocation types other
than `R_X86_64_PC32`.

Tests:

    make test
    python tests/run_blackjack16.py

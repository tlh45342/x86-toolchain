# BJOBJ2 named sections and linker placement proposal

**Status:** design specification, not yet implemented. The existing `BJO2`
writer and reader accept only a single TEXT section; see `BJO2_FORMAT.md`.
This proposal requires a versioned extension. Existing BJO2 readers must
reject it, never silently interpret the new header as the old layout.

## Section naming and semantics

A section is identified by a case-sensitive UTF-8 name, independent of its
storage class and its final location. Names beginning with `.` are conventional,
not privileged. The assembler accepts user-defined names and records their
attributes. The linker must not infer execution permissions or memory model
from a custom name alone.

| Conventional name | Class | Default flags | Default alignment |
|---|---|---|---:|
| `.text`, `.text.*` | PROGBITS | ALLOC, EXEC | 16 |
| `.rodata`, `.rodata.*` | PROGBITS | ALLOC, READ | 2 |
| `.data`, `.data.*` | PROGBITS | ALLOC, READ, WRITE | 2 |
| `.bss`, `.bss.*` | NOBITS | ALLOC, READ, WRITE, ZERO | 2 |
| `.stack` | NOBITS | ALLOC, READ, WRITE, STACK | 16 |

These are defaults only. A custom section must explicitly declare a class,
flags, and alignment, or be assigned attributes through a linker layout rule.
Unknown section names with no declared attributes are errors.

Proposed assembler syntax (NOT IMPLEMENTED):

```asm
section .text
section .drivers, progbits, alloc, exec, align=16
section .config, progbits, alloc, read, align=2
section .scratch, nobits, alloc, write, zero, align=16
```

Reentering a section appends to its contents and restores its location counter.
Labels are section-relative. `org` is invalid in relocatable sectioned objects;
absolute placement belongs in the linker layout. `NOBITS` cannot emit DB/DW
initialized bytes; reservation directives advance its memory size only.

## Object representation: proposed revision

Use a distinct magic/version (e.g. `BJO3`) or a separately negotiated major
format version. Never repurpose the currently implemented 20-byte BJO2 header.
The file must contain:

1. A fixed-size header with version, counts, offsets, and bounds for tables.
2. A section table: name offset/length, type, flags, alignment, logical size,
   payload file offset/size, and optional grouping or COMDAT identifier.
3. A symbol table: name, binding (local/global/weak), section index, value,
   size, and optional absolute/undefined classification.
4. A relocation table: source section index, source offset, target symbol
   index, relocation type, and **signed addend**.
5. A length-delimited string table and payload bytes for PROGBITS sections.

All multi-byte integers are little-endian. Section indices are stable within
one object and start at 1; 0 means undefined or absolute as explicitly tagged.
Section alignment must be a nonzero power of two. `NOBITS` has memory size but
zero payload file size. Reject integer overflow, overlapping payload ranges,
invalid indices, unsupported relocation types, and duplicate strong globals.

## 8086 memory model and relocations

`TEXT` sections can be assigned separate CS windows; all near data references
in Medium model use one shared DS window, and the stack uses SS. The linker
must enforce 64 KiB maximum offsets within each segment, account for paragraph
alignment, and reject code or data that exceeds the real-mode address space.

Proposed relocation semantics:

- `PC16`: signed/modulo-16 relative branch within the *same CS*.
- `FAR32`: offset:segment address of target code; encodes 4 bytes.
- `DATA16`: 16-bit offset from the common DS base; target must be data.
- `CODE16`: 16-bit offset within the target code segment; requires an
  unambiguous segment selection and must not masquerade as a near call.
- `SEG16`: paragraph segment address of the target's assigned segment.

Relocations should use explicit signed addends, not infer them from the
instruction stream. Validate target section class and overflow at link time.

## Linker layout and ordering

The linker, not the assembler, determines physical order. A future layout
language could support named output groups and patterns:

```text
MEMORY code  origin=0x08000 length=0x60000
MEMORY data  origin=0x68000 length=0x10000
MEMORY stack origin=0x78000 length=0x04000

OUTPUT code : code { .text .text.* .drivers } align=16
OUTPUT data : data { .rodata .data .data.* .config } align=16
OUTPUT bss  : data { .bss .bss.* .scratch } align=16 nobits
```

This syntax is illustrative and is NOT accepted by x86-ld today.
Ordering rules should use stable object-input order as a tie-breaker, detect
unmatched allocated sections, reject conflicting attributes, and provide an
explicit KEEP facility for sections not referenced by relocations. Optional
subsection priorities can be added later without changing the object format.

The linker must report a map: section, input object, group, physical base,
logical segment:offset, file size, memory size, and symbols. A binary kernel
needs startup metadata for the shared DS, DATA initialization, and BSS zeroing.

## Required acceptance tests

- Two objects define and reference a shared DATA global across different CS.
- DATA initializers survive load; BSS is zero before C starts.
- A custom `.drivers` executable section is ordered after `.text` by layout.
- A custom `.config` section is placed in the common DS window.
- Unmatched or conflicting custom sections fail with actionable diagnostics.
- Near calls across CS fail; FAR32 succeeds beyond physical 64 KiB.
- Objdump lists custom section names, flags, alignment, symbols, relocations,
  and does not disassemble PROGBITS data or NOBITS sections.
- Existing BJO1 and single-TEXT BJO2 compatibility tests remain passing.

# Medium model: segmented code and shared near data

## Current verified behavior

The `blackjack16-medium` linker places BJO1 objects on paragraph boundaries.
FAR32 relocations resolve to the destination object's CS and its local IP.
The VM regression executes a far call beyond physical 0x10000, checks AX=42,
and checks that the caller's stack pointer and CS:IP are restored.

This is a *code-segmentation prototype*, not yet a complete Medium-model
linker. In particular, BJO1 has no distinction between code and data.

## Required object-format evolution

Introduce a versioned object format (BJO2) rather than reinterpreting the
existing BJO1 ABS16 relocation. Preserve BJO1 for existing Small binaries.

Each BJO2 section needs a kind (TEXT, DATA, BSS), size, alignment, and bytes
except for BSS. Every symbol must identify its defining section and offset.
Every relocation must identify its *source* section, source offset, target
symbol/section, addend, and relocation kind.

Suggested relocation semantics:

* PC16: relative 16-bit code displacement, valid only within the same CS.
* FAR32: target code segment plus target offset.
* DATA16: target offset relative to the common DS base.
* CODE16: target offset relative to the intended code segment.
* SEG16: segment word for a named section, for startup or far pointers.

The linker must reject a near branch between different code segments, data
references outside the 64 KiB DS window, and any relocation whose section
identity is unknown. In particular, BJO1 ABS16 must not be silently treated
as a DS-relative address in Medium mode.

## Proposed physical layout

The loader receives a contiguous kernel image. TEXT sections occupy paragraph-
aligned regions, with far-call targets resolved to their assigned CS:IP.
DATA and BSS are grouped into one near-data region, whose paragraph base is
installed into DS by the startup code before any C global access. BSS must be
zeroed before C initialization. The kernel stack has its own SS:SP policy.

An important compatibility issue: compiler-generated pointers to globals,
strings, static objects, and function pointers must be audited separately.
A pointer to a local variable remains SS-relative when dereferenced, which
cannot be assumed to be the same as DS. This also needs ABI tests.

## Acceptance tests before enabling kernel linking

1. Two separate C objects share an initialized global through DS.
2. One object updates a global and another reads the updated value.
3. Strings, BSS, arrays and global pointers resolve through the same DS.
4. Far calls cross physical 64 KiB while DS and SS remain correct.
5. Near calls crossing code segments are rejected at link time.
6. Startup initializes DS and clears BSS before invoking C.
7. Existing Small-model tests and Blackjack boot remain unchanged.

Do not mark Medium kernel boot support complete until these tests and an
actual Blackjack boot pass.

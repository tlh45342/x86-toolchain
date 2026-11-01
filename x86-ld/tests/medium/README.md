# Medium-model incremental regression probes

Compile each C file with `x86-cc --model=medium -S` first, then with `-c` and the current development assembler on PATH.

01: local far call/return; expected AX=42. Confirm `call far` and `retf`.
02: two stack arguments; expected AX=42. Confirm `[bp+6]` and `[bp+8]`.
03: near global data; expected AX=42. Requires correct DS initialization and ABS16 relocation.
04: far function accessing near global data; expected AX=42. Requires DS preserved across CS changes.

These are *compile/assembly probes*, not VM execution tests. A passing object build does not validate segment placement, DS, SS, or runtime semantics. The segmented linker and boot entry are not implemented yet.

Next tests: explicit assembly near/far caller, cross-object far call, far call over 64 KiB, multiple segments with shared DS, recursion, and far function pointers.

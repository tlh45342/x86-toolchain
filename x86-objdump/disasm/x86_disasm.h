// src/cpu/disasm.h

#pragma once
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    size_t len;        // bytes consumed
    char   text[192];   // disassembly
    bool   ok;         // decoded something known
} x86_disasm_t;

/*
 * Disassemble ONE instruction from a byte window.
 * - bytes[0] is the opcode at CS:IP
 * - avail is how many bytes are available in the window
 *
 * Returns:
 * - d.len: instruction length (>= 1)
 * - d.ok : true if recognized
 * - d.text: mnemonic text
 */
x86_disasm_t x86_disasm(const uint8_t *bytes, size_t avail);

/* Address-aware form used by execution tracing so relative branch
 * targets are rendered from the architectural IP, not physical RAM. */
x86_disasm_t x86_disasm_at(const uint8_t *bytes, size_t avail, uint16_t ip);

/*
 * Back-compat wrapper for older callers that treat memory as a flat array
 * indexed by 'lin'. This calls x86_disasm() on mem+lin.
 */
x86_disasm_t x86_disasm_one_16(const uint8_t *mem, size_t memsz, uint32_t lin);
#ifndef BJ_SECTION_SYMBOLS_H
#define BJ_SECTION_SYMBOLS_H

#include "bj_section_object.h"

/* BJO3 symbol and relocation records. These routines extend the existing
 * section-payload codec; they do not change legacy BJO1/BJO2 layouts.
 * Section IDs are 1-based. Zero identifies an undefined symbol.
 * Relocation addends are signed 32-bit quantities encoded little-endian.
 */
typedef struct {
    char name[64];
    uint16_t section;
    uint16_t binding;
    uint32_t offset;
} BjSectionSymbol;

typedef struct {
    uint16_t source_section;
    uint16_t type;
    uint32_t source_offset;
    uint32_t symbol_index;
    int32_t addend;
} BjSectionRelocation;

static int bj_write_section_symbols(FILE *file,
                                    const BjSectionSymbol *symbols,
                                    size_t count, size_t section_count)
{
    size_t i;

    if (!file || count > UINT16_MAX || (count && !symbols) ||
        !bj_write_u16(file, (uint16_t)count)) {
        return 0;
    }
    for (i = 0; i < count; ++i) {
        const BjSectionSymbol *symbol = &symbols[i];

        if (symbol->section > section_count ||
            fwrite(symbol->name, 1, sizeof(symbol->name), file) !=
                sizeof(symbol->name) ||
            !bj_write_u16(file, symbol->section) ||
            !bj_write_u16(file, symbol->binding) ||
            !bj_write_u32(file, symbol->offset)) {
            return 0;
        }
    }
    return !ferror(file);
}

static int bj_write_section_relocations(FILE *file,
                                        const BjSectionRelocation *relocations,
                                        size_t count, size_t section_count,
                                        size_t symbol_count)
{
    size_t i;

    if (!file || count > UINT16_MAX || (count && !relocations) ||
        !bj_write_u16(file, (uint16_t)count)) {
        return 0;
    }
    for (i = 0; i < count; ++i) {
        const BjSectionRelocation *relocation = &relocations[i];

        if (!relocation->source_section ||
            relocation->source_section > section_count ||
            relocation->symbol_index >= symbol_count ||
            !bj_write_u16(file, relocation->source_section) ||
            !bj_write_u16(file, relocation->type) ||
            !bj_write_u32(file, relocation->source_offset) ||
            !bj_write_u32(file, relocation->symbol_index) ||
            !bj_write_u32(file, (uint32_t)relocation->addend)) {
            return 0;
        }
    }
    return !ferror(file);
}

#endif

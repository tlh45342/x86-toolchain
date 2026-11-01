#ifndef BJ_SECTION_OBJECT_H
#define BJ_SECTION_OBJECT_H

#include "bj_sections.h"

/* BJO3 sectioned object envelope. All integer fields are little-endian.
 * Header: magic[4], section_count:u16, reserved:u16.
 * Each section: name[64], type:u32, flags:u32, alignment:u32,
 * logical_size:u32, payload_size:u32, followed by payload bytes.
 * Symbols and relocations are deliberately NOT encoded by this module;
 * this is a section-payload codec, not yet a linkable object format. */
static int bj_write_u16(FILE *file, uint16_t value)
{
    return fputc(value & 255, file) != EOF &&
           fputc((value >> 8) & 255, file) != EOF;
}

static int bj_write_u32(FILE *file, uint32_t value)
{
    return bj_write_u16(file, (uint16_t)value) &&
           bj_write_u16(file, (uint16_t)(value >> 16));
}

static int bj_write_section_payloads(FILE *file, const BjSections *table)
{
    size_t i;

    if (!file || !table || table->count > BJ_MAX_SECTIONS ||
        !bj_write_u16(file, (uint16_t)table->count) ||
        !bj_write_u16(file, 0)) {
        return 0;
    }
    for (i = 0; i < table->count; ++i) {
        const BjSection *section = &table->sections[i];
        uint32_t payload_size = section->type == BJ_SECTION_NOBITS ? 0 : section->size;

        if (fwrite(section->name, 1, sizeof(section->name), file) !=
                sizeof(section->name) ||
            !bj_write_u32(file, section->type) ||
            !bj_write_u32(file, section->flags) ||
            !bj_write_u32(file, section->alignment) ||
            !bj_write_u32(file, section->size) ||
            !bj_write_u32(file, payload_size)) {
            return 0;
        }
        if (payload_size &&
            (!section->bytes || fwrite(section->bytes, 1, payload_size, file) != payload_size)) {
            return 0;
        }
    }
    return !ferror(file);
}

#endif

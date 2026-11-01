#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "disasm/x86_disasm.h"

#define VER "0.0.3"

static uint16_t r16(const unsigned char *p)
{
    return (uint16_t)(p[0] | ((uint16_t)p[1] << 8));
}

static uint32_t r32(const unsigned char *p)
{
    return (uint32_t)p[0] | ((uint32_t)p[1] << 8) |
           ((uint32_t)p[2] << 16) | ((uint32_t)p[3] << 24);
}

static unsigned char *load(const char *path, size_t *length)
{
    FILE *file = fopen(path, "rb");
    unsigned char *bytes;
    long size;
    if (!file) {
        fprintf(stderr, "x86-objdump: %s: %s\n", path, strerror(errno));
        return NULL;
    }
    if (fseek(file, 0, SEEK_END) || (size = ftell(file)) < 0 ||
        fseek(file, 0, SEEK_SET)) {
        fclose(file);
        return NULL;
    }
    bytes = malloc(size ? (size_t)size : 1);
    if (!bytes || (size && fread(bytes, 1, (size_t)size, file) != (size_t)size)) {
        free(bytes);
        fclose(file);
        return NULL;
    }
    fclose(file);
    *length = (size_t)size;
    return bytes;
}

static void disassemble(const unsigned char *bytes, size_t size, uint16_t base)
{
    size_t pos = 0;
    puts("\nDISASSEMBLY");
    while (pos < size) {
        x86_disasm_t insn = x86_disasm_at(bytes + pos, size - pos,
                                          (uint16_t)(base + pos));
        size_t len = insn.len ? insn.len : 1;
        printf("%04X  ", (unsigned)(uint16_t)(base + pos));
        for (size_t i = 0; i < 6; i++) {
            printf(i < len && pos + i < size ? "%02X " : "   ",
                   i < len && pos + i < size ? bytes[pos + i] : 0);
        }
        printf(" %s\n", insn.text);
        pos += len;
    }
}

static const char *relocation_name(unsigned type)
{
    switch (type) {
    case 1: return "PC16";
    case 2: return "ABS16";
    case 3: return "FAR32";
    case 4: return "DATA16";
    case 5: return "CODE16";
    case 6: return "SEG16";
    default: return "UNKNOWN";
    }
}

/* BJO2 currently supports one TEXT section. Reject unsupported layouts
 * rather than treating DATA or BSS bytes as executable instructions. */
static int dump_bjo3(const char *path, const unsigned char *bytes, size_t size);

static int dump_object(const char *path, const unsigned char *bytes, size_t size)
{
    int v2 = memcmp(bytes, "BJO2", 4) == 0;
    uint16_t symbols, relocations;
    uint32_t text_size;
    size_t pos, entry_size;
    if (v2) {
        if (size < 20 || r16(bytes + 4) != 1 || r16(bytes + 12) != 1 ||
            r16(bytes + 18) != 16) {
            fprintf(stderr, "x86-objdump: unsupported BJO2 section layout\n");
            return 1;
        }
        symbols = r16(bytes + 6);
        relocations = r16(bytes + 8);
        text_size = r32(bytes + 14);
        pos = 20;
        entry_size = 71;
        printf("%s: BJO2, sections=1, symbols=%u, relocations=%u\n",
               path, symbols, relocations);
        printf("\nSECTIONS\n[1] .text size=%u align=16\n", text_size);
    } else {
        symbols = r16(bytes + 8);
        relocations = r16(bytes + 10);
        text_size = r32(bytes + 4);
        pos = 12;
        entry_size = 69;
        printf("%s: BJO1, text=%u, symbols=%u, relocations=%u\n",
               path, text_size, symbols, relocations);
    }
    if ((size_t)symbols > (size - pos) / entry_size ||
        (size_t)relocations > (size - pos - (size_t)symbols * entry_size) / entry_size ||
        text_size > size - pos - ((size_t)symbols + relocations) * entry_size) {
        fprintf(stderr, "x86-objdump: truncated object\n");
        return 1;
    }
    puts("\nSYMBOLS");
    for (unsigned i = 0; i < symbols; i++, pos += entry_size) {
        char name[65] = {0};
        unsigned section = v2 ? r16(bytes + pos + 64) : 1;
        unsigned value = r32(bytes + pos + (v2 ? 66 : 64));
        unsigned defined = bytes[pos + (v2 ? 70 : 68)];
        memcpy(name, bytes + pos, 64);
        if (v2 && section > 1) {
            fprintf(stderr, "x86-objdump: invalid symbol section %u\n", section);
            return 1;
        }
        printf("%c %-5s %04X %s\n", defined ? 'D' : 'U',
               v2 ? (section == 1 ? ".text" : "UND") : "flat",
               value, name);
    }
    puts("\nRELOCATIONS");
    for (unsigned i = 0; i < relocations; i++, pos += entry_size) {
        char name[65] = {0};
        unsigned section = v2 ? r16(bytes + pos + 64) : 1;
        unsigned offset = r32(bytes + pos + (v2 ? 66 : 64));
        unsigned type = bytes[pos + (v2 ? 70 : 68)];
        memcpy(name, bytes + pos, 64);
        if (v2 && section != 1) {
            fprintf(stderr, "x86-objdump: invalid relocation section %u\n", section);
            return 1;
        }
        printf("%-5s %04X %-7s %s\n", v2 ? ".text" : "flat",
               offset, relocation_name(type), name[0] ? name : "<object-local>");
    }
    disassemble(bytes + pos, text_size, 0);
    return 0;
}

/* BJO3 uses variable-length section payloads and indexed relocations. */
static int dump_bjo3(const char *path, const unsigned char *bytes, size_t size)
{
    size_t pos = 8, text_pos = 0, text_size = 0;
    unsigned text_count = 0;
    uint16_t section_count, symbol_count, relocation_count;
    char names[16][65] = {{0}};

    if (size < 8 || (section_count = r16(bytes + 4)) == 0 ||
        section_count > 16 || r16(bytes + 6) != 0) goto invalid;
    printf("%s: BJO3, sections=%u\n", path, section_count);
    puts("\nSECTIONS");
    for (unsigned i = 0; i < section_count; ++i) {
        uint32_t kind, flags, alignment, logical, payload;
        if (pos > size || size - pos < 84 ||
            !memchr(bytes + pos, 0, 64)) goto invalid;
        memcpy(names[i], bytes + pos, 64);
        kind = r32(bytes + pos + 64);
        flags = r32(bytes + pos + 68);
        alignment = r32(bytes + pos + 72);
        logical = r32(bytes + pos + 76);
        payload = r32(bytes + pos + 80);
        pos += 84;
        if (payload > size - pos || (kind == 2 && payload != 0) ||
            (kind == 1 && payload != logical)) goto invalid;
        printf("[%u] %-8s size=%u payload=%u kind=%u flags=%u align=%u\n",
               i + 1, names[i], logical, payload, kind, flags, alignment);
        if ((flags & 2) && kind == 1) {
            text_pos = pos;
            text_size = payload;
            text_count++;
        }
        pos += payload;
    }
    if (pos > size || size - pos < 2) goto invalid;
    symbol_count = r16(bytes + pos);
    pos += 2;
    if (symbol_count > (size - pos) / 72) goto invalid;
    puts("\nSYMBOLS");
    for (unsigned i = 0; i < symbol_count; ++i) {
        const unsigned char *sym = bytes + pos + (size_t)i * 72;
        uint16_t section = r16(sym + 64);
        if (!memchr(sym, 0, 64) || section > section_count) goto invalid;
        printf("[%u] %-8s %04X %s\n", i,
               section ? names[section - 1] : "UND",
               r32(sym + 68), (const char *)sym);
    }
    pos += (size_t)symbol_count * 72;
    if (pos > size || size - pos < 2) goto invalid;
    relocation_count = r16(bytes + pos);
    pos += 2;
    if (relocation_count > (size - pos) / 16 ||
        (size_t)relocation_count * 16 != size - pos) goto invalid;
    puts("\nRELOCATIONS");
    for (unsigned i = 0; i < relocation_count; ++i) {
        const unsigned char *rel = bytes + pos + (size_t)i * 16;
        unsigned section = r16(rel);
        unsigned symbol = r32(rel + 8);
        if (!section || section > section_count || symbol >= symbol_count)
            goto invalid;
        printf("%-8s %04X %-7s symbol[%u] addend=%d\n",
               names[section - 1], r32(rel + 4),
               relocation_name(r16(rel + 2)), symbol, (int32_t)r32(rel + 12));
    }
    if (text_count > 1) goto invalid;
    if (text_size) {
        puts("\nEXECUTABLE SECTION .text");
        disassemble(bytes + text_pos, text_size, 0);
    } else {
        puts("\nNO EXECUTABLE SECTION");
    }
    return 0;
invalid:
    fprintf(stderr, "x86-objdump: malformed BJO3 object: %s\n", path);
    return 1;
}

#include "omf_dump.h"

int main(int argc, char **argv)
{
    const char *path = NULL;
    uint16_t base = 0;
    unsigned char *bytes;
    size_t size;
    int status;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--version") == 0) {
            printf("x86-objdump %s\n", VER);
            return 0;
        }
        if (strcmp(argv[i], "--adjust-vma") == 0 && i + 1 < argc) {
            char *end;
            unsigned long value = strtoul(argv[++i], &end, 0);
            if (*end || value > 0xffff) return 2;
            base = (uint16_t)value;
        } else if (argv[i][0] == '-') {
            fprintf(stderr, "usage: x86-objdump [--adjust-vma N] FILE\n");
            return 2;
        } else {
            path = argv[i];
        }
    }
    if (!path) return 2;
    bytes = load(path, &size);
    if (!bytes) return 1;
    if (size >= 8 && memcmp(bytes, "BJO3", 4) == 0) {
        status = dump_bjo3(path, bytes, size);
    } else if (size >= 12 && (memcmp(bytes, "BJO1", 4) == 0 ||
                       memcmp(bytes, "BJO2", 4) == 0)) {
        status = dump_object(path, bytes, size);
    } else if (size >= 4 && bytes[0] == 0x80) {
        status = dump_omf(path, bytes, size);
    } else {
        printf("%s: flat binary, %u bytes\n", path, (unsigned)size);
        disassemble(bytes, size, base);
        status = 0;
    }
    free(bytes);
    return status;
}

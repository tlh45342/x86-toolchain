#include "../bj_section_symbols.h"
#include <assert.h>
#include <stdio.h>

static uint32_t read32(const unsigned char *bytes)
{
    return (uint32_t)bytes[0] | ((uint32_t)bytes[1] << 8) |
           ((uint32_t)bytes[2] << 16) | ((uint32_t)bytes[3] << 24);
}

int main(void)
{
    BjSections sections = {0};
    BjSectionSymbol symbols[2] = {0};
    BjSectionRelocation relocations[1] = {0};
    unsigned char bytes[256] = {0};
    FILE *file = tmpfile();
    size_t length;

    assert(file);
    (void)bj_section_emit;
    (void)bj_write_section_payloads;
    assert(bj_section_select(&sections, ".text", BJ_SECTION_PROGBITS,
                             BJ_SECTION_ALLOC | BJ_SECTION_EXEC, 16) == 1);
    assert(bj_section_select(&sections, ".data", BJ_SECTION_PROGBITS,
                             BJ_SECTION_ALLOC | BJ_SECTION_WRITE, 2) == 2);
    strcpy(symbols[0].name, "start");
    symbols[0].section = 1;
    symbols[0].binding = 1;
    strcpy(symbols[1].name, "counter");
    symbols[1].section = 2;
    symbols[1].offset = 4;
    relocations[0].source_section = 1;
    relocations[0].type = 4; /* DATA16 */
    relocations[0].source_offset = 7;
    relocations[0].symbol_index = 1;
    relocations[0].addend = -3;

    assert(bj_write_section_symbols(file, symbols, 2, sections.count));
    assert(bj_write_section_relocations(file, relocations, 1,
                                        sections.count, 2));
    rewind(file);
    length = fread(bytes, 1, sizeof(bytes), file);
    assert(length == 2 + 2 * 72 + 2 + 16);
    assert(strcmp((char *)bytes + 2, "start") == 0);
    assert(read32(bytes + 2 + 72 + 68) == 4);
    assert(read32(bytes + 2 + 144 + 2 + 4) == 7);
    assert(read32(bytes + 2 + 144 + 2 + 12) == UINT32_MAX - 2);
    fclose(file);

    file = tmpfile();
    assert(file);
    relocations[0].symbol_index = 2;
    assert(!bj_write_section_relocations(file, relocations, 1,
                                         sections.count, 2));
    fclose(file);
    bj_sections_destroy(&sections);
    puts("PASS BJO3 symbol and relocation encoding and validation");
    return 0;
}

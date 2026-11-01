#include "../bj_sections.h"
#include <assert.h>
#include <stdio.h>

int main(void)
{
    BjSections sections = {0};
    const unsigned char first[] = {0x90, 0x90};
    const unsigned char driver[] = {0xb8, 0x2a, 0x00, 0xcb};
    const unsigned char last[] = {0xf4};

    assert(bj_section_select(&sections, ".text", BJ_SECTION_PROGBITS,
                             BJ_SECTION_ALLOC | BJ_SECTION_EXEC, 16) == 1);
    assert(bj_section_emit(&sections, first, sizeof(first)));
    assert(bj_section_select(&sections, ".drivers", BJ_SECTION_PROGBITS,
                             BJ_SECTION_ALLOC | BJ_SECTION_EXEC, 16) == 2);
    assert(bj_section_emit(&sections, driver, sizeof(driver)));
    assert(bj_section_select(&sections, ".text", BJ_SECTION_PROGBITS,
                             BJ_SECTION_ALLOC | BJ_SECTION_EXEC, 16) == 1);
    assert(bj_section_emit(&sections, last, sizeof(last)));
    assert(sections.sections[0].size == 3);
    assert(sections.sections[0].bytes[2] == 0xf4);
    assert(sections.sections[1].size == sizeof(driver));
    assert(memcmp(sections.sections[1].bytes, driver, sizeof(driver)) == 0);

    assert(bj_section_select(&sections, ".bss", BJ_SECTION_NOBITS,
                             BJ_SECTION_ALLOC | BJ_SECTION_WRITE, 2) == 3);
    assert(bj_section_emit(&sections, NULL, 512));
    assert(sections.sections[2].size == 512);
    assert(sections.sections[2].bytes == NULL);
    assert(!bj_section_emit(&sections, first, sizeof(first)));
    assert(!bj_section_select(&sections, ".drivers", BJ_SECTION_NOBITS,
                              BJ_SECTION_ALLOC, 16));
    assert(!bj_section_select(&sections, ".bad", BJ_SECTION_PROGBITS,
                              BJ_SECTION_ALLOC, 3));
    bj_sections_destroy(&sections);
    puts("PASS named sections, switching, BSS and validation");
    return 0;
}

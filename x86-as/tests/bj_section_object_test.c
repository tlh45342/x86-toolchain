#include "../bj_section_object.h"
#include <assert.h>
#include <stdio.h>

static uint32_t read32(const unsigned char *p)
{
    return (uint32_t)p[0] | ((uint32_t)p[1] << 8) |
           ((uint32_t)p[2] << 16) | ((uint32_t)p[3] << 24);
}

int main(void)
{
    BjSections table = {0};
    unsigned char bytes[512] = {0};
    const unsigned char code[] = {0xb8, 0x2a, 0, 0xcb};
    FILE *file = tmpfile();
    size_t length;

    assert(file != NULL);
    assert(bj_section_select(&table, ".drivers", BJ_SECTION_PROGBITS,
                             BJ_SECTION_ALLOC | BJ_SECTION_EXEC, 16));
    assert(bj_section_emit(&table, code, sizeof(code)));
    assert(bj_section_select(&table, ".bss", BJ_SECTION_NOBITS,
                             BJ_SECTION_ALLOC | BJ_SECTION_WRITE, 2));
    assert(bj_section_emit(&table, NULL, 100));
    assert(bj_write_section_payloads(file, &table));
    rewind(file);
    length = fread(bytes, 1, sizeof(bytes), file);
    assert(length == 4 + 84 + 4 + 84);
    assert(bytes[0] == 2 && bytes[1] == 0);
    assert(strcmp((const char *)bytes + 4, ".drivers") == 0);
    assert(read32(bytes + 4 + 76) == sizeof(code));
    assert(memcmp(bytes + 4 + 84, code, sizeof(code)) == 0);
    assert(strcmp((const char *)bytes + 4 + 84 + 4, ".bss") == 0);
    assert(read32(bytes + 4 + 84 + 4 + 80) == 0);
    fclose(file);
    bj_sections_destroy(&table);

    /* Names must be data, not a hard-coded whitelist. */
    {
        BjSections custom = {0};
        const unsigned char alpha[] = {0x90};
        const unsigned char omega[] = {0xf4};
        FILE *stream = tmpfile();
        unsigned char encoded[256] = {0};
        size_t used;

        assert(stream != NULL);
        assert(bj_section_select(&custom, ".alpha", BJ_SECTION_PROGBITS,
                                 BJ_SECTION_ALLOC | BJ_SECTION_EXEC, 16) == 1);
        assert(bj_section_emit(&custom, alpha, sizeof(alpha)));
        assert(bj_section_select(&custom, ".omega", BJ_SECTION_PROGBITS,
                                 BJ_SECTION_ALLOC | BJ_SECTION_EXEC, 16) == 2);
        assert(bj_section_emit(&custom, omega, sizeof(omega)));
        assert(bj_write_section_payloads(stream, &custom));
        rewind(stream);
        used = fread(encoded, 1, sizeof(encoded), stream);
        assert(used == 4 + 85 + 85);
        assert(strcmp((const char *)encoded + 4, ".alpha") == 0);
        assert(strcmp((const char *)encoded + 4 + 85, ".omega") == 0);
        assert(encoded[4 + 84] == 0x90);
        assert(encoded[4 + 85 + 84] == 0xf4);
        fclose(stream);
        bj_sections_destroy(&custom);
    }
    puts("PASS named section payload encoding and NOBITS serialization");
    return 0;
}

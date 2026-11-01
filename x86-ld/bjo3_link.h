/* BJO3 TEXT-only linker. The sectioned data model is intentionally rejected
 * until segment-aware placement and typed relocations are implemented. */
#ifndef BJO3_LINK_H
#define BJO3_LINK_H

typedef struct {
    unsigned char *bytes;
    size_t length, text_offset, text_size, output_offset;
    size_t data_offset, data_size, data_output, bss_size, bss_output;
    uint16_t data_id, bss_id;
    uint16_t symbol_count, relocation_count;
    size_t symbol_offset, relocation_offset;
} Bjo3Object;

static int bjo3_parse(Bjo3Object *object, const char *path)
{
    size_t cursor = 8;
    uint32_t kind, flags, alignment, logical_size, payload_size;

    object->bytes = read_file(path, &object->length);
    if (!object->bytes || object->length < 8 ||
        memcmp(object->bytes, "BJO3", 4) ||
        (rd16(object->bytes + 4) < 1 || rd16(object->bytes + 4) > 3) || rd16(object->bytes + 6) != 0 ||
        !range_ok(object->length, cursor, 84)) goto invalid;
    kind = rd32(object->bytes + cursor + 64);
    flags = rd32(object->bytes + cursor + 68);
    alignment = rd32(object->bytes + cursor + 72);
    logical_size = rd32(object->bytes + cursor + 76);
    payload_size = rd32(object->bytes + cursor + 80);
    if (strcmp((const char *)(object->bytes + cursor), ".text") ||
        kind != 1 || flags != 3 || alignment != 16 ||
        logical_size != payload_size) goto invalid;
    cursor += 84;
    if (!range_ok(object->length, cursor, payload_size)) goto invalid;
    object->text_offset = cursor;
    object->text_size = payload_size;
    cursor += payload_size;
    for (uint16_t id = 2; id <= rd16(object->bytes + 4); ++id) {
        if (!range_ok(object->length, cursor, 84) ||
            !memchr(object->bytes + cursor, 0, 64)) goto invalid;
        const char *name = (const char *)(object->bytes + cursor);
        kind = rd32(object->bytes + cursor + 64);
        flags = rd32(object->bytes + cursor + 68);
        alignment = rd32(object->bytes + cursor + 72);
        logical_size = rd32(object->bytes + cursor + 76);
        payload_size = rd32(object->bytes + cursor + 80);
        cursor += 84;
        if (alignment != 16 || !range_ok(object->length, cursor, payload_size))
            goto invalid;
        if (!strcmp(name, ".data") && !object->data_id &&
            kind == 1 && flags == 5 && logical_size == payload_size) {
            object->data_id = id;
            object->data_offset = cursor;
            object->data_size = payload_size;
        } else if (!strcmp(name, ".bss") && !object->bss_id &&
                   kind == 2 && flags == 5 && payload_size == 0) {
            object->bss_id = id;
            object->bss_size = logical_size;
        } else goto invalid;
        cursor += payload_size;
    }
    if (!range_ok(object->length, cursor, 2)) goto invalid;
    object->symbol_count = rd16(object->bytes + cursor);
    cursor += 2;
    object->symbol_offset = cursor;
    if (!range_ok(object->length, cursor, (size_t)object->symbol_count * 72)) goto invalid;
    cursor += (size_t)object->symbol_count * 72;
    if (!range_ok(object->length, cursor, 2)) goto invalid;
    object->relocation_count = rd16(object->bytes + cursor);
    cursor += 2;
    object->relocation_offset = cursor;
    if (!range_ok(object->length, cursor, (size_t)object->relocation_count * 16) ||
        cursor + (size_t)object->relocation_count * 16 != object->length) goto invalid;
    for (size_t i = 0; i < object->symbol_count; ++i) {
        const unsigned char *symbol = object->bytes + object->symbol_offset + i * 72;
        uint16_t section = rd16(symbol + 64);
        size_t limit = section == 1 ? object->text_size :
                       section == object->data_id ? object->data_size :
                       section == object->bss_id ? object->bss_size : 0;
        if (!memchr(symbol, 0, 64) || section > rd16(object->bytes + 4) ||
            (section && !limit && rd32(symbol + 68) != 0) ||
            (section && rd32(symbol + 68) > limit)) goto invalid;
    }
    for (size_t i = 0; i < object->relocation_count; ++i) {
        const unsigned char *rel = object->bytes + object->relocation_offset + i * 16;
        uint16_t type = rd16(rel + 2);
        size_t width = type == 3 ? 4 : 2;
        if (rd16(rel) != 1 || (type != 1 && type != 3 && type != 4 && type != 5 && type != 6) ||
            rd32(rel + 8) >= object->symbol_count ||
            !range_ok(object->text_size, rd32(rel + 4), width)) goto invalid;
    }
    return 1;
invalid:
    fprintf(stderr, "x86-ld: invalid or unsupported BJO3 TEXT object: %s\n", path);
    return 0;
}

static int bjo3_resolve(const Bjo3Object *objects, int count, int owner,
                        uint32_t symbol_index, uint32_t *address,
                        int *owner_out, uint16_t *section_out)
{
    const Bjo3Object *object = &objects[owner];
    const unsigned char *symbol = object->bytes + object->symbol_offset +
                                  (size_t)symbol_index * 72;
    uint16_t section = rd16(symbol + 64);
    if (section) {
        size_t start = section == 1 ? object->output_offset :
                       section == object->data_id ? object->data_output :
                       object->bss_output;
        *address = (uint32_t)(start + rd32(symbol + 68));
        *owner_out = owner;
        *section_out = section;
        return 1;
    }
    for (int i = 0; i < count; ++i) {
        for (size_t j = 0; j < objects[i].symbol_count; ++j) {
            const unsigned char *candidate = objects[i].bytes +
                                             objects[i].symbol_offset + j * 72;
            if (rd16(candidate + 64) != 0 && rd16(candidate + 66) == 1 &&
                !strcmp((const char *)symbol, (const char *)candidate)) {
                uint16_t id = rd16(candidate + 64);
                size_t start = id == 1 ? objects[i].output_offset :
                               id == objects[i].data_id ? objects[i].data_output :
                               objects[i].bss_output;
                *address = (uint32_t)(start + rd32(candidate + 68));
                *owner_out = i;
                *section_out = id;
                return 1;
            }
        }
    }
    fprintf(stderr, "x86-ld: BJO3 undefined symbol: %s\n", symbol);
    return 0;
}

static int link_bjo3(const char **paths, int count, const char *output,
                     uint32_t base, int medium)
{
    Bjo3Object objects[MAX_INPUTS] = {{0}};
    unsigned char *image = NULL;
    size_t total = 0, data_start = 0, file_size = 0;
    FILE *file = NULL;
    int result = 1;

    if (medium && (base & 15u)) {
        fprintf(stderr, "x86-ld: medium model requires paragraph-aligned -Ttext (got 0x%X)\n", base);
        goto cleanup;
    }
    for (int i = 0; i < count; ++i) {
        if (!bjo3_parse(&objects[i], paths[i])) goto cleanup;
        if (medium) total = (total + 15) & ~(size_t)15;
        objects[i].output_offset = total;
        if (objects[i].text_size > SIZE_MAX - total) goto cleanup;
        total += objects[i].text_size;
    }
    int has_data = 0;
    for (int i = 0; i < count; ++i)
        if (objects[i].data_id || objects[i].bss_id) has_data = 1;
    if (has_data) total = (total + 15u) & ~(size_t)15u;
    data_start = total;
    for (int i = 0; i < count; ++i) {
        if (objects[i].data_id) {
            total = (total + 15u) & ~(size_t)15u;
            objects[i].data_output = total;
            total += objects[i].data_size;
        }
    }
    file_size = total;
    for (int i = 0; i < count; ++i) {
        if (objects[i].bss_id) {
            total = (total + 15u) & ~(size_t)15u;
            objects[i].bss_output = total;
            total += objects[i].bss_size;
        }
    }
    if ((uint64_t)base + total > (medium ? 0x100000u : 65536u) ||
        total - data_start > 65536u) {
        fprintf(stderr, "x86-ld: BJO3 TEXT-only output exceeds flat 64K\n");
        goto cleanup;
    }
    image = calloc(file_size ? file_size : 1, 1);
    if (!image) goto cleanup;
    for (int i = 0; i < count; ++i) {
        Bjo3Object *object = &objects[i];
        memcpy(image + object->output_offset,
               object->bytes + object->text_offset, object->text_size);
        if (object->data_id && object->data_size)
            memcpy(image + object->data_output,
                   object->bytes + object->data_offset, object->data_size);
    }
    for (int i = 0; i < count; ++i) {
        Bjo3Object *object = &objects[i];
        for (size_t j = 0; j < object->relocation_count; ++j) {
            const unsigned char *rel = object->bytes + object->relocation_offset + j * 16;
            uint32_t target, offset = rd32(rel + 4);
            int target_owner = -1;
            uint16_t target_section = 0;
            int64_t value;
            size_t location = object->output_offset + offset;
            if (!bjo3_resolve(objects, count, i, rd32(rel + 8), &target,
                              &target_owner, &target_section)) goto cleanup;
            value = (int64_t)target + (int32_t)rd32(rel + 12);
            if (rd16(rel + 2) == 6) {
                /* ABS16: ORG-based flat code with DS=0 addresses its
                 * local symbols by physical offset, including -Ttext. */
                value += (int64_t)base;
                if (value < 0 || value > UINT16_MAX) {
                    fprintf(stderr, "x86-ld: ABS16 address out of range: %s\n", paths[i]);
                    goto cleanup;
                }
                image[location] = (unsigned char)value;
                image[location + 1] = (unsigned char)(value >> 8);
            } else if (rd16(rel + 2) == 5) {
                /* CODE16 offset must be representable in the caller's CS.
                 * This initial rule assumes a bank begins at object start. */
                if (target < object->output_offset ||
                    target - object->output_offset > 65535u ||
                    value < (int64_t)object->output_offset ||
                    value - (int64_t)object->output_offset > 65535) {
                    fprintf(stderr, "x86-ld: CODE16 reference crosses code bank: %s\n",
                            paths[i]);
                    goto cleanup;
                }
                value -= (int64_t)object->output_offset;
                image[location] = (unsigned char)value;
                image[location + 1] = (unsigned char)(value >> 8);
            } else if (rd16(rel + 2) == 4) {
                /* A legacy assembly file may embed literals in .text.
                 * Such references are code-segment offsets, not DS data.
                 * Preserve the rejection until an explicit relocation type
                 * distinguishes CS-relative offsets from DS-relative ones. */
                if (target < data_start || target - data_start > 65535u) {
                    const unsigned char *sym = object->bytes + object->symbol_offset +
                                               (size_t)rd32(rel + 8) * 72;
                    fprintf(stderr,
                            "x86-ld: DATA16 target outside shared data segment: "
                            "object=%s symbol=%s target=0x%X data=[0x%zX,0x%zX) "
                            "reloc=0x%X\n",
                            paths[i], (const char *)sym, target, data_start,
                            total, offset);
                    goto cleanup;
                }
                value -= (int64_t)data_start;
                image[location] = (unsigned char)value;
                image[location + 1] = (unsigned char)(value >> 8);
            } else if (rd16(rel + 2) == 1) {
                /* REL16 addends already encode the instruction-specific
                 * adjustment (CALL uses -2). The relocation site is the
                 * displacement word, so do not subtract its width twice. */
                value -= (int64_t)location;
                if (value < INT16_MIN || value > INT16_MAX) {
                    fprintf(stderr, "x86-ld: REL16 out of range in %s, offset %u, symbol %s, delta %lld\n", paths[i], offset, (const char *)(object->bytes + object->symbol_offset + (size_t)rd32(rel + 8) * 72), (long long)value);
                    goto cleanup;
                }
                image[location] = (unsigned char)value;
                image[location + 1] = (unsigned char)(value >> 8);
            } else if (rd16(rel + 2) == 3) {
                uint32_t seg, off;
                if (medium) {
                    uint32_t tbase = (uint32_t)objects[target_owner].output_offset;
                    int64_t relative = value - (int64_t)tbase;
                    if (target_section != 1 || relative < 0 || relative > 65535) {
                        fprintf(stderr, "x86-ld: FAR32 target outside code bank: %s\n", paths[i]);
                        goto cleanup;
                    }
                    seg = (base + tbase) >> 4;
                    off = (uint32_t)relative;
                } else {
                    uint32_t linear = base + (uint32_t)value;
                    seg = linear >> 4;
                    off = linear & 15u;
                }
                image[location] = (unsigned char)off;
                image[location + 1] = (unsigned char)(off >> 8);
                image[location + 2] = (unsigned char)seg;
                image[location + 3] = (unsigned char)(seg >> 8);
            } else {
                fprintf(stderr, "x86-ld: unsupported BJO3 relocation type %u in %s\n",
                        rd16(rel + 2), paths[i]);
                goto cleanup;
            }
        }
    }
    file = fopen(output, "wb");
    if (!file || (file_size && fwrite(image, 1, file_size, file) != file_size)) goto cleanup;
    if (fclose(file)) { file = NULL; goto cleanup; }
    file = NULL;
    printf("linked %d BJO3 objects -> %s (%llu initialized bytes, %llu BSS bytes)\n",
           count, output, (unsigned long long)file_size,
           (unsigned long long)(total - file_size));
    result = 0;
cleanup:
    if (file) fclose(file);
    if (result) remove(output);
    for (int i = 0; i < count; ++i) free(objects[i].bytes);
    free(image);
    return result;
}
#endif

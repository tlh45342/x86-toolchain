#ifndef BJ_SECTIONS_H
#define BJ_SECTIONS_H

/* Named-section storage for the next sectioned Blackjack object revision.
 * This module does not change the legacy BJO1/BJO2 wire format. */
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BJ_MAX_SECTIONS 128
#define BJ_SECTION_NAME_MAX 64
#define BJ_SECTION_PROGBITS 1u
#define BJ_SECTION_NOBITS 2u
#define BJ_SECTION_ALLOC 1u
#define BJ_SECTION_EXEC 2u
#define BJ_SECTION_WRITE 4u

typedef struct {
    char name[BJ_SECTION_NAME_MAX];
    uint32_t type;
    uint32_t flags;
    uint32_t alignment;
    uint32_t size;
    uint32_t capacity;
    unsigned char *bytes;
} BjSection;

typedef struct {
    BjSection sections[BJ_MAX_SECTIONS];
    size_t count;
    size_t current;
} BjSections;

static void bj_sections_destroy(BjSections *table)
{
    size_t i;
    for (i = 0; i < table->count; ++i) {
        free(table->sections[i].bytes);
        table->sections[i].bytes = NULL;
    }
    memset(table, 0, sizeof(*table));
}

/* Returns 1-based section ID; 0 denotes an error. */
static unsigned bj_section_select(BjSections *table, const char *name,
                                  uint32_t type, uint32_t flags,
                                  uint32_t alignment)
{
    size_t i;
    BjSection *section;

    if (!name || !*name || strlen(name) >= BJ_SECTION_NAME_MAX ||
        (type != BJ_SECTION_PROGBITS && type != BJ_SECTION_NOBITS) ||
        !alignment || (alignment & (alignment - 1u))) {
        return 0;
    }
    for (i = 0; i < table->count; ++i) {
        section = &table->sections[i];
        if (strcmp(section->name, name) == 0) {
            if (section->type != type || section->flags != flags ||
                section->alignment != alignment) {
                return 0;
            }
            table->current = i + 1;
            return (unsigned)table->current;
        }
    }
    if (table->count >= BJ_MAX_SECTIONS) {
        return 0;
    }
    section = &table->sections[table->count];
    memset(section, 0, sizeof(*section));
    memcpy(section->name, name, strlen(name) + 1);
    section->type = type;
    section->flags = flags;
    section->alignment = alignment;
    table->current = ++table->count;
    return (unsigned)table->current;
}

static int bj_section_emit(BjSections *table, const void *source, size_t count)
{
    BjSection *section;
    uint32_t capacity;
    unsigned char *new_bytes;

    if (!table->current || table->current > table->count ||
        count > UINT32_MAX) {
        return 0;
    }
    section = &table->sections[table->current - 1];
    if (count > UINT32_MAX - section->size) {
        return 0;
    }
    if (section->type == BJ_SECTION_NOBITS) {
        if (source != NULL) {
            return 0; /* Initialized bytes cannot be stored in BSS. */
        }
        section->size += (uint32_t)count;
        return 1;
    }
    if (count && !source) {
        return 0;
    }
    if (section->size + count > section->capacity) {
        capacity = section->capacity ? section->capacity : 64;
        while (capacity < section->size + count) {
            if (capacity > UINT32_MAX / 2) {
                capacity = section->size + (uint32_t)count;
                break;
            }
            capacity *= 2;
        }
        new_bytes = realloc(section->bytes, capacity);
        if (!new_bytes) {
            return 0;
        }
        section->bytes = new_bytes;
        section->capacity = capacity;
    }
    if (count) {
        memcpy(section->bytes + section->size, source, count);
    }
    section->size += (uint32_t)count;
    return 1;
}

#endif

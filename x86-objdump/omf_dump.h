/* Intel OMF record inspection: bounded parsing and checksum validation. */
#ifndef X86_OMF_DUMP_H
#define X86_OMF_DUMP_H
static const char *omf_record_name(unsigned type)
{
    switch (type) {
    case 0x80: return "THEADR";
    case 0x88: return "COMENT";
    case 0x8a: return "MODEND";
    case 0x8c: return "EXTDEF";
    case 0x90: return "PUBDEF";
    case 0x96: return "LNAMES";
    case 0x98: return "SEGDEF";
    case 0x9a: return "GRPDEF";
    case 0x9c: return "FIXUPP";
    case 0xa0: return "LEDATA";
    case 0xa2: return "LIDATA";
    case 0xb0: return "COMDEF";
    case 0xb2: return "BAKPAT";
    case 0xb4: return "LEXTDEF";
    case 0xb6: return "LPUBDEF";
    case 0xc2: return "COMDAT";
    default: return "OTHER";
    }
}
static int dump_omf(const char *path, const unsigned char *data, size_t size)
{
    size_t pos = 0;
    unsigned records = 0;
    printf("%s: Intel OMF object (%u bytes)\n", path, (unsigned)size);
    while (pos < size) {
        unsigned type, length, sum = 0;
        size_t end;
        if (size - pos < 3) goto malformed;
        type = data[pos];
        length = (unsigned)data[pos + 1] | ((unsigned)data[pos + 2] << 8);
        if (length == 0 || length > size - pos - 3) goto malformed;
        end = pos + 3 + length;
        for (size_t i = pos; i < end; i++) sum += data[i];
        if ((sum & 255u) != 0) {
            fprintf(stderr, "x86-objdump: OMF checksum error at offset 0x%lx\n", (unsigned long)pos);
            return 1;
        }
        printf("  %06lx  %-8s (0x%02x) payload=%u\n", (unsigned long)pos,
               omf_record_name(type), type, length - 1);
        pos = end;
        records++;
    }
    printf("  %u OMF records verified\n", records);
    return 0;
malformed:
    fprintf(stderr, "x86-objdump: malformed OMF object at offset 0x%lx\n", (unsigned long)pos);
    return 1;
}
#endif

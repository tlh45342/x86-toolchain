/* Minimal Intel OMF86 writer. The first milestone intentionally rejects fixups. */
#ifndef X86_AS_OMF_WRITER_H
#define X86_AS_OMF_WRITER_H
static int omf_record(FILE *f, unsigned type, const unsigned char *payload, size_t size)
{
    unsigned sum = type + (unsigned)((size + 1) & 255) + (unsigned)((size + 1) >> 8);
    if (size > 65534 || fputc(type, f) == EOF ||
        fputc((size + 1) & 255, f) == EOF || fputc((size + 1) >> 8, f) == EOF)
        return 0;
    for (size_t i = 0; i < size; i++) {
        if (fputc(payload[i], f) == EOF) return 0;
        sum += payload[i];
    }
    return fputc((-sum) & 255, f) != EOF;
}
static int omf_name(unsigned char *p, size_t *n, const char *name)
{
    size_t len = strlen(name);
    if (len > 255 || *n + len + 1 > 1024) return 0;
    p[(*n)++] = (unsigned char)len;
    memcpy(p + *n, name, len);
    *n += len;
    return 1;
}
static int write_omf(Asm *a, const char *rawpath, const char *outpath)
{
    FILE *in = NULL, *out = NULL;
    unsigned char buf[1024];
    size_t n;
    long size = 0;
    int ok = 1;
    if (a->nrelocs) {
        fprintf(stderr, "x86-as: OMF fixups not implemented; refusing object with %d relocations\n", a->nrelocs);
        return 0;
    }
    if (a->org || a->pc > 65535 || a->sections.count > 0) {
        fprintf(stderr, "x86-as: initial OMF backend requires a single <=64K segment without ORG or SECTION\n");
        return 0;
    }
    in = fopen(rawpath, "rb");
    if (!in) return 0;
    if (fseek(in, 0, SEEK_END) || (size = ftell(in)) < 0 || fseek(in, 0, SEEK_SET)) ok = 0;
    if (ok && (unsigned long)size > 65535ul) ok = 0;
    if (ok) out = fopen(outpath, "wb");
    if (!out) ok = 0;
    n = 0;
    if (ok && (!omf_name(buf, &n, "x86-as") || !omf_record(out, 0x80, buf, n))) ok = 0;
    n = 0;
    if (ok && (!omf_name(buf, &n, "") || !omf_name(buf, &n, "_TEXT") ||
        !omf_name(buf, &n, "CODE") || !omf_record(out, 0x96, buf, n))) ok = 0;
    /* 16-bit, paragraph alignment, public combine; segment and class indices 2,3. */
    { const unsigned char seg[] = {0x68, (unsigned char)size, (unsigned char)(size >> 8), 2, 3, 1};
      if (ok && !omf_record(out, 0x98, seg, sizeof(seg))) ok = 0; }
    for (int i = 0; ok && i < a->nglobals; i++) {
        uint32_t value = 0;
        if (!sym_find(a, a->globals[i], &value) || value > 65535) {
            fprintf(stderr, "x86-as: OMF external '%s' requires EXTDEF/FIXUPP support\n", a->globals[i]);
            ok = 0;
            break;
        }
        n = 0;
        buf[n++] = 0; buf[n++] = 1; /* no base group, segment 1 */
        if (!omf_name(buf, &n, a->globals[i])) { ok = 0; break; }
        buf[n++] = (unsigned char)value; buf[n++] = (unsigned char)(value >> 8);
        buf[n++] = 0; /* type index */
        if (!omf_record(out, 0x90, buf, n)) ok = 0;
    }
    for (long off = 0; ok && off < size; ) {
        size_t count = (size_t)(size - off);
        if (count > 1000) count = 1000;
        buf[0] = 1; buf[1] = (unsigned char)off; buf[2] = (unsigned char)(off >> 8);
        if (fread(buf + 3, 1, count, in) != count ||
            !omf_record(out, 0xa0, buf, count + 3)) ok = 0;
        off += (long)count;
    }
    { const unsigned char end[] = {0};
      if (ok && !omf_record(out, 0x8a, end, sizeof(end))) ok = 0; }
    if (out && fclose(out)) ok = 0;
    fclose(in);
    if (!ok) remove(outpath);
    return ok;
}
#endif

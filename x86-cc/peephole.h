/* 8086 assembly peephole scanner: fail-closed lexical and flag analysis. */
#ifndef X86CC_PEEPHOLE_H
#define X86CC_PEEPHOLE_H
#include <ctype.h>
/* Read-only scan of one assembler line, ignoring trailing whitespace. */
static void ph_trim(const char *src, char *dst, size_t cap) {
    size_t n = 0;
    while (*src && isspace((unsigned char)*src)) src++;
    while (*src && *src != ';' && n + 1 < cap) dst[n++] = *src++;
    while (n && isspace((unsigned char)dst[n-1])) n--;
    dst[n] = 0;
}
static int ph_starts(const char *s, const char *prefix) {
    size_t n = strlen(prefix);
    return strncmp(s, prefix, n) == 0 && (s[n] == 0 || isspace((unsigned char)s[n]));
}
static int ph_barrier(const char *s) {
    size_t n = strlen(s);
    if (!n) return 0;
    if (s[n-1] == ':' || s[0] == '.' || s[0] == '%' || s[0] == '[') return 1;
    if (ph_starts(s,"call") || ph_starts(s,"ret") || ph_starts(s,"jmp") ||
        ph_starts(s,"int") || ph_starts(s,"hlt") || ph_starts(s,"iret") ||
        ph_starts(s,"popf") || ph_starts(s,"sahf") || ph_starts(s,"db") ||
        ph_starts(s,"dw") || ph_starts(s,"org") || ph_starts(s,"bits") ||
        ph_starts(s,"cpu") || ph_starts(s,"section") || ph_starts(s,"global") ||
        ph_starts(s,"extern") || ph_starts(s,"asm")) return 1;
    if (s[0] == 'j' || ph_starts(s,"loop") || ph_starts(s,"adc") ||
        ph_starts(s,"sbb") || ph_starts(s,"rcl") || ph_starts(s,"rcr") ||
        ph_starts(s,"pushf") || ph_starts(s,"lahf") || ph_starts(s,"into"))
        return 1;
    return 0;
}
static int ph_flag_writer(const char *s) {
    static const char *const ops[] = {"cmp","test","add","sub","and","or","xor",NULL};
    int i;
    for (i=0; ops[i]; i++) if (ph_starts(s,ops[i])) return 1;
    return 0;
}
static int ph_flag_neutral(const char *s) {
    return ph_starts(s,"mov") || ph_starts(s,"push") ||
           ph_starts(s,"pop") || ph_starts(s,"lea") ||
           ph_starts(s,"xchg") || ph_starts(s,"nop");
}
/* Only prove dead flags along a straight-line, fully classified path. */
static int ph_flags_dead(char **lines, size_t count, size_t start) {
    size_t i;
    char s[512];
    for (i=start; i<count; i++) {
        ph_trim(lines[i],s,sizeof(s));
        if (!s[0]) continue;
        if (ph_barrier(s)) return 0;
        if (ph_flag_writer(s)) return 1;
        if (!ph_flag_neutral(s)) return 0;
    }
    return 0;
}
static int ph_dead_ax_address(char **lines, size_t count, size_t i) {
    char a[512], b[512], c[512];
    int disp, slot;
    char tail;
    if (i+2 >= count) return 0;
    ph_trim(lines[i],a,sizeof(a));
    ph_trim(lines[i+1],b,sizeof(b));
    ph_trim(lines[i+2],c,sizeof(c));
    if (strcmp(a,"mov ax, bp")) return 0;
    if (sscanf(b,"sub ax, %d %c",&disp,&tail)!=1 &&
        sscanf(b,"add ax, %d %c",&disp,&tail)!=1) return 0;
    if (disp < 0 || disp > 65535) return 0;
    /* Restrict overwrite to exact BP-relative loads or immediates. */
    if (sscanf(c,"mov ax, [bp-%d] %c",&slot,&tail)!=1 &&
        sscanf(c,"mov ax, [bp+%d] %c",&slot,&tail)!=1 &&
        sscanf(c,"mov ax, %d %c",&slot,&tail)!=1) return 0;
    return ph_flags_dead(lines,count,i+3);
}
static int ph_self_move(const char *line) {
    char s[512], lhs[40], rhs[40], extra;
    static const char *const regs[] = {
        "ax","bx","cx","dx","si","di","bp","sp",
        "al","ah","bl","bh","cl","ch","dl","dh",NULL
    };
    int i;
    ph_trim(line,s,sizeof(s));
    if (sscanf(s,"mov %39[a-z], %39[a-z] %c",lhs,rhs,&extra)!=2) return 0;
    if (strcmp(lhs,rhs)) return 0;
    for (i=0;regs[i];i++) if (!strcmp(lhs,regs[i])) return 1;
    return 0;
}
static int peephole_optimize_file(const char *path, int level) {
    FILE *in=NULL, *out=NULL;
    char tmp[1200], buf[4096];
    char **lines=NULL;
    size_t count=0,cap=0,i,j;
    int ok=0;
    if (!level) return 1;
    in=fopen(path,"rb");
    if (!in) return 0;
    while (fgets(buf,sizeof(buf),in)) {
        char *copy;
        size_t n=strlen(buf);
        if (!n || (buf[n-1]!='\n' && !feof(in))) goto cleanup;
        if (count==cap) {
            size_t newcap=cap ? cap*2 : 256;
            char **p=realloc(lines,newcap*sizeof(*lines));
            if (!p) goto cleanup;
            lines=p;cap=newcap;
        }
        copy=malloc(n+1);
        if (!copy) goto cleanup;
        memcpy(copy,buf,n+1);
        lines[count++]=copy;
    }
    if (ferror(in)) goto cleanup;
    fclose(in);in=NULL;
    if (strlen(path)+8>=sizeof(tmp)) goto cleanup;
    snprintf(tmp,sizeof(tmp),"%s.peetmp",path);
    out=fopen(tmp,"wb");
    if (!out) goto cleanup;
    for (i=0;i<count;i++) {
        if (ph_dead_ax_address(lines,count,i)) { i+=2; }
        else if (ph_self_move(lines[i])) continue;
        if (fputs(lines[i],out)==EOF) goto cleanup;
    }
    if (fclose(out)!=0) {out=NULL;goto cleanup;}
    out=NULL;
    /* On Windows rename cannot replace an existing file. */
    if (remove(path)!=0 || rename(tmp,path)!=0) goto cleanup;
    ok=1;
cleanup:
    if (out) fclose(out);
    if (in) fclose(in);
    if (!ok && strlen(path)+8<sizeof(tmp)) {
        snprintf(tmp,sizeof(tmp),"%s.peetmp",path);
        remove(tmp);
    }
    for (j=0;j<count;j++) free(lines[j]);
    free(lines);
    return ok;
}
#endif

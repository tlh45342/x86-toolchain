/* x86-disk.c - tiny PC floppy image helper for x86 bring-up. */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#define X86_DISK_VERSION "0.0.2"
#define FLOPPY_144_SIZE 1474560UL
#define SECTOR_SIZE 512UL

static void usage(const char *argv0)
{
    fprintf(stderr,
        "x86-disk %s\n"
        "usage:\n"
        "  %s create    <image> <size>\n"
        "  %s format    <image>\n"
        "  %s makeboot  <image> <boot.bin>\n"
        "  %s putsector <image> <lba> <file>\n"
        "  %s dump      <image> <lba>\n"
        "  %s info      <image>\n"
        "\n"
        "sizes: 1.44M, 1440K, or an exact byte count\n",
        X86_DISK_VERSION,
        argv0, argv0, argv0, argv0, argv0, argv0);
}

static int parse_size(const char *s, unsigned long *out)
{
    char *end = NULL;
    double v;
    double mult = 1.0;

    if (!s || !*s || !out) return 0;

    if (strcmp(s, "1.44M") == 0 || strcmp(s, "1.44m") == 0 ||
        strcmp(s, "1440K") == 0 || strcmp(s, "1440k") == 0) {
        *out = FLOPPY_144_SIZE;
        return 1;
    }

    v = strtod(s, &end);
    if (end == s) return 0;

    if (*end) {
        if (end[1] != '\0') return 0;
        switch (tolower((unsigned char)*end)) {
        case 'k': mult = 1024.0; break;
        case 'm': mult = 1024.0 * 1024.0; break;
        default: return 0;
        }
    }

    v *= mult;
    if (v < 512.0 || v > 4294967295.0) return 0;
    *out = (unsigned long)v;
    return 1;
}

static int parse_lba(const char *s, unsigned long *out)
{
    char *end = NULL;
    unsigned long v;
    if (!s || !*s || !out) return 0;
    v = strtoul(s, &end, 0);
    if (end == s || *end != '\0') return 0;
    *out = v;
    return 1;
}

static int zero_bytes(FILE *fp, unsigned long count)
{
    unsigned char zero[4096] = {0};
    while (count) {
        size_t n = count > sizeof(zero) ? sizeof(zero) : (size_t)count;
        if (fwrite(zero, 1, n, fp) != n) return 0;
        count -= (unsigned long)n;
    }
    return 1;
}

static long file_size(FILE *fp)
{
    long n;
    if (fseek(fp, 0, SEEK_END) != 0) return -1;
    n = ftell(fp);
    if (n < 0) return -1;
    if (fseek(fp, 0, SEEK_SET) != 0) return -1;
    return n;
}

static int cmd_create(const char *path, const char *size_text)
{
    unsigned long size;
    FILE *fp;

    if (!parse_size(size_text, &size)) {
        fprintf(stderr, "x86-disk: bad size: %s\n", size_text);
        return 1;
    }

    fp = fopen(path, "wb");
    if (!fp) { perror(path); return 1; }
    if (!zero_bytes(fp, size)) {
        fprintf(stderr, "x86-disk: write failed\n");
        fclose(fp);
        return 1;
    }
    fclose(fp);
    printf("created %s (%lu bytes, %lu sectors)\n",
           path, size, size / SECTOR_SIZE);
    return 0;
}

static int cmd_format(const char *path)
{
    FILE *fp = fopen(path, "r+b");
    long size;
    if (!fp) { perror(path); return 1; }
    size = file_size(fp);
    if (size < 0) { fclose(fp); return 1; }
    if (!zero_bytes(fp, (unsigned long)size)) {
        fprintf(stderr, "x86-disk: format failed\n");
        fclose(fp);
        return 1;
    }
    fclose(fp);
    printf("formatted %s (%ld bytes; raw zeroed image)\n", path, size);
    return 0;
}

static int write_sector(const char *image, unsigned long lba,
                        const unsigned char sector[SECTOR_SIZE])
{
    FILE *ifp;
    long isize;
    unsigned long offset;

    ifp = fopen(image, "r+b");
    if (!ifp) { perror(image); return 1; }
    isize = file_size(ifp);
    if (isize < 0) { fclose(ifp); return 1; }

    if (lba > (~0UL / SECTOR_SIZE)) {
        fprintf(stderr, "x86-disk: LBA too large\n");
        fclose(ifp);
        return 1;
    }
    offset = lba * SECTOR_SIZE;
    if (offset > (unsigned long)isize ||
        SECTOR_SIZE > (unsigned long)isize - offset) {
        fprintf(stderr, "x86-disk: LBA %lu is outside image (%ld bytes)\n",
                lba, isize);
        fclose(ifp);
        return 1;
    }
    if (fseek(ifp, (long)offset, SEEK_SET) != 0 ||
        fwrite(sector, 1, SECTOR_SIZE, ifp) != SECTOR_SIZE) {
        fprintf(stderr, "x86-disk: sector write failed\n");
        fclose(ifp);
        return 1;
    }
    fclose(ifp);
    return 0;
}

static int cmd_makeboot(const char *image, const char *boot)
{
    unsigned char sector[SECTOR_SIZE];
    FILE *bf = fopen(boot, "rb");
    long bsize;

    if (!bf) { perror(boot); return 1; }
    bsize = file_size(bf);
    if (bsize != (long)SECTOR_SIZE) {
        fprintf(stderr, "x86-disk: %s must be exactly 512 bytes (is %ld)\n",
                boot, bsize);
        fclose(bf);
        return 1;
    }
    if (fread(sector, 1, sizeof(sector), bf) != sizeof(sector)) {
        fprintf(stderr, "x86-disk: could not read boot sector\n");
        fclose(bf);
        return 1;
    }
    fclose(bf);

    if (sector[510] != 0x55 || sector[511] != 0xAA) {
        fprintf(stderr, "x86-disk: boot sector missing 55 AA signature\n");
        return 1;
    }

    if (write_sector(image, 0, sector) != 0) return 1;
    printf("installed %s as boot sector of %s\n", boot, image);
    return 0;
}

static int cmd_putsector(const char *image, const char *lba_text, const char *path)
{
    unsigned char sector[SECTOR_SIZE] = {0};
    unsigned long lba;
    FILE *fp;
    long size;

    if (!parse_lba(lba_text, &lba)) {
        fprintf(stderr, "x86-disk: bad LBA: %s\n", lba_text);
        return 1;
    }

    fp = fopen(path, "rb");
    if (!fp) { perror(path); return 1; }
    size = file_size(fp);
    if (size < 0 || size > (long)SECTOR_SIZE) {
        fprintf(stderr, "x86-disk: %s must be <= 512 bytes (is %ld)\n",
                path, size);
        fclose(fp);
        return 1;
    }
    if (size > 0 && fread(sector, 1, (size_t)size, fp) != (size_t)size) {
        fprintf(stderr, "x86-disk: could not read %s\n", path);
        fclose(fp);
        return 1;
    }
    fclose(fp);

    if (write_sector(image, lba, sector) != 0) return 1;
    printf("installed %s at LBA %lu of %s (%ld bytes, zero-padded)\n",
           path, lba, image, size);
    return 0;
}

static int cmd_dump(const char *image, const char *lba_text)
{
    unsigned char sector[SECTOR_SIZE];
    unsigned long lba, offset;
    FILE *fp;
    long isize;

    if (!parse_lba(lba_text, &lba)) {
        fprintf(stderr, "x86-disk: bad LBA: %s\n", lba_text);
        return 1;
    }
    fp = fopen(image, "rb");
    if (!fp) { perror(image); return 1; }
    isize = file_size(fp);
    if (isize < 0) { fclose(fp); return 1; }
    if (lba > (~0UL / SECTOR_SIZE)) { fclose(fp); return 1; }
    offset = lba * SECTOR_SIZE;
    if (offset > (unsigned long)isize ||
        SECTOR_SIZE > (unsigned long)isize - offset) {
        fprintf(stderr, "x86-disk: LBA %lu is outside image\n", lba);
        fclose(fp);
        return 1;
    }
    if (fseek(fp, (long)offset, SEEK_SET) != 0 ||
        fread(sector, 1, SECTOR_SIZE, fp) != SECTOR_SIZE) {
        fprintf(stderr, "x86-disk: sector read failed\n");
        fclose(fp);
        return 1;
    }
    fclose(fp);

    for (unsigned i = 0; i < SECTOR_SIZE; i += 16) {
        printf("%08lX: ", offset + i);
        for (unsigned j = 0; j < 16; ++j)
            printf("%02X%c", sector[i+j], j == 7 ? ' ' : ' ');
        printf(" | ");
        for (unsigned j = 0; j < 16; ++j) {
            unsigned char c = sector[i+j];
            putchar((c >= 32 && c <= 126) ? c : '.');
        }
        printf("\n");
    }
    return 0;
}

static int cmd_info(const char *path)
{
    unsigned char sig[2] = {0,0};
    FILE *fp = fopen(path, "rb");
    long size;
    if (!fp) { perror(path); return 1; }
    size = file_size(fp);
    if (size >= 512 && fseek(fp, 510, SEEK_SET) == 0)
        (void)fread(sig, 1, 2, fp);
    fclose(fp);
    printf("image      : %s\n", path);
    printf("bytes      : %ld\n", size);
    printf("sectors    : %ld\n", size >= 0 ? size / 512 : 0);
    printf("boot sig   : %02X %02X%s\n", sig[0], sig[1],
           (sig[0] == 0x55 && sig[1] == 0xAA) ? " (bootable)" : "");
    return size < 0 ? 1 : 0;
}

int main(int argc, char **argv)
{
    if (argc < 2) { usage(argv[0]); return 1; }
    if (strcmp(argv[1], "create") == 0 && argc == 4)
        return cmd_create(argv[2], argv[3]);
    if (strcmp(argv[1], "format") == 0 && argc == 3)
        return cmd_format(argv[2]);
    if (strcmp(argv[1], "makeboot") == 0 && argc == 4)
        return cmd_makeboot(argv[2], argv[3]);
    if (strcmp(argv[1], "putsector") == 0 && argc == 5)
        return cmd_putsector(argv[2], argv[3], argv[4]);
    if (strcmp(argv[1], "dump") == 0 && argc == 4)
        return cmd_dump(argv[2], argv[3]);
    if (strcmp(argv[1], "info") == 0 && argc == 3)
        return cmd_info(argv[2]);
    usage(argv[0]);
    return 1;
}

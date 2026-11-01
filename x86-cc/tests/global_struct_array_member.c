#include <stdint.h>
struct item { uint16_t type; uint16_t references; uint16_t flags; uint16_t inode; uint32_t offset; uint16_t object_id; };
enum file_type { FILE_FREE = 0, FILE_REGULAR = 1 };
extern struct item items[64];
struct item items[64];
void initialize(void)
{
    uint16_t i;
    for (i = 0; i < 64; ++i) {
        items[i].type = FILE_FREE;
        items[i].references = 0;
        items[i].flags = 0;
        items[i].inode = 0;
        items[i].offset = 0;
        items[i].object_id = 0;
    }
}

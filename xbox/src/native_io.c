/* Real libc-backed file and heap operations; no SDK or game headers. */
#include "native_backend.h"
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <malloc.h>
int ac_native_read(const char *path, unsigned long offset, void *dst, unsigned long bytes) {
    FILE *file;
    size_t count;
    int failed;
    if (!path || (!dst && bytes) || bytes > INT_MAX || offset > LONG_MAX) return -1;
    /* Device/filesystem registration is the launcher's responsibility. A GC
     * disc image is not an ISO9660 volume. No implicit mount or fake DVD. */
    file = fopen(path, "rb");
    if (!file) return -1;
    if (fseek(file, (long)offset, SEEK_SET)) { fclose(file); return -1; }
    count = fread(dst, 1, bytes, file);
    failed = ferror(file);
    if (fclose(file)) failed = 1;
    return failed ? -1 : (int)count;
}

void *ac_native_alloc(unsigned long bytes, unsigned long alignment) {
    if (!bytes || alignment < sizeof(void *) || (alignment & (alignment - 1))) return NULL;
    return memalign(alignment, bytes);
}
void ac_native_free(void *pointer) { free(pointer); }


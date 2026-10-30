#ifndef AC_FAT32_READ_H
#define AC_FAT32_READ_H
#include <stddef.h>
#include <stdint.h>
typedef int (*ACSectorRead)(void *,uint32_t,unsigned char *);
/* Native metadata, not an on-disk structure. Source/media must stay unchanged
 * until close. Calls are serialized by the caller. Zero-initialize before open. */
typedef struct {
    ACSectorRead read;void *user;
    uint32_t base,total,fat,data,clusters,root;unsigned int spc;
} ACFat32Volume;
typedef struct {
    ACFat32Volume volume;uint32_t size,count;uint32_t *chain;
} ACFat32File;
/* Open builds an exact allocation-chain index, capped at 16 MiB. No file payload
 * is preloaded. Rejects early EOC, cycles and surplus preallocated clusters.
 * Read-at is exact, bounded by EOF; an I/O error may leave a valid prefix. */
int ac_fat32_open(ACSectorRead,void *,const unsigned char name[11],ACFat32File *);
int ac_fat32_read_at(ACFat32File *,uint32_t,void *,size_t);
void ac_fat32_close(ACFat32File *);
/* Read-only 512-byte-sector FAT32: superfloppy or primary MBR FAT32 partition,
 * one root-directory 8.3 file. No writes, LFN, subdirectories, GPT or exFAT. */
int ac_fat32_read(ACSectorRead,void *,const unsigned char name[11],
                  unsigned char *,size_t,size_t *);
#endif

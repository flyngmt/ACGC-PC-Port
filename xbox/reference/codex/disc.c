#include "disc.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

static FILE* image;
static ACDiscReader reader;
static void *reader_user;
static unsigned char* fst;
static unsigned char identity[32];
static uint32_t entries, fst_bytes;
static unsigned long image_bytes;
static uint32_t be32(const unsigned char* p) {
    return (uint32_t)p[0]<<24 | (uint32_t)p[1]<<16 | (uint32_t)p[2]<<8 | p[3];
}
static uint32_t field(uint32_t i, uint32_t offset) { return be32(fst+i*12+offset); }
static int isdir(uint32_t i) { return (field(i,0)>>24)==1; }
static const char* name(uint32_t i) { return (char*)fst+entries*12+(field(i,0)&0xffffff); }
static int exact(unsigned long position, void* dst, unsigned long size) {
    if(position>image_bytes||size>image_bytes-position)return 0;
    if(reader)return reader(reader_user,position,dst,size)==0;
    return fseek(image,(long)position,SEEK_SET)==0 && fread(dst,1,size,image)==size;
}
void ac_disc_unmount(void) {
    if (image) fclose(image);
    free(fst); fst=0; image=0; entries=fst_bytes=0; image_bytes=0;
    reader=0;reader_user=0;
    memset(identity,0,sizeof(identity));
}
static int parse_image(void) {
    unsigned char header[0x430];
    uint32_t start, size, i;
    if (image_bytes<sizeof(header) || !exact(0,header,sizeof(header)) || be32(header+0x1c)!=0xc2339f3d) goto fail;
    start=be32(header+0x424); size=be32(header+0x428);
    if (size<12 || size>16*1024*1024 || (uint64_t)start+size>image_bytes) goto fail;
    fst=malloc(size); if (!fst || !exact(start,fst,size)) goto fail;
    entries=be32(fst+8); fst_bytes=size;
    if (!entries || entries>size/12 || !isdir(0) || field(0,4)!=0) goto fail;
    for (i=0;i<entries;++i) {
        uint32_t flags=field(i,0), off=flags&0xffffff;
        if ((flags>>24)>1 || off>=size-entries*12 ||
            !memchr(fst+entries*12+off,0,size-entries*12-off)) goto fail;
        if (isdir(i)) {
            uint32_t parent=field(i,4), next=field(i,8);
            if (next<=i || next>entries || (i && (parent>=i || !isdir(parent) || next>field(parent,8)))) goto fail;
        } else if ((uint64_t)field(i,4)+field(i,8)>image_bytes) goto fail;
    }
    /* Validate tree nesting, not only individual ranges. */
    {
        uint32_t directory=0;
        for (i=1;i<entries;++i) {
            while (directory && i>=field(directory,8)) directory=field(directory,4);
            if (i>=field(directory,8)) goto fail;
            if (isdir(i)) { if (field(i,4)!=directory) goto fail; directory=i; }
        }
    }
    memcpy(identity,header,32);
    return 0;
fail:
    ac_disc_unmount(); return -1;
}
int ac_disc_mount(const char *path) {
    long end;
    ac_disc_unmount();
    if(!path||!(image=fopen(path,"rb")))return -1;
    if(fseek(image,0,SEEK_END)||(end=ftell(image))<0||(unsigned long)end>0x7fffffffUL){ac_disc_unmount();return -1;}
    image_bytes=(unsigned long)end;return parse_image();
}
int ac_disc_mount_reader(ACDiscReader read,void *user,unsigned long size) {
    ac_disc_unmount();
    if(!read||!size||size>0x7fffffffUL)return -1;
    reader=read;reader_user=user;image_bytes=size;return parse_image();
}
int ac_disc_mounted(void) { return (image!=0||reader!=0) && fst!=0; }
int ac_disc_id(unsigned char out[32]) {
    if (!ac_disc_mounted() || !out) return -1;
    memcpy(out,identity,32); return 0;
}
static unsigned char lower(unsigned char c) { return c>='A' && c<='Z' ? c+32 : c; }
int ac_disc_lookup(const char* path, unsigned int directory) {
    if (!ac_disc_mounted() || !path || directory>=entries || !isdir(directory)) return -1;
    if (*path=='/') { directory=0; while (*path=='/') ++path; }
    while (*path) {
        const char* end=path; uint32_t i; size_t length;
        while (*end && *end!='/') ++end;
        length=(size_t)(end-path);
        if (length==1 && path[0]=='.') { /* current directory */ }
        else if (length==2 && path[0]=='.' && path[1]=='.') directory=field(directory,4);
        else {
            for (i=directory+1;i<field(directory,8);i=isdir(i)?field(i,8):i+1) {
                const char* candidate=name(i); size_t n;
                for (n=0;n<length && candidate[n] && lower((unsigned char)path[n])==lower((unsigned char)candidate[n]);++n) {}
                if (n==length && !candidate[n]) break;
            }
            if (i>=field(directory,8)) return -1;
            if (!*end) return (int)i;
            if (!isdir(i)) return -1;
            directory=i;
        }
        path=end; while (*path=='/') ++path;
    }
    return (int)directory;
}
int ac_disc_entry(unsigned int i, unsigned long* position, unsigned long* length, int* directory) {
    if (!ac_disc_mounted() || i>=entries || !position || !length || !directory) return -1;
    *directory=isdir(i); *position=field(i,4); *length=field(i,8); return 0;
}
int ac_disc_read(unsigned long position, void* dst, unsigned long length) {
    if (!ac_disc_mounted() || (!dst && length) || length>INT_MAX || (uint64_t)position+length>image_bytes) return -1;
    return exact(position,dst,length) ? (int)length : -1;
}
unsigned int ac_disc_count(void) { return ac_disc_mounted() ? entries : 0; }

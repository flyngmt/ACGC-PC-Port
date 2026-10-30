#include "fat32_read.h"
#include <stdlib.h>
#include <string.h>
static uint32_t le16(const unsigned char *p){return p[0]|((uint32_t)p[1]<<8);}
static uint32_t le32(const unsigned char *p){return le16(p)|(le16(p+2)<<16);}
typedef ACFat32Volume Volume;
static int sector(Volume *v,uint32_t relative,unsigned char *b){
    if(relative>=v->total||relative>UINT32_MAX-v->base)return -1;
    return v->read(v->user,v->base+relative,b);
}
static int next(Volume *v,uint32_t cluster,uint32_t *result,unsigned char *b){
    if(cluster<2||cluster>=v->clusters+2||sector(v,v->fat+cluster/128,b))return -1;
    *result=le32(b+(cluster%128)*4)&0x0fffffff;return 0;
}
static int cluster_sector(Volume *v,uint32_t cluster,unsigned int i,unsigned char *b){
    if(cluster<2||cluster>=v->clusters+2||i>=v->spc)return -1;
    return sector(v,v->data+(cluster-2)*v->spc+i,b);
}
int ac_fat32_open(ACSectorRead read,void *user,const unsigned char name[11],ACFat32File *file){
    unsigned char b[512];Volume v={0};uint32_t partition_limit=UINT32_MAX;
    uint32_t fatsz,reserved,fats,flags,cluster,file_cluster=0,file_size=0;unsigned int i;
    if(!read||!name||!file||file->chain||file->volume.read)return -1;
    v.read=read;v.user=user;
    if(read(user,0,b)||b[510]!=0x55||b[511]!=0xaa)return -2;
    if(le16(b+11)!=512||le16(b+22)!=0||!le32(b+36)){
        int found=0;
        for(i=0;i<4;++i){const unsigned char *p=b+446+i*16;
            if(p[4]==0x0b||p[4]==0x0c){v.base=le32(p+8);partition_limit=le32(p+12);found=1;break;}}
        if(!found||!v.base||!partition_limit||read(user,v.base,b))return -2;
    }
    if(b[510]!=0x55||b[511]!=0xaa||le16(b+11)!=512||le16(b+17)||le16(b+22)||le16(b+42))return -2;
    v.spc=b[13];reserved=le16(b+14);fats=b[16];fatsz=le32(b+36);v.total=le32(b+32);
    if(!v.spc||(v.spc&(v.spc-1))||v.spc>128||!reserved||!fats||fats>2||!fatsz||
       v.total>partition_limit||v.total>UINT32_MAX-v.base||fatsz>(UINT32_MAX-reserved)/fats)return -2;
    v.data=reserved+fats*fatsz;
    if(v.data>=v.total)return -2;
    v.clusters=(v.total-v.data)/v.spc;
    if(v.clusters<65525||v.clusters>=0x0ffffff5||fatsz<(v.clusters+2+127)/128)return -2;
    flags=le16(b+40);v.fat=reserved;
    if(flags&128){if((flags&15)>=fats)return -2;v.fat+=(flags&15)*fatsz;}
    v.root=le32(b+44)&0x0fffffff;cluster=v.root;
    /* Bounded traversal prevents corrupt/cyclic media from looping forever. */
    for(unsigned int hops=0;hops<4096;++hops){
        for(i=0;i<v.spc;++i){
            if(cluster_sector(&v,cluster,i,b))return -3;
            for(unsigned int p=0;p<512;p+=32){
                unsigned int j;const unsigned char *entry=b+p;
                if(!entry[0])return -4;
                if(entry[0]==0xe5||(entry[11]&0x18)||entry[11]==15)continue;
                for(j=0;j<11&&entry[j]==name[j];++j){}
                if(j==11){file_cluster=(le16(entry+20)<<16)|le16(entry+26);file_size=le32(entry+28);goto found;}
            }
        }
        if(next(&v,cluster,&cluster,b))return -3;
        if(cluster>=0x0ffffff8)return -4;
    }
    return -5;
found:;
    /* Bound the index to 16 MiB. A 1.4 GiB image at 512-byte clusters fits.
     * The index contains cluster numbers only, never file payload. */
    uint64_t needed=((uint64_t)file_size+v.spc*512-1)/(v.spc*512);
    if(needed>v.clusters||needed>4194304)return -5;
    uint32_t *chain=needed?malloc((size_t)needed*sizeof(*chain)):0;
    if(needed&&!chain)return -7;
    cluster=file_cluster;
    uint32_t cached=UINT32_MAX;
    for(uint32_t n=0;n<(uint32_t)needed;++n){
        if(cluster<2||cluster>=v.clusters+2)goto bad_chain;
        chain[n]=cluster;
        uint32_t fat_sector=v.fat+cluster/128;
        if(fat_sector!=cached){if(sector(&v,fat_sector,b))goto bad_chain;cached=fat_sector;}
        cluster=le32(b+(cluster%128)*4)&0x0fffffff;
        if(n+1<(uint32_t)needed && cluster>=0x0ffffff8)goto bad_chain;
    }
    /* Exact allocation chain: early EOC, cycles and surplus allocation fail. */
    if(needed&&cluster<0x0ffffff8)goto bad_chain;
    file->volume=v;file->size=file_size;file->count=(uint32_t)needed;file->chain=chain;
    return 0;
bad_chain:
    free(chain);return -5;
}
void ac_fat32_close(ACFat32File *file){
    if(file){free(file->chain);memset(file,0,sizeof(*file));}
}
int ac_fat32_read_at(ACFat32File *file,uint32_t offset,void *out,size_t length){
    unsigned char b[512];unsigned char *destination=out;
    if(!file||!file->volume.read||(!out&&length))return -1;
    if(offset>file->size||length>file->size-offset)return -6;
    for(size_t copied=0;copied<length;){
        uint32_t position=offset+(uint32_t)copied;
        uint32_t cluster_bytes=file->volume.spc*512,index=position/cluster_bytes;
        unsigned int within=position%512,sector_index=(position%cluster_bytes)/512;
        size_t amount=512-within;if(amount>length-copied)amount=length-copied;
        if(index>=file->count||cluster_sector(&file->volume,file->chain[index],sector_index,b))return -3;
        memcpy(destination+copied,b+within,amount);copied+=amount;
    }
    return 0;
}
int ac_fat32_read(ACSectorRead read,void *user,const unsigned char name[11],
                  unsigned char *out,size_t capacity,size_t *size){
    ACFat32File file={0};
    if(!out||!size)return -1;
    int result=ac_fat32_open(read,user,name,&file);
    if(result)return result;
    if(!file.size||file.size>capacity){ac_fat32_close(&file);return -6;}
    result=ac_fat32_read_at(&file,0,out,file.size);
    if(!result)*size=file.size;
    ac_fat32_close(&file);return result;
}

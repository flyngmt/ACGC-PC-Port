#include "gx_texture_xenos.h"
#include "gx_texture_binding_private.h"
#include "gx_texture.h"
#include <xenos/xe.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>
typedef struct {unsigned int fields[13];ACMaterialProgram material;} Key;
typedef struct {Key key;struct XenosSurface *surface;} Cache;
_Static_assert(sizeof(ACMaterialProgram)==16 && sizeof(Key)==68,"deterministic cache key layout");
static struct XenosDevice *device;static Cache cache[32];static unsigned int busy;
static int native_fence(void *user){Xe_Sync(user);return 0;}
static int separate(const void *a,size_t n,const void *b,size_t m){
    uintptr_t x=(uintptr_t)a,y=(uintptr_t)b;
    return n<=UINTPTR_MAX-x&&m<=UINTPTR_MAX-y&&!(x<y+m&&y<x+n);
}
int ac_gx_xenos_setup(struct XenosDevice *xe){
    if(!xe||device||busy||ac_gx_texture_frame_active())return AC_GX_BIND_BUSY;
    int result=ac_gx_texture_set_fence(native_fence,xe);if(result)return result;device=xe;return 0;
}
static int apply(unsigned int stage,const ACGXTextureView *input,unsigned char *workspace,size_t capacity,const ACMaterialProgram *material){
    ACGXTextureView v=*input;int result;
    if(v.min_filter!=v.mag_filter)return AC_GX_BIND_UNSUPPORTED;
    if(!workspace||!material)return AC_GX_BIND_ARGUMENT;
    unsigned char probe[4]={0};if(ac_material_texel(material,probe,probe))return AC_GX_BIND_UNSUPPORTED;
    Key key={{v.image_token,v.image_offset,v.width,v.height,v.format,v.wrap_s,v.wrap_t,v.min_filter,v.mag_filter,
              v.palette_token,v.palette_offset,v.palette_entries,v.palette_format},*material};
    Cache *free_slot=0;
    for(unsigned int i=0;i<32;++i){
        if(cache[i].surface&&memcmp(&cache[i].key,&key,sizeof(key))==0){Xe_SetTexture(device,(int)stage,cache[i].surface);return 0;}
        if(!cache[i].surface&&!free_slot)free_slot=&cache[i];
    }
    if(!free_slot)return AC_GX_BIND_CAPACITY;
    size_t bytes=(size_t)v.width*v.height*4;
    if(!ac_gx_texture_scratch_valid(workspace,bytes))return AC_GX_TEX_OVERLAP;
    result=ac_gx_texture_decode_palette(v.format,v.width,v.height,v.image,v.image_bytes,v.palette,v.palette_bytes,
        v.palette_entries,v.palette_format,workspace,(size_t)v.width*4,capacity);if(result)return result;
    result=ac_material_pixels(&key.material,workspace,v.width,v.height,(size_t)v.width*4,capacity);if(result)return result;
    for(size_t p=0;p<bytes;p+=4){unsigned char t=workspace[p];workspace[p]=workspace[p+2];workspace[p+2]=t;}
    struct XenosSurface *s=Xe_CreateTexture(device,v.width,v.height,1,XE_FMT_8888|XE_FMT_BGRA,0);
    if(!s){return AC_GX_BIND_CAPACITY;}
    if(s->width!=(int)v.width||s->height!=(int)v.height||s->tiled||s->format!=(XE_FMT_8888|XE_FMT_BGRA)||
       s->bypp!=4||s->wpitch<(int)(v.width*4)||s->hpitch<(int)v.height||!s->base||s->wpitch>INT_MAX/s->hpitch){
        Xe_DestroyTexture(device,s);return AC_GX_BIND_RANGE;
    }
    size_t extent=(size_t)s->wpitch*(unsigned int)s->hpitch;
    if(!separate(s->base,extent,workspace,bytes)||!separate(s->base,extent,v.image,v.image_bytes)||
       (v.palette&&!separate(s->base,extent,v.palette,v.palette_bytes))){Xe_DestroyTexture(device,s);return AC_GX_TEX_OVERLAP;}
    unsigned char *pixels=Xe_Surface_LockRect(device,s,0,0,(int)v.width,(int)v.height,XE_LOCK_WRITE);
    if(!pixels){Xe_DestroyTexture(device,s);return AC_GX_BIND_RANGE;}
    memset(pixels,0,extent);for(unsigned int y=0;y<v.height;++y)memcpy(pixels+(size_t)y*(unsigned int)s->wpitch,workspace+(size_t)y*v.width*4,(size_t)v.width*4);
    Xe_Surface_Unlock(device,s);static const int addresses[3]={XE_TEXADDR_CLAMP,XE_TEXADDR_WRAP,XE_TEXADDR_MIRROR};
    s->u_addressing=addresses[v.wrap_s];s->v_addressing=addresses[v.wrap_t];s->use_filtering=(int)v.min_filter;
    free_slot->key=key;free_slot->surface=s;Xe_SetTexture(device,(int)stage,s);return 0;
}
int ac_gx_xenos_apply(unsigned int stage,unsigned char *workspace,size_t capacity,const ACMaterialProgram *material){
    if(!device||busy)return AC_GX_BIND_BUSY;
    ACGXTextureView v;int result=ac_gx_texture_view(stage,&v);if(result)return result;
    result=ac_gx_texture_transaction_begin(1);if(result)return result;
    busy=1;result=apply(stage,&v,workspace,capacity,material);busy=0;
    int ended=ac_gx_texture_transaction_end();return result?result:ended;
}
int ac_gx_xenos_collect(void){
    if(!device||busy||ac_gx_texture_frame_active())return AC_GX_BIND_BUSY;
    int result=ac_gx_texture_transaction_begin(0);if(result)return result;
    busy=1;for(unsigned int stage=0;stage<8;++stage)Xe_SetTexture(device,(int)stage,0);
    for(unsigned int i=0;i<32;++i)if(cache[i].surface){Xe_DestroyTexture(device,cache[i].surface);memset(&cache[i],0,sizeof(cache[i]));}
    busy=0;return ac_gx_texture_transaction_end();
}
int ac_gx_xenos_shutdown(void){
    int result=ac_gx_xenos_collect();if(result)return result;
    result=ac_gx_texture_set_fence(0,0);if(result)return result;device=0;return 0;
}

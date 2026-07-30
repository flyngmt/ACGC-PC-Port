#ifndef _DOLPHIN_GXTEXTURE
#define _DOLPHIN_GXTEXTURE

#include <dolphin/gx/GXEnum.h>
#include <dolphin/gx/GXStruct.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef GXTexRegion* (*GXTexRegionCallback)(const GXTexObj* obj, GXTexMapID id);
typedef GXTlutRegion* (*GXTlutRegionCallback)(u32 idx);

void GXInitTexObj(GXTexObj* obj, void* image_ptr, u16 width, u16 height, GXTexFmt format, GXTexWrapMode wrap_s,
                  GXTexWrapMode wrap_t, u8 mipmap);
void GXInitTexObjCI(GXTexObj* obj, void* image_ptr, u16 width, u16 height, GXCITexFmt format, GXTexWrapMode wrap_s,
                    GXTexWrapMode wrap_t, u8 mipmap, u32 tlut_name);
void GXInitTexObjData(GXTexObj* obj, void* image_ptr);
void GXInitTexObjLOD(GXTexObj* obj, GXTexFilter min_filt, GXTexFilter mag_filt, f32 min_lod, f32 max_lod, f32 lod_bias,
                     GXBool bias_clamp, GXBool do_edge_lod, GXAnisotropy max_aniso);
void GXLoadTexObj(GXTexObj* obj, GXTexMapID id);
u32 GXGetTexBufferSize(u16 width, u16 height, u32 format, GXBool mipmap, u8 max_lod);
void GXInvalidateTexAll();
void GXInitTexObjWrapMode(GXTexObj* obj, GXTexWrapMode s, GXTexWrapMode t);
void GXInitTlutObj(GXTlutObj* tlut_obj, void* lut, GXTlutFmt fmt, u16 n_entries);
void GXLoadTlut(GXTlutObj* obj, u32 idx);
void GXSetTexCoordScaleManually(GXTexCoordID coord, GXBool enable, u16 ss, u16 ts);
void GXInitTexCacheRegion(GXTexRegion* region, GXBool is_32b_mipmap, u32 tmem_even, GXTexCacheSize size_even,
                          u32 tmem_odd, GXTexCacheSize size_odd);
GXTexRegionCallback GXSetTexRegionCallback(GXTexRegionCallback callback);
void GXInvalidateTexRegion(GXTexRegion* region);
void GXInitTlutRegion(GXTlutRegion* region, u32 tmem_addr, GXTlutSize tlut_size);
void GXSetTexCoordBias(GXTexCoordID coord, u8 s_enable, u8 t_enable);
#ifdef __cplusplus
}
#endif

#endif // _DOLPHIN_GXTEXTURE

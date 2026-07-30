#ifndef _DOLPHIN_GXTRANSFORM
#define _DOLPHIN_GXTRANSFORM

#include <dolphin/gx/GXEnum.h>

#ifdef __cplusplus
extern "C" {
#endif

#define GX_PROJECTION_SZ 7

#ifdef TARGET_PC
void GXSetProjection(const void* mtx, GXProjectionType type);
void GXLoadPosMtxImm(const void* mtx, u32 id);
void GXLoadNrmMtxImm(const void* mtx, u32 id);
void GXLoadTexMtxImm(const void* mtx, u32 id, GXTexMtxType type);
#else
void GXSetProjection(f32 mtx[4][4], GXProjectionType type);
void GXLoadPosMtxImm(f32 mtx[3][4], u32 id);
void GXLoadNrmMtxImm(f32 mtx[3][4], u32 id);
void GXLoadTexMtxImm(f32 mtx[][4], u32 id, GXTexMtxType type);
#endif
void GXSetViewport(f32 left, f32 top, f32 wd, f32 ht, f32 nearz, f32 farz);
void GXSetCurrentMtx(u32 id);
void GXSetViewportJitter(f32 left, f32 top, f32 wd, f32 ht, f32 nearz, f32 farz, u32 field);
void GXSetScissorBoxOffset(s32 x_off, s32 y_off);
void GXSetClipMode(GXClipMode mode);

#ifdef __cplusplus
}
#endif

#endif // _DOLPHIN_GXTRANSFORM

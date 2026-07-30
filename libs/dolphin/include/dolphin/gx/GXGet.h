#ifndef _DOLPHIN_GXGET
#define _DOLPHIN_GXGET

#include <dolphin/gx/GXEnum.h>
#include <dolphin/gx/GXStruct.h>

#ifdef __cplusplus
extern "C" {
#endif

GXBool GXGetTexObjMipMap(const GXTexObj* obj);
GXTexFmt GXGetTexObjFmt(const GXTexObj* obj);
u16 GXGetTexObjHeight(const GXTexObj* obj);
u16 GXGetTexObjWidth(const GXTexObj* obj);
GXTexWrapMode GXGetTexObjWrapS(const GXTexObj* obj);
GXTexWrapMode GXGetTexObjWrapT(const GXTexObj* obj);
void* GXGetTexObjData(const GXTexObj* obj);
void GXGetProjectionv(f32* p);
void GXGetLightPos(GXLightObj* lt_obj, f32* x, f32* y, f32* z);
void GXGetLightColor(GXLightObj* lt_obj, GXColor* color);
void GXGetVtxAttrFmt(GXVtxFmt idx, GXAttr attr, GXCompCnt* compCnt, GXCompType* compType,
                     u8* shift);

#ifdef __cplusplus
}
#endif

#endif // _DOLPHIN_GXGET

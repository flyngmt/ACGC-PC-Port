#ifndef _DOLPHIN_GXSTRUCT
#define _DOLPHIN_GXSTRUCT

#include <dolphin/types.h>
#include <dolphin/gx/GXEnum.h>
#include <dolphin/vi.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _GXRenderModeObj {
  VITVMode viTVmode;
  u16 fbWidth;
  u16 efbHeight;
  u16 xfbHeight;
  u16 viXOrigin;
  u16 viYOrigin;
  u16 viWidth;
  u16 viHeight;
  VIXFBMode xFBmode;
  u8 field_rendering;
  u8 aa;
  u8 sample_pattern[12][2];
  u8 vfilter[7];
} GXRenderModeObj;

typedef struct _GXColor {
  u8 r;
  u8 g;
  u8 b;
  u8 a;
} GXColor;

typedef struct _GXTexObj {
#ifdef TARGET_PC
  u32 dummy[22];
#else
  u32 dummy[8];
#endif
} GXTexObj;

typedef struct _GXTlutObj {
#ifdef TARGET_PC
  u32 dummy[4];
#else
  u32 dummy[3];
#endif
} GXTlutObj;

typedef struct _GXLightObj {
  u32 dummy[16];
} GXLightObj;

typedef struct _GXColorS10 {
  s16 r;
  s16 g;
  s16 b;
  s16 a;
} GXColorS10;

typedef struct _GXTexRegion {
  u32 dummy[4];
} GXTexRegion;

typedef struct _GXTlutRegion {
  u32 dummy[4];
} GXTlutRegion;

typedef struct _GXFogAdjTable
{
    u16 r[10];
} GXFogAdjTable;

typedef struct _GXVtxDescList {
    GXAttr attr;
    GXAttrType type;
} GXVtxDescList;

typedef struct _GXVtxAttrFmtList {
    GXAttr attr;
    GXCompCnt cnt;
    GXCompType type;
    u8 frac;
} GXVtxAttrFmtList;

#ifdef __cplusplus
}
#endif

#endif // _DOLPHIN_GXSTRUCT

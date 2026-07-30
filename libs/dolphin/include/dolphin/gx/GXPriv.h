#ifndef _DOLPHIN_GXPRIV
#define _DOLPHIN_GXPRIV

#include "dolphin/gx/GXVert.h"

typedef struct GXLightObj_ {
  u32 padding[3];
  u32 color;
  float a0;
  float a1;
  float a2;
  float k0;
  float k1;
  float k2;
  float px;
  float py;
  float pz;
  float nx;
  float ny;
  float nz;
} GXLightObj_;

#define XF_LIGHT_BASE 0x0600
#define XF_LIGHT_SIZE 0x10

#define GX_FIFO_ADDR 0xCC008000

#define GX_WRITE_U8(v) (GXWGFifo.u8 = v)
#define GX_WRITE_U32(v) (GXWGFifo.u32 = v)

typedef struct GXData {
  u16 cpSRreg;
  u16 cpCRreg;
} GXData;

extern GXData* __GXData;

#endif // _DOLPHIN_GXPRIV

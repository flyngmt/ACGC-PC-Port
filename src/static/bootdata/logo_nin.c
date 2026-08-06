#include "bootdata.h"
#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 nintendo_376x104[0x4C60];
#else
#include "assets/bootdata/nintendo_376x104.inc"
#endif

#ifdef TARGET_PC
Vtx logo_nin_v[0x40 / sizeof(Vtx)];
#else
Vtx logo_nin_v[] = {
  #include "assets/bootdata/logo_nin_v.inc"
};
#endif

Gfx logo_ninT_model[] = {
  gsDPLoadTextureBlock_4b_Dolphin(nintendo_376x104, G_IM_FMT_I, 376, 104, 15, GX_CLAMP, GX_CLAMP, 0, 0),
  gsSPVertex(&logo_nin_v[0], 4, 0),
  gsSPNTrianglesInit_5b(
    2, // tri count
    0, 1, 2, // tri0
    1, 3, 2, // tri1
    0, 0, 0 // tri2
  ),
  gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_static_bootdata_logo_nin_c(void) {
    pc_load_asset("assets/bootdata/logo_nin_v.bin", logo_nin_v, 0x40, 0xC00C0, 1, 2);
    pc_load_asset("assets/bootdata/nintendo_376x104.bin", nintendo_376x104, 0x4C60, 0xBB460, 1, 0);
}
#endif

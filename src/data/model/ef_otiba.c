#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_otiba01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_otiba01_pal[] = {
#include "assets/obj_otiba01_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 ef_otiba_0_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) u8 ef_otiba_0_tex[] = {
#include "assets/ef_otiba_0_tex.inc"
};
#endif

Gfx ef_otiba01_setmode[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 0xFF, 0xFF, 0xFF, 0xFF, 0xC8),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPPipeSync(),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_otiba01_pal),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
    // #include "assets/ef_otiba01_setmode.inc"
};

#ifdef TARGET_PC
Vtx ef_otiba01_00_v[0x50 / sizeof(Vtx)];
#else
Vtx ef_otiba01_00_v[] = {
#include "assets/ef_otiba01_00_v.inc"
};
#endif

Gfx ef_otiba01_00_modelT[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, ef_otiba_0_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(ef_otiba01_00_v, 5, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSP2Triangles(0, 4, 1, 0, 4, 3, 1, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
u8 ef_otiba_1_tex[0x80];
#else
u8 ef_otiba_1_tex[] = {
#include "assets/ef_otiba_1_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx ef_otiba01_01_v[0x50 / sizeof(Vtx)];
#else
Vtx ef_otiba01_01_v[] = {
#include "assets/ef_otiba01_01_v.inc"
};
#endif

Gfx ef_otiba01_01_modelT[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, ef_otiba_1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(ef_otiba01_01_v, 5, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSP2Triangles(0, 4, 1, 0, 4, 3, 1, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
u8 ef_otiba_2_tex[0x80];
#else
u8 ef_otiba_2_tex[] = {
#include "assets/ef_otiba_2_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx ef_otiba01_02_v[0x50 / sizeof(Vtx)];
#else
Vtx ef_otiba01_02_v[] = {
#include "assets/ef_otiba01_02_v.inc"
};
#endif

Gfx ef_otiba01_02_modelT[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, ef_otiba_2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(ef_otiba01_02_v, 5, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSP2Triangles(0, 4, 1, 0, 4, 3, 1, 0),
    gsSPEndDisplayList(),
};

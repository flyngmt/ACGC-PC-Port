#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 ef_kisha_kemuri01_0[0x80];
#else
ATTRIBUTE_ALIGN(32) u8 ef_kisha_kemuri01_0[] = {
#include "assets/ef_kisha_kemuri01_0.inc"
};
#endif

#ifdef TARGET_PC
u8 ef_kisha_kemuri01_1[0x80];
#else
u8 ef_kisha_kemuri01_1[] = {
#include "assets/ef_kisha_kemuri01_1.inc"
};
#endif

#ifdef TARGET_PC
Vtx ef_kisha_kemuri01_00_v[0x40 / sizeof(Vtx)];
#else
Vtx ef_kisha_kemuri01_00_v[] = {
#include "assets/ef_kisha_kemuri01_00_v.inc"
};
#endif

Gfx ef_kisha_kemuri01_modelT[] = {
    gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_CLD_SURF2),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, SHADE, 0, COMBINED, 0, COMBINED, 0,
                       PRIMITIVE, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, ef_kisha_kemuri01_0),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, ef_kisha_kemuri01_1),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(ef_kisha_kemuri01_00_v, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
    gsSPEndDisplayList(),
};

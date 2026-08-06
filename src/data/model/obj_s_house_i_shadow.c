#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_s_house_i_shadow_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) u8 obj_s_house_i_shadow_tex[] = {
#include "assets/obj_s_house_i_shadow_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_house_i_shadow_v[0x1C0 / sizeof(Vtx)];
#else
Vtx obj_s_house_i_shadow_v[] = {
#include "assets/obj_s_house_i_shadow_v.inc"
};
#endif

Gfx obj_s_house_i_shadowT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_s_house_i_shadow_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(anime_1_txt, 28, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPNTrianglesInit_5b(6, 4, 5, 6, 4, 6, 7, 8, 9, 10),
    gsSPNTriangles_5b(8, 10, 11, 12, 13, 14, 12, 14, 15, 0, 0, 0),
    gsSPNTrianglesInit_5b(2, 16, 17, 18, 16, 18, 19, 0, 0, 0),
    gsSPNTrianglesInit_5b(6, 20, 21, 22, 21, 23, 22, 24, 20, 25),
    gsSPNTriangles_5b(20, 22, 25, 26, 24, 25, 26, 27, 24, 0, 0, 0),
    gsSPEndDisplayList(),
};

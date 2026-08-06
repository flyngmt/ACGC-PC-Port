#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_s_douzou_kage_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) u8 obj_s_douzou_kage_txt[] = {
#include "assets/obj_s_douzou_kage_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_douzou_shadow_v[0x80 / sizeof(Vtx)];
#else
Vtx obj_s_douzou_shadow_v[] = {
#include "assets/obj_s_douzou_shadow_v.inc"
};
#endif

Gfx obj_s_douzou_shadow_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_OVL_SURF2),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_8b, 16, 16, obj_s_douzou_kage_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(anime_1_txt, 8, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 1, 3, 2, 4, 1, 0),
    gsSPNTriangles_5b(4, 5, 1, 2, 3, 6, 3, 7, 6, 0, 0, 0),
    gsSPEndDisplayList(),
};

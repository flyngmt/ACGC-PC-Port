#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_myhome_step_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_myhome_step_pal[] = {
#include "assets/obj_myhome_step_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_myhome_step_tex[0x800];
#else
u8 obj_myhome_step_tex[] = {
#include "assets/obj_myhome_step_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_myhome_step_down_v[0x180 / sizeof(Vtx)];
#else
Vtx obj_myhome_step_down_v[] = {
#include "assets/obj_myhome_step_down_v.inc"
};
#endif

Gfx obj_myhome_step_down_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(SHADE, 0, TEXEL0, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_myhome_step_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_myhome_step_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_myhome_step_down_v, 24, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 0, 2, 3, 3, 2, 4),
    gsSPNTriangles_5b(3, 4, 5, 6, 7, 1, 6, 1, 0, 8, 9, 7),
    gsSPNTriangles_5b(8, 7, 6, 10, 11, 9, 10, 9, 8, 12, 13, 11),
    gsSPNTriangles_5b(12, 11, 10, 14, 15, 13, 14, 13, 12, 16, 15, 14),
    gsSPNTriangles_5b(16, 14, 17, 18, 19, 20, 18, 20, 21, 4, 22, 23),
    gsSPNTriangles_5b(4, 23, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

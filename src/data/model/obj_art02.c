#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_art_ang_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_art_ang_pal[] = {
#include "assets/obj_art_ang_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_art_ang_gaku_tex[0x80];
#else
u8 obj_art_ang_gaku_tex[] = {
#include "assets/obj_art_ang_gaku_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_art_ang_art_tex[0x300];
#else
u8 obj_art_ang_art_tex[] = {
#include "assets/obj_art_ang_art_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_art_ang_name_tex[0x80];
#else
u8 obj_art_ang_name_tex[] = {
#include "assets/obj_art_ang_name_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_art02_v[0x1E0 / sizeof(Vtx)];
#else
Vtx obj_art02_v[] = {
#include "assets/obj_art02_v.inc"
};
#endif

Gfx obj_art02_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_art_ang_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_art_ang_name_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_art02_v, 30, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, obj_art_ang_art_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 6, 7, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_art_ang_gaku_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsSPNTrianglesInit_5b(14, 8, 9, 10, 8, 10, 11, 11, 12, 13),
    gsSPNTriangles_5b(11, 13, 8, 14, 15, 16, 14, 16, 17, 18, 19, 20),
    gsSPNTriangles_5b(18, 20, 21, 21, 22, 23, 21, 23, 18, 17, 24, 25),
    gsSPNTriangles_5b(17, 25, 14, 26, 27, 28, 26, 28, 29, 0, 0, 0),
    gsSPEndDisplayList(),
};

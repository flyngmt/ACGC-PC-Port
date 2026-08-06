#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_yos_wheel_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_yos_wheel_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_yos_wheel_pal[] = {
#include "assets/int_yos_wheel_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yos_wheel_nakatyu_tex_txt[0x100];
#else
u8 int_yos_wheel_nakatyu_tex_txt[] = {
#include "assets/int_yos_wheel_nakatyu_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yos_wheel_tyu_tex_txt[0x80];
#else
u8 int_yos_wheel_tyu_tex_txt[] = {
#include "assets/int_yos_wheel_tyu_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yos_wheel_bo_tex_txt[0x100];
#else
u8 int_yos_wheel_bo_tex_txt[] = {
#include "assets/int_yos_wheel_bo_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yos_wheel_sotowa_tex_txt[0x200];
#else
u8 int_yos_wheel_sotowa_tex_txt[] = {
#include "assets/int_yos_wheel_sotowa_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_yos_wheel_v[0x380 / sizeof(Vtx)];
#else
Vtx int_yos_wheel_v[] = {
#include "assets/int_yos_wheel_v.inc"
};
#endif

Gfx int_yos_wheel_obj_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_yos_wheel_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_yos_wheel_nakatyu_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_yos_wheel_v, 25, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 1, 3, 2, 4, 0, 2),
    gsSPNTriangles_5b(3, 5, 2, 6, 4, 2, 5, 7, 2, 8, 6, 2),
    gsSPNTriangles_5b(7, 9, 2, 10, 8, 2, 9, 10, 2, 0, 0, 0),
    gsSPNTrianglesInit_5b(10, 11, 12, 13, 11, 14, 12, 11, 13, 15),
    gsSPNTriangles_5b(11, 16, 14, 11, 15, 17, 11, 18, 16, 11, 17, 19),
    gsSPNTriangles_5b(11, 20, 18, 11, 19, 21, 11, 21, 20, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_yos_wheel_tyu_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 22, 23, 24, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 8, int_yos_wheel_bo_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_yos_wheel_v[25], 31, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 1, 3, 2, 4, 0, 2),
    gsSPNTriangles_5b(3, 5, 2, 6, 4, 2, 5, 6, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_yos_wheel_sotowa_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 7, 8, 9, 7, 9, 10, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 8, int_yos_wheel_bo_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(10, 11, 12, 13, 13, 14, 11, 15, 16, 17),
    gsSPNTriangles_5b(17, 18, 15, 19, 20, 21, 21, 22, 19, 23, 24, 25),
    gsSPNTriangles_5b(25, 26, 23, 27, 28, 29, 29, 30, 27, 0, 0, 0),
    gsSPEndDisplayList(),
};

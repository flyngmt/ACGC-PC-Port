#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_tak_astro_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_tak_astro_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_tak_astro_pal[] = {
#include "assets/int_tak_astro_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_tak_astro_face_tex_pic_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_tak_astro_face_tex_pic_ci4_pal[] = {
#include "assets/int_tak_astro_face_tex_pic_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_astro_body_tex_txt[0x300];
#else
u8 int_tak_astro_body_tex_txt[] = {
#include "assets/int_tak_astro_body_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_astro_arm_tex_txt[0x100];
#else
u8 int_tak_astro_arm_tex_txt[] = {
#include "assets/int_tak_astro_arm_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_astro_head_tex_txt[0x80];
#else
u8 int_tak_astro_head_tex_txt[] = {
#include "assets/int_tak_astro_head_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_astro_back_tex_txt[0x180];
#else
u8 int_tak_astro_back_tex_txt[] = {
#include "assets/int_tak_astro_back_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_astro_packtop_tex_txt[0x80];
#else
u8 int_tak_astro_packtop_tex_txt[] = {
#include "assets/int_tak_astro_packtop_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_astro_pack_tex_txt[0x100];
#else
u8 int_tak_astro_pack_tex_txt[] = {
#include "assets/int_tak_astro_pack_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_astro_face_tex_txt[0x80];
#else
u8 int_tak_astro_face_tex_txt[] = {
#include "assets/int_tak_astro_face_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_tak_astro_v[0x440 / sizeof(Vtx)];
#else
Vtx int_tak_astro_v[] = {
#include "assets/int_tak_astro_v.inc"
};
#endif

Gfx int_tak_astro_face_env_model[] = {
    gsSPTexture(5000, 10000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_astro_face_tex_pic_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_astro_face_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 1, 1),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_astro_v[62], 6, 0),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 1, 3, 2, 3, 4, 2),
    gsSPNTriangles_5b(4, 5, 2, 5, 0, 2, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_tak_astro_body_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_astro_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_tak_astro_body_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_tak_astro_v, 23, 0),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 3, 4, 2, 2, 4, 0),
    gsSPNTriangles_5b(5, 0, 4, 5, 4, 6, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_tak_astro_arm_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPNTrianglesInit_5b(10, 7, 8, 9, 10, 9, 8, 11, 7, 9),
    gsSPNTriangles_5b(10, 12, 9, 13, 11, 14, 15, 16, 17, 18, 17, 19),
    gsSPNTriangles_5b(18, 20, 21, 22, 18, 19, 18, 22, 20, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_astro_head_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_tak_astro_v[23], 27, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 3, 1, 4, 5, 0),
    gsSPNTriangles_5b(6, 7, 8, 9, 10, 4, 10, 11, 4, 4, 11, 5),
    gsSPNTriangles_5b(8, 12, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_tak_astro_back_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 188),
    gsSPNTrianglesInit_5b(8, 13, 14, 15, 14, 16, 15, 17, 18, 19),
    gsSPNTriangles_5b(17, 20, 18, 21, 22, 23, 21, 24, 22, 21, 25, 24),
    gsSPNTriangles_5b(20, 26, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_astro_packtop_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_tak_astro_v[50], 12, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 5, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_tak_astro_pack_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 6, 7, 8, 9, 10, 11, 0, 0, 0),
    gsSPEndDisplayList(),
};

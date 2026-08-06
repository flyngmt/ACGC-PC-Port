#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx act_mus_kurage_a1_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 act_f37_kurage_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 act_f37_kurage_pal[] = {
#include "assets/act_mus_kurage_a1/act_f37_kurage_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 act_mus_kurage_head_tex[0x100];
#else
u8 act_mus_kurage_head_tex[] = {
#include "assets/act_mus_kurage_head_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 act_mus_kurage_foot_tex[0x100];
#else
u8 act_mus_kurage_foot_tex[] = {
#include "assets/act_mus_kurage_foot_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx act_mus_kurage_a1_v[0x320 / sizeof(Vtx)];
#else
Vtx act_mus_kurage_a1_v[] = {
#include "assets/act_mus_kurage_a1_v.inc"
};
#endif

Gfx act_mus_kurage_sakana_foot_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 180),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, act_f37_kurage_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, act_mus_kurage_foot_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(act_mus_kurage_a1_v, 24, 0),
    gsSPNTrianglesInit_5b(24, 0, 1, 2, 0, 2, 3, 1, 4, 2),
    gsSPNTriangles_5b(5, 6, 7, 5, 7, 0, 6, 8, 7, 9, 10, 6),
    gsSPNTriangles_5b(9, 6, 5, 10, 8, 6, 3, 2, 11, 3, 11, 9),
    gsSPNTriangles_5b(2, 4, 11, 12, 13, 14, 12, 14, 15, 13, 16, 14),
    gsSPNTriangles_5b(15, 17, 18, 15, 18, 19, 17, 20, 18, 19, 18, 21),
    gsSPNTriangles_5b(19, 21, 22, 18, 20, 21, 22, 23, 13, 22, 13, 12),
    gsSPNTriangles_5b(23, 16, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx act_mus_kurage_sakana_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 180),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, act_f37_kurage_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, act_mus_kurage_head_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&act_mus_kurage_a1_v[24], 26, 0),
    gsSPNTrianglesInit_5b(32, 0, 1, 2, 0, 3, 1, 3, 4, 5),
    gsSPNTriangles_5b(4, 6, 5, 7, 8, 2, 7, 9, 8, 10, 11, 9),
    gsSPNTriangles_5b(10, 6, 11, 12, 7, 1, 12, 1, 5, 10, 12, 5),
    gsSPNTriangles_5b(1, 7, 2, 5, 1, 3, 9, 7, 10, 7, 12, 10),
    gsSPNTriangles_5b(6, 10, 5, 13, 14, 15, 14, 16, 15, 17, 18, 16),
    gsSPNTriangles_5b(17, 19, 18, 13, 20, 21, 20, 22, 21, 22, 23, 24),
    gsSPNTriangles_5b(23, 19, 24, 14, 21, 25, 17, 14, 25, 17, 25, 24),
    gsSPNTriangles_5b(13, 21, 14, 16, 14, 17, 24, 21, 22, 24, 25, 21),
    gsSPNTriangles_5b(17, 24, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_act_mus_kurage_a1_c(void) {
    pc_load_asset("assets/act_mus_kurage_a1/act_f37_kurage_pal.bin", act_f37_kurage_pal, 0x20, 0x9625A0, 0, 1);
}
#endif

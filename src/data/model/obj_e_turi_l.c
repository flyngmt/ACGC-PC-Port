#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 obj_e_turi_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 obj_e_turi_pal[] = {
#include "assets/obj_e_turi_l/obj_e_turi_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_turi_t1_tex[0x800];
#else
u8 obj_e_turi_t1_tex[] = {
#include "assets/obj_e_turi_t1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_turi_t2_tex[0x800];
#else
u8 obj_e_turi_t2_tex[] = {
#include "assets/obj_e_turi_t2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_turi_t3_tex[0x800];
#else
u8 obj_e_turi_t3_tex[] = {
#include "assets/obj_e_turi_t3_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_e_turi_l_v[0x5B0 / sizeof(Vtx)];
#else
Vtx obj_e_turi_l_v[] = {
#include "assets/obj_e_turi_l_v.inc"
};
#endif

Gfx obj_e_turi_l_modelT[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_e_turi_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_turi_t1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_e_turi_l_v, 32, 0),
    gsSPNTrianglesInit_5b(19, 0, 1, 2, 0, 2, 3, 1, 4, 5),
    gsSPNTriangles_5b(1, 5, 2, 6, 7, 8, 6, 8, 9, 7, 10, 11),
    gsSPNTriangles_5b(7, 11, 8, 12, 13, 14, 12, 14, 15, 13, 16, 17),
    gsSPNTriangles_5b(13, 17, 14, 18, 19, 20, 18, 20, 21, 19, 22, 23),
    gsSPNTriangles_5b(19, 23, 20, 24, 25, 26, 24, 26, 27, 28, 29, 30),
    gsSPVertex(&obj_e_turi_l_v[31], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_turi_t2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPVertex(&obj_e_turi_l_v[47], 28, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 22, 23, 24),
    gsSPNTriangles_5b(22, 24, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 12, 13, 14, 12, 14, 15, 16, 17, 18),
    gsSPNTriangles_5b(16, 18, 19, 20, 21, 16, 20, 16, 17, 26, 27, 15),
    gsSPNTriangles_5b(26, 15, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_turi_t3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_turi_l_v[75], 16, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 12, 14, 15, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
Vtx obj_e_turi_r_v[0x590 / sizeof(Vtx)];
#else
Vtx obj_e_turi_r_v[] = {
#include "assets/obj_e_turi_r_v.inc"
};
#endif

Gfx obj_e_turi_r_modelT[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_e_turi_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_turi_t1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_e_turi_r_v, 32, 0),
    gsSPNTrianglesInit_5b(19, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 4, 7, 8, 7, 9, 10, 11, 12),
    gsSPNTriangles_5b(10, 12, 13, 14, 10, 13, 14, 13, 15, 16, 17, 18),
    gsSPNTriangles_5b(16, 18, 19, 20, 16, 19, 20, 19, 21, 22, 23, 24),
    gsSPNTriangles_5b(22, 24, 25, 23, 26, 27, 23, 27, 24, 28, 29, 30),
    gsSPVertex(&obj_e_turi_r_v[31], 14, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 5, 8, 5, 4, 10, 11, 12),
    gsSPNTriangles_5b(10, 12, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_turi_t2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPVertex(&obj_e_turi_r_v[45], 28, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 22, 23, 24),
    gsSPNTriangles_5b(22, 24, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 12, 13, 14, 12, 14, 15, 16, 17, 18),
    gsSPNTriangles_5b(16, 18, 19, 20, 21, 16, 20, 16, 17, 26, 27, 15),
    gsSPNTriangles_5b(26, 15, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_turi_t3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_turi_r_v[73], 16, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 12, 14, 15, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_obj_e_turi_l_c(void) {
    pc_load_asset("assets/obj_e_turi_l/obj_e_turi_pal.bin", obj_e_turi_pal, 0x20, 0x893D00, 0, 1);
}
#endif

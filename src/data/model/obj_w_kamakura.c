#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 obj_w_kamakura_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 obj_w_kamakura_pal[] = {
#include "assets/obj_w_kamakura/obj_w_kamakura_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_kamakura_t1_tex[0x800];
#else
u8 obj_w_kamakura_t1_tex[] = {
#include "assets/obj_w_kamakura_t1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_kamakura_t2_tex[0x800];
#else
u8 obj_w_kamakura_t2_tex[] = {
#include "assets/obj_w_kamakura_t2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_kamakura_t3_tex[0x800];
#else
u8 obj_w_kamakura_t3_tex[] = {
#include "assets/obj_w_kamakura_t3_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_kamakura_light02_tex[0x80];
#else
u8 obj_w_kamakura_light02_tex[] = {
#include "assets/obj_w_kamakura_light02_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_w_kamakura_v[0x540 / sizeof(Vtx)];
#else
Vtx obj_w_kamakura_v[] = {
#include "assets/obj_w_kamakura_v.inc"
};
#endif

Gfx obj_w_kamakura_light_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, ENVIRONMENT, 0, 0, 0, PRIMITIVE, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_w_kamakura_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_kamakura_t2_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_w_kamakura_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_kamakura_t2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_kamakura_v[4], 32, 0),
    gsSPNTrianglesInit_5b(30, 0, 1, 2, 3, 2, 4, 3, 5, 2),
    gsSPNTriangles_5b(5, 6, 2, 6, 0, 2, 5, 7, 6, 8, 9, 0),
    gsSPNTriangles_5b(8, 0, 10, 0, 6, 11, 0, 11, 10, 6, 7, 11),
    gsSPNTriangles_5b(12, 13, 14, 12, 14, 3, 14, 15, 5, 14, 5, 3),
    gsSPNTriangles_5b(15, 7, 5, 9, 16, 1, 9, 1, 0, 3, 4, 12),
    gsSPNTriangles_5b(4, 17, 12, 18, 19, 20, 21, 18, 20, 21, 20, 22),
    gsSPNTriangles_5b(21, 22, 23, 22, 24, 23, 25, 19, 26, 27, 25, 26),
    gsSPNTriangles_5b(27, 26, 28, 29, 30, 27, 29, 27, 28, 0, 0, 0),
    gsSPVertex(&obj_w_kamakura_v[35], 19, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 3, 0, 2, 3, 2, 4),
    gsSPNTriangles_5b(5, 6, 3, 5, 3, 4, 6, 7, 8, 6, 8, 9),
    gsSPNTriangles_5b(8, 10, 11, 8, 11, 9, 10, 12, 11, 13, 14, 15),
    gsSPNTriangles_5b(16, 13, 15, 16, 15, 17, 18, 5, 16, 18, 16, 17),
    gsSPEndDisplayList(),
};

Gfx obj_w_kamakura_window_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_w_kamakura_light02_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_kamakura_v[54], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_kamakura_t1_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_w_kamakura_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_kamakura_t1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_kamakura_v[58], 13, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 0, 3, 1, 3, 4, 1),
    gsSPNTriangles_5b(5, 6, 7, 6, 8, 7, 9, 10, 11, 9, 12, 10),
    gsSPEndDisplayList(),
};

Gfx obj_w_kamakura_t3_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_DECAL2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_w_kamakura_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_kamakura_t3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_kamakura_v[71], 13, 0),
    gsSPNTrianglesInit_5b(11, 0, 1, 2, 1, 3, 2, 3, 4, 2),
    gsSPNTriangles_5b(4, 5, 2, 5, 6, 2, 6, 7, 2, 6, 8, 7),
    gsSPNTriangles_5b(8, 9, 7, 9, 10, 7, 10, 11, 7, 11, 12, 7),
    gsSPEndDisplayList(),
};

Gfx kamakura_DL_model[] = {
    gsSPDisplayList(obj_w_kamakura_light_model),
    gsSPDisplayList(obj_w_kamakura_t2_on_model),
    gsSPDisplayList(obj_w_kamakura_t1_onT_model),
    gsSPDisplayList(obj_w_kamakura_t3_onT_model),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_obj_w_kamakura_c(void) {
    pc_load_asset("assets/obj_w_kamakura/obj_w_kamakura_pal.bin", obj_w_kamakura_pal, 0x20, 0x812A00, 0, 1);
}
#endif

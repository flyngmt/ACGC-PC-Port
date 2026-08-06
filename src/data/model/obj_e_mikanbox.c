#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_e_mikanbox_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) u8 obj_e_mikanbox_tex[] = {
#include "assets/obj_e_mikanbox_tex.inc"
};
#endif

#ifdef TARGET_PC
static Vtx obj_e_mikanbox_v[0x1C0 / sizeof(Vtx)];
#else
static Vtx obj_e_mikanbox_v[] = {
#include "assets/obj_e_mikanbox/obj_e_mikanbox_v.inc"
};
#endif

Gfx obj_e_mikanbox_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, obj_e_mikanbox_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_e_mikanbox_v, 24, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 copyright_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 copyright_tex[] = {
#include "assets/copyright_tex.inc"
};
#endif

Gfx obj_e_mikanbox_copyrightT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 256, 16, copyright_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
u8 end_notice2_tex[0x800];
#else
u8 end_notice2_tex[] = {
#include "assets/end_notice2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 end_notice1_tex[0x800];
#else
u8 end_notice1_tex[] = {
#include "assets/end_notice1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 end_notice3_tex[0x800];
#else
u8 end_notice3_tex[] = {
#include "assets/end_notice3_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx end_notice_v[0xC0 / sizeof(Vtx)];
#else
Vtx end_notice_v[] = {
#include "assets/end_notice_v.inc"
};
#endif

Gfx obj_e_mikanbox_copyrightT_model2[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 256, 16, end_notice3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(end_notice_v, 12, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 256, 16, end_notice1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 6, 7, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 256, 16, end_notice2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_obj_e_mikanbox_c(void) {
    pc_load_asset("assets/obj_e_mikanbox/obj_e_mikanbox_v.bin", obj_e_mikanbox_v, 0x1C0, 0x818B40, 0, 2);
}
#endif

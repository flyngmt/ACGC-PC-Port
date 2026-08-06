#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx rom_train_out_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 rom_train_4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 rom_train_4_pal[] = {
#include "assets/rom_train_4_pal.inc"
};
#endif

#ifdef TARGET_PC
static u16 rom_train_3_pal[0x20 / sizeof(u16)];
#else
static u16 rom_train_3_pal[] = {
#include "assets/rom_train_out/rom_train_3_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_train_bgtree_tex[0x800];
#else
u8 rom_train_bgtree_tex[] = {
#include "assets/rom_train_bgtree_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_train_bgsky_tex[0x80];
#else
u8 rom_train_bgsky_tex[] = {
#include "assets/rom_train_bgsky_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_train_tunnel_tex[0x400];
#else
u8 rom_train_tunnel_tex[] = {
#include "assets/rom_train_tunnel_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_train_bgcloud_tex_rgb_i4[0x800];
#else
u8 rom_train_bgcloud_tex_rgb_i4[] = {
#include "assets/rom_train_bgcloud_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_train_glass_tex_rgb_i4[0x80];
#else
u8 rom_train_glass_tex_rgb_i4[] = {
#include "assets/rom_train_glass_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_train_shine_tex_rgb_i4[0x100];
#else
u8 rom_train_shine_tex_rgb_i4[] = {
#include "assets/rom_train_shine_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
Vtx rom_train_out_v[0x300 / sizeof(Vtx)];
#else
Vtx rom_train_out_v[] = {
#include "assets/rom_train_out_v.inc"
};
#endif

Gfx rom_train_out_bgcloud_modelT[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, 0, PRIM_LOD_FRAC, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetEnvColor(127, 127, 100, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 64, rom_train_bgcloud_tex_rgb_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPDisplayList(anime_2_txt),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&rom_train_out_v[16], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx rom_train_out_bgtree_modelT[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, 0, PRIM_LOD_FRAC, ENVIRONMENT, 0, 0, 0, TEXEL0, TEXEL1, 0, COMBINED, 0, 0, 0, 0,
                       COMBINED),
    gsDPSetEnvColor(60, 60, 35, 255),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_3_txt),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, rom_train_bgtree_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPDisplayList(anime_1_txt),
    gsSPVertex(&rom_train_out_v[24], 8, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx rom_train_out_shineglass_modelT[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, TEXEL1, 0, 0, 0, 0, COMBINED, COMBINED, 0, PRIM_LOD_FRAC, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 8, rom_train_shine_tex_rgb_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, rom_train_glass_tex_rgb_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_CLAMP, GX_CLAMP, 0, 15),
    gsSPDisplayList(anime_5_txt),
    gsSPVertex(&rom_train_out_v[32], 16, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx rom_train_out_tunnel_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, 0, PRIM_LOD_FRAC, ENVIRONMENT, 0, 0, 0, TEXEL0, TEXEL1, 0, COMBINED, 0, 0, 0, 0,
                       COMBINED),
    gsDPSetEnvColor(0, 0, 0, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_train_3_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, rom_train_tunnel_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsSPDisplayList(anime_4_txt),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&rom_train_out_v[8], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx rom_train_out_bgsky_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_train_4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, rom_train_bgsky_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(rom_train_out_v, 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_rom_train_out_c(void) {
    pc_load_asset("assets/rom_train_out/rom_train_3_pal.bin", rom_train_3_pal, 0x20, 0x8D9A40, 0, 1);
}
#endif

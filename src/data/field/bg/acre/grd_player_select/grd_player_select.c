#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_open_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_open_pal[] = {
#include "assets/field/bg/rom_open_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_open_floor_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_open_floor_tex[] = {
#include "assets/field/bg/rom_open_floor_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_open_shade_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_open_shade_tex[] = {
#include "assets/field/bg/rom_open_shade_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_open_spot2_tex_rgb_i4[0x200];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_open_spot2_tex_rgb_i4[] = {
#include "assets/field/bg/rom_open_spot2_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_open_spot_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_open_spot_tex[] = {
#include "assets/field/bg/rom_open_spot_tex.inc"
};
#endif

#ifdef TARGET_PC
static Vtx grd_player_select_v[0x140 / sizeof(Vtx)];
#else
static Vtx grd_player_select_v[] = {
#include "assets/field/bg/grd_player_select_v.inc"
};
#endif

extern Gfx grd_player_select_modelT[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, TEXEL1, TEXEL1, 0, 0, 0, COMBINED,
                       COMBINED, 0, PRIM_LOD_FRAC, 0),
    gsDPSetPrimColor(0, 150, 255, 255, 255, 255),
    gsDPSetEnvColor(0xFF, 0xFF, 0x82, 0xFF),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_XLU_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(rom_open_spot2_tex_rgb_i4, G_IM_FMT_I, 32, 32, 15, GX_REPEAT, GX_REPEAT, 15, 15),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_8b, 32, 64, rom_open_spot_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 0, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPDisplayList(0x08000000),
    gsSPLoadGeometryMode(G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&grd_player_select_v[12], 4, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 0, 0, 0, 255),
    gsDPLoadTextureBlock_4b_Dolphin(rom_open_shade_tex, G_IM_FMT_I, 32, 64, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_player_select_v[16], 4, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          0, 0, 0  // tri2
                          ),
    gsSPEndDisplayList(),
};

extern Gfx grd_player_select_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, PRIMITIVE, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_open_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_open_floor_tex, G_IM_FMT_CI, 64, 64, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&grd_player_select_v[0], 12, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 6, 7,   // tri0
                      8, 9, 10,  // tri1
                      8, 10, 11, // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_field_bg_acre_grd_player_select_grd_player_select_c(void) {
    pc_load_asset("assets/field/bg/rom_open_pal.bin", rom_open_pal, 0x20, 0xC15580, 0, 1);
    pc_load_asset("assets/field/bg/rom_open_floor_tex.bin", rom_open_floor_tex, 0x800, 0xC155A0, 0, 0);
    pc_load_asset("assets/field/bg/rom_open_shade_tex.bin", rom_open_shade_tex, 0x400, 0xC15DA0, 0, 0);
    pc_load_asset("assets/field/bg/rom_open_spot2_tex_rgb_i4.bin", rom_open_spot2_tex_rgb_i4, 0x200, 0xC161A0, 0, 0);
    pc_load_asset("assets/field/bg/rom_open_spot_tex.bin", rom_open_spot_tex, 0x800, 0xC163A0, 0, 0);
    pc_load_asset("assets/field/bg/grd_player_select_v.bin", grd_player_select_v, 0x140, 0xC16BA0, 0, 2);
}
#endif

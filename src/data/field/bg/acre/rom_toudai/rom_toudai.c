#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_toudai_yuka_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_toudai_yuka_pal[] = {
#include "assets/field/bg/rom_toudai_yuka_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_toudai_kabe_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_toudai_kabe_pal[] = {
#include "assets/field/bg/rom_toudai_kabe_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_toudai_step_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_toudai_step_pal[] = {
#include "assets/field/bg/rom_toudai_step_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_toudai_meka_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_toudai_meka_pal[] = {
#include "assets/field/bg/rom_toudai_meka_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_toudai_ukiwa_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_toudai_ukiwa_pal[] = {
#include "assets/field/bg/rom_toudai_ukiwa_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_toudai_yuka_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_toudai_yuka_tex[] = {
#include "assets/field/bg/rom_toudai_yuka_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_toudai_kabeA_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_toudai_kabeA_tex[] = {
#include "assets/field/bg/rom_toudai_kabeA_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_toudai_kabeB_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_toudai_kabeB_tex[] = {
#include "assets/field/bg/rom_toudai_kabeB_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_toudai_step_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_toudai_step_tex[] = {
#include "assets/field/bg/rom_toudai_step_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_toudai_mekaA_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_toudai_mekaA_tex[] = {
#include "assets/field/bg/rom_toudai_mekaA_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_toudai_ukiwa_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_toudai_ukiwa_tex[] = {
#include "assets/field/bg/rom_toudai_ukiwa_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_toudai_kage1_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_toudai_kage1_tex[] = {
#include "assets/field/bg/rom_toudai_kage1_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_toudai_mekaC_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_toudai_mekaC_tex[] = {
#include "assets/field/bg/rom_toudai_mekaC_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_toudai_kage2_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_toudai_kage2_tex[] = {
#include "assets/field/bg/rom_toudai_kage2_tex.inc"
};
#endif

#ifdef TARGET_PC
static Vtx rom_toudai_v[0x670 / sizeof(Vtx)];
#else
static Vtx rom_toudai_v[] = {
#include "assets/field/bg/rom_toudai_v.inc"
};
#endif

extern Gfx rom_toudai_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx rom_toudai_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_toudai_meka_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_toudai_mekaC_tex, G_IM_FMT_CI, 32, 32, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&rom_toudai_v[66], 11, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          0, 4, 5  // tri2
                          ),
    gsSPNTriangles_5b(0, 6, 4,  // tri0
                      7, 8, 9,  // tri1
                      8, 10, 9, // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_toudai_mekaA_tex, G_IM_FMT_CI, 16, 32, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_toudai_v[77], 22, 0),
    gsSPNTrianglesInit_5b(12,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 6, 7,   // tri0
                      8, 9, 10,  // tri1
                      8, 10, 11, // tri2
                      12, 13, 14 // tri3
                      ),
    gsSPNTriangles_5b(12, 14, 15, // tri0
                      16, 17, 18, // tri1
                      16, 18, 19, // tri2
                      20, 8, 11   // tri3
                      ),
    gsSPNTriangles_5b(20, 11, 21, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_toudai_ukiwa_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_toudai_ukiwa_tex, G_IM_FMT_CI, 32, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_toudai_v[99], 4, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_toudai_yuka_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_toudai_yuka_tex, G_IM_FMT_CI, 64, 64, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_toudai_v[0], 19, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 4, // tri1
                          1, 0, 5  // tri2
                          ),
    gsSPNTriangles_5b(2, 6, 0, // tri0
                      0, 4, 7, // tri1
                      0, 8, 3, // tri2
                      9, 10, 0 // tri3
                      ),
    gsSPNTriangles_5b(10, 11, 0, // tri0
                      11, 12, 0, // tri1
                      12, 13, 0, // tri2
                      14, 15, 0  // tri3
                      ),
    gsSPNTriangles_5b(15, 16, 0, // tri0
                      16, 17, 0, // tri1
                      17, 18, 0, // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_toudai_step_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_toudai_step_tex, G_IM_FMT_CI, 64, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_toudai_v[19], 8, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          3, 0, 2, // tri1
                          4, 3, 2  // tri2
                          ),
    gsSPNTriangles_5b(5, 4, 2, // tri0
                      6, 4, 5, // tri1
                      0, 7, 1, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_toudai_kabe_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_toudai_kabeB_tex, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_toudai_v[27], 31, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 0, 3  // tri2
                          ),
    gsSPNTriangles_5b(5, 4, 3,  // tri0
                      6, 7, 8,  // tri1
                      9, 6, 8,  // tri2
                      10, 11, 8 // tri3
                      ),
    gsSPNTriangles_5b(10, 8, 12, // tri0
                      9, 13, 14, // tri1
                      9, 14, 15, // tri2
                      16, 12, 15 // tri3
                      ),
    gsSPNTriangles_5b(14, 16, 15, // tri0
                      11, 13, 9,  // tri1
                      8, 11, 9,   // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_toudai_kabeA_tex, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(12,         // tri count
                          17, 18, 19, // tri0
                          20, 17, 19, // tri1
                          21, 22, 23  // tri2
                          ),
    gsSPNTriangles_5b(24, 21, 23, // tri0
                      25, 26, 27, // tri1
                      25, 27, 28, // tri2
                      24, 26, 25  // tri3
                      ),
    gsSPNTriangles_5b(21, 24, 25, // tri0
                      29, 23, 22, // tri1
                      29, 22, 30, // tri2
                      18, 17, 28  // tri3
                      ),
    gsSPNTriangles_5b(18, 28, 27, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 110, 0, 0, 30, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(rom_toudai_kage2_tex, G_IM_FMT_I, 16, 16, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_toudai_v[58], 8, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_toudai_kage1_tex, G_IM_FMT_I, 16, 16, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          4, 5, 6, // tri0
                          4, 6, 7, // tri1
                          0, 0, 0  // tri2
                          ),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_field_bg_acre_rom_toudai_rom_toudai_c(void) {
    pc_load_asset("assets/field/bg/rom_toudai_yuka_pal.bin", rom_toudai_yuka_pal, 0x20, 0xB98360, 0, 1);
    pc_load_asset("assets/field/bg/rom_toudai_kabe_pal.bin", rom_toudai_kabe_pal, 0x20, 0xB98380, 0, 1);
    pc_load_asset("assets/field/bg/rom_toudai_step_pal.bin", rom_toudai_step_pal, 0x20, 0xB983A0, 0, 1);
    pc_load_asset("assets/field/bg/rom_toudai_meka_pal.bin", rom_toudai_meka_pal, 0x20, 0xB983C0, 0, 1);
    pc_load_asset("assets/field/bg/rom_toudai_ukiwa_pal.bin", rom_toudai_ukiwa_pal, 0x20, 0xB983E0, 0, 1);
    pc_load_asset("assets/field/bg/rom_toudai_yuka_tex.bin", rom_toudai_yuka_tex, 0x800, 0xB98400, 0, 0);
    pc_load_asset("assets/field/bg/rom_toudai_kabeA_tex.bin", rom_toudai_kabeA_tex, 0x800, 0xB98C00, 0, 0);
    pc_load_asset("assets/field/bg/rom_toudai_kabeB_tex.bin", rom_toudai_kabeB_tex, 0x800, 0xB99400, 0, 0);
    pc_load_asset("assets/field/bg/rom_toudai_step_tex.bin", rom_toudai_step_tex, 0x400, 0xB99C00, 0, 0);
    pc_load_asset("assets/field/bg/rom_toudai_mekaA_tex.bin", rom_toudai_mekaA_tex, 0x100, 0xB9A000, 0, 0);
    pc_load_asset("assets/field/bg/rom_toudai_ukiwa_tex.bin", rom_toudai_ukiwa_tex, 0x200, 0xB9A100, 0, 0);
    pc_load_asset("assets/field/bg/rom_toudai_kage1_tex.bin", rom_toudai_kage1_tex, 0x80, 0xB9A300, 0, 0);
    pc_load_asset("assets/field/bg/rom_toudai_mekaC_tex.bin", rom_toudai_mekaC_tex, 0x200, 0xB9A380, 0, 0);
    pc_load_asset("assets/field/bg/rom_toudai_kage2_tex.bin", rom_toudai_kage2_tex, 0x80, 0xB9A580, 0, 0);
    pc_load_asset("assets/field/bg/rom_toudai_v.bin", rom_toudai_v, 0x670, 0xB9A600, 0, 2);
}
#endif

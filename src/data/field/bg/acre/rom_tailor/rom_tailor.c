#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_tailor_wall_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_tailor_wall_pal[] = {
#include "assets/field/bg/rom_tailor_wall_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_tailor_floor_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_tailor_floor_pal[] = {
#include "assets/field/bg/rom_tailor_floor_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_tailor_mado_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_tailor_mado_pal[] = {
#include "assets/field/bg/rom_tailor_mado_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_tailor_reji_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_tailor_reji_pal[] = {
#include "assets/field/bg/rom_tailor_reji_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_tailor_dogu_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_tailor_dogu_pal[] = {
#include "assets/field/bg/rom_tailor_dogu_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_tailor_misin_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_tailor_misin_pal[] = {
#include "assets/field/bg/rom_tailor_misin_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_tailor_table_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_tailor_table_pal[] = {
#include "assets/field/bg/rom_tailor_table_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_tailor_box_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_tailor_box_pal[] = {
#include "assets/field/bg/rom_tailor_box_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_tailor_quilt_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_tailor_quilt_pal[] = {
#include "assets/field/bg/rom_tailor_quilt_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_tailor_ent_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_tailor_ent_pal[] = {
#include "assets/field/bg/rom_tailor_ent_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_wallA_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_wallA_tex[] = {
#include "assets/field/bg/rom_tailor_wallA_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_wallB_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_wallB_tex[] = {
#include "assets/field/bg/rom_tailor_wallB_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_floorA_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_floorA_tex[] = {
#include "assets/field/bg/rom_tailor_floorA_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_floorB_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_floorB_tex[] = {
#include "assets/field/bg/rom_tailor_floorB_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_floorC_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_floorC_tex[] = {
#include "assets/field/bg/rom_tailor_floorC_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_floorD_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_floorD_tex[] = {
#include "assets/field/bg/rom_tailor_floorD_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_kage1_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_kage1_tex[] = {
#include "assets/field/bg/rom_tailor_kage1_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_mado_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_mado_tex[] = {
#include "assets/field/bg/rom_tailor_mado_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_pic1_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_pic1_tex[] = {
#include "assets/field/bg/rom_tailor_pic1_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_pic2_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_pic2_tex[] = {
#include "assets/field/bg/rom_tailor_pic2_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_pic3_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_pic3_tex[] = {
#include "assets/field/bg/rom_tailor_pic3_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_pic4_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_pic4_tex[] = {
#include "assets/field/bg/rom_tailor_pic4_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_pic5_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_pic5_tex[] = {
#include "assets/field/bg/rom_tailor_pic5_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_pic6_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_pic6_tex[] = {
#include "assets/field/bg/rom_tailor_pic6_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_pic7_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_pic7_tex[] = {
#include "assets/field/bg/rom_tailor_pic7_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_pic8_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_pic8_tex[] = {
#include "assets/field/bg/rom_tailor_pic8_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_tyoki_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_tyoki_tex[] = {
#include "assets/field/bg/rom_tailor_tyoki_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_cloth1_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_cloth1_tex[] = {
#include "assets/field/bg/rom_tailor_cloth1_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_misin2_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_misin2_tex[] = {
#include "assets/field/bg/rom_tailor_misin2_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_table_mae_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_table_mae_tex[] = {
#include "assets/field/bg/rom_tailor_table_mae_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_table_yoko_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_table_yoko_tex[] = {
#include "assets/field/bg/rom_tailor_table_yoko_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_table_ue_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_table_ue_tex[] = {
#include "assets/field/bg/rom_tailor_table_ue_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_ito_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_ito_tex[] = {
#include "assets/field/bg/rom_tailor_ito_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_table_reji_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_table_reji_tex[] = {
#include "assets/field/bg/rom_tailor_table_reji_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_misin1_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_misin1_tex[] = {
#include "assets/field/bg/rom_tailor_misin1_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_misindai_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_misindai_tex[] = {
#include "assets/field/bg/rom_tailor_misindai_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_table_misin1_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_table_misin1_tex[] = {
#include "assets/field/bg/rom_tailor_table_misin1_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_reji_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_reji_tex[] = {
#include "assets/field/bg/rom_tailor_reji_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_table_misin2_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_table_misin2_tex[] = {
#include "assets/field/bg/rom_tailor_table_misin2_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_box_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_box_tex[] = {
#include "assets/field/bg/rom_tailor_box_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_box1_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_box1_tex[] = {
#include "assets/field/bg/rom_tailor_box1_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_box2_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_box2_tex[] = {
#include "assets/field/bg/rom_tailor_box2_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_box3_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_box3_tex[] = {
#include "assets/field/bg/rom_tailor_box3_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_box4_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_box4_tex[] = {
#include "assets/field/bg/rom_tailor_box4_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_box5_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_box5_tex[] = {
#include "assets/field/bg/rom_tailor_box5_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_box6_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_box6_tex[] = {
#include "assets/field/bg/rom_tailor_box6_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_box7_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_box7_tex[] = {
#include "assets/field/bg/rom_tailor_box7_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_box8_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_box8_tex[] = {
#include "assets/field/bg/rom_tailor_box8_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_kage2_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_kage2_tex[] = {
#include "assets/field/bg/rom_tailor_kage2_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_quilt_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_quilt_tex[] = {
#include "assets/field/bg/rom_tailor_quilt_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_ent_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_ent_tex[] = {
#include "assets/field/bg/rom_tailor_ent_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_misinbari1_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_misinbari1_tex[] = {
#include "assets/field/bg/rom_tailor_misinbari1_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_misinbari2_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_misinbari2_tex[] = {
#include "assets/field/bg/rom_tailor_misinbari2_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_tape_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_tape_tex[] = {
#include "assets/field/bg/rom_tailor_tape_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_dogu1_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_dogu1_tex[] = {
#include "assets/field/bg/rom_tailor_dogu1_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_dogu2_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_tailor_dogu2_tex[] = {
#include "assets/field/bg/rom_tailor_dogu2_tex.inc"
};
#endif

#ifdef TARGET_PC
static Vtx rom_tailor_v[0x1DE0 / sizeof(Vtx)];
#else
static Vtx rom_tailor_v[] = {
#include "assets/field/bg/rom_tailor_v.inc"
};
#endif

extern Gfx rom_tailor_modelT[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 0, 0, 30, 80),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tailor_kage2_tex, G_IM_FMT_I, 16, 16, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&rom_tailor_v[274], 12, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tailor_kage1_tex, G_IM_FMT_I, 32, 16, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          4, 5, 6, // tri0
                          4, 6, 7, // tri1
                          8, 9, 10 // tri2
                          ),
    gsSPNTriangles_5b(8, 10, 11, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tailor_kage2_tex, G_IM_FMT_I, 16, 16, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_tailor_v[286], 4, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          0, 0, 0  // tri2
                          ),
    gsSPEndDisplayList(),
};

extern Gfx rom_tailor_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_tailor_table_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tailor_table_misin2_tex, G_IM_FMT_CI, 16, 16, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&rom_tailor_v[290], 24, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 6, 7, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tailor_table_misin1_tex, G_IM_FMT_CI, 32, 16, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4,         // tri count
                          8, 9, 10,  // tri0
                          8, 10, 11, // tri1
                          12, 13, 14 // tri2
                          ),
    gsSPNTriangles_5b(12, 14, 15, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tailor_table_yoko_tex, G_IM_FMT_CI, 16, 16, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(4,          // tri count
                          16, 17, 18, // tri0
                          16, 18, 19, // tri1
                          20, 21, 22  // tri2
                          ),
    gsSPNTriangles_5b(20, 22, 23, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tailor_table_mae_tex, G_IM_FMT_CI, 32, 16, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&rom_tailor_v[314], 8, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 6, 7, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_tailor_reji_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tailor_tyoki_tex, G_IM_FMT_CI, 16, 32, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_tailor_v[322], 4, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_tailor_dogu_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tailor_dogu1_tex, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_tailor_v[326], 30, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tailor_tape_tex, G_IM_FMT_CI, 32, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          4, 5, 6, // tri0
                          5, 7, 6, // tri1
                          5, 8, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 9, 7, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(2,          // tri count
                          10, 11, 12, // tri0
                          11, 13, 12, // tri1
                          0, 0, 0     // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tailor_ito_tex, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(8,          // tri count
                          14, 15, 16, // tri0
                          14, 16, 17, // tri1
                          18, 19, 20  // tri2
                          ),
    gsSPNTriangles_5b(18, 20, 21, // tri0
                      22, 23, 24, // tri1
                      22, 24, 25, // tri2
                      26, 27, 28  // tri3
                      ),
    gsSPNTriangles_5b(26, 28, 29, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&rom_tailor_v[356], 24, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          0, 0, 0  // tri2
                          ),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(2,       // tri count
                          4, 5, 6, // tri0
                          4, 6, 7, // tri1
                          0, 0, 0  // tri2
                          ),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(2,         // tri count
                          8, 9, 10,  // tri0
                          8, 10, 11, // tri1
                          0, 0, 0    // tri2
                          ),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(6,          // tri count
                          12, 13, 14, // tri0
                          12, 14, 15, // tri1
                          16, 17, 18  // tri2
                          ),
    gsSPNTriangles_5b(16, 18, 19, // tri0
                      20, 21, 22, // tri1
                      20, 22, 23, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_tailor_misin_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tailor_misinbari2_tex, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_tailor_v[380], 8, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tailor_misinbari1_tex, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          4, 5, 6, // tri0
                          4, 6, 7, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tailor_misindai_tex, G_IM_FMT_CI, 64, 16, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_tailor_v[388], 22, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tailor_misin1_tex, G_IM_FMT_CI, 64, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          4, 5, 6, // tri0
                          4, 6, 7, // tri1
                          8, 9, 10 // tri2
                          ),
    gsSPNTriangles_5b(8, 10, 11,  // tri0
                      12, 13, 14, // tri1
                      13, 15, 14, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tailor_misin2_tex, G_IM_FMT_CI, 64, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4,          // tri count
                          16, 17, 18, // tri0
                          16, 18, 19, // tri1
                          20, 19, 18  // tri2
                          ),
    gsSPNTriangles_5b(20, 18, 21, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_tailor_box_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tailor_box8_tex, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_tailor_v[410], 28, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          0, 3, 4  // tri2
                          ),
    gsSPNTriangles_5b(0, 4, 5, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tailor_box6_tex, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          6, 7, 8, // tri0
                          6, 8, 9, // tri1
                          6, 9, 10 // tri2
                          ),
    gsSPNTriangles_5b(6, 10, 11, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tailor_box4_tex, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4,          // tri count
                          12, 13, 14, // tri0
                          12, 14, 15, // tri1
                          12, 15, 16  // tri2
                          ),
    gsSPNTriangles_5b(12, 16, 17, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tailor_box2_tex, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4,          // tri count
                          18, 19, 20, // tri0
                          18, 20, 21, // tri1
                          18, 21, 22  // tri2
                          ),
    gsSPNTriangles_5b(18, 22, 23, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tailor_box_tex, G_IM_FMT_CI, 16, 32, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(2,          // tri count
                          24, 25, 26, // tri0
                          25, 27, 26, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPVertex(&rom_tailor_v[438], 16, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 3, 5  // tri2
                          ),
    gsSPNTriangles_5b(3, 1, 5, // tri0
                      0, 6, 7, // tri1
                      0, 7, 2, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(2,         // tri count
                          8, 9, 10,  // tri0
                          8, 10, 11, // tri1
                          0, 0, 0    // tri2
                          ),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(2,          // tri count
                          12, 13, 14, // tri0
                          12, 14, 15, // tri1
                          0, 0, 0     // tri2
                          ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_tailor_quilt_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tailor_quilt_tex, G_IM_FMT_CI, 64, 64, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_tailor_v[454], 24, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_tailor_mado_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tailor_pic8_tex, G_IM_FMT_CI, 32, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          4, 5, 6, // tri0
                          7, 4, 6, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tailor_pic6_tex, G_IM_FMT_CI, 32, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2,        // tri count
                          8, 9, 10, // tri0
                          8, 11, 9, // tri1
                          0, 0, 0   // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tailor_pic5_tex, G_IM_FMT_CI, 32, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2,          // tri count
                          12, 13, 14, // tri0
                          12, 14, 15, // tri1
                          0, 0, 0     // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tailor_mado_tex, G_IM_FMT_CI, 32, 32, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4,          // tri count
                          16, 17, 18, // tri0
                          17, 19, 18, // tri1
                          20, 21, 22  // tri2
                          ),
    gsSPNTriangles_5b(20, 23, 21, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsSPVertex(&rom_tailor_v[0], 8, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_tailor_wall_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tailor_wallB_tex, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_tailor_v[8], 32, 0),
    gsSPNTrianglesInit_5b(25,      // tri count
                          0, 1, 2, // tri0
                          3, 2, 1, // tri1
                          2, 3, 4  // tri2
                          ),
    gsSPNTriangles_5b(0, 5, 6,  // tri0
                      5, 7, 6,  // tri1
                      8, 9, 10, // tri2
                      9, 11, 10 // tri3
                      ),
    gsSPNTriangles_5b(4, 12, 13,  // tri0
                      12, 14, 13, // tri1
                      7, 5, 15,   // tri2
                      5, 16, 15   // tri3
                      ),
    gsSPNTriangles_5b(15, 17, 10, // tri0
                      18, 1, 6,   // tri1
                      1, 0, 6,    // tri2
                      8, 10, 17   // tri3
                      ),
    gsSPNTriangles_5b(19, 12, 3,  // tri0
                      12, 4, 3,   // tri1
                      15, 16, 17, // tri2
                      20, 21, 22  // tri3
                      ),
    gsSPNTriangles_5b(23, 20, 22, // tri0
                      24, 25, 26, // tri1
                      27, 24, 26, // tri2
                      20, 28, 29  // tri3
                      ),
    gsSPNTriangles_5b(21, 20, 29, // tri0
                      30, 31, 26, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&rom_tailor_v[40], 7, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          1, 0, 3, // tri1
                          4, 3, 0  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 6, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tailor_wallA_tex, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_tailor_v[47], 29, 0),
    gsSPNTrianglesInit_5b(31,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 1, 5  // tri2
                          ),
    gsSPNTriangles_5b(1, 3, 5,  // tri0
                      3, 6, 7,  // tri1
                      6, 8, 7,  // tri2
                      9, 10, 11 // tri3
                      ),
    gsSPNTriangles_5b(10, 12, 11, // tri0
                      13, 14, 15, // tri1
                      14, 9, 15,  // tri2
                      16, 17, 18  // tri3
                      ),
    gsSPNTriangles_5b(19, 11, 20, // tri0
                      19, 9, 11,  // tri1
                      12, 20, 11, // tri2
                      21, 22, 23  // tri3
                      ),
    gsSPNTriangles_5b(21, 16, 22, // tri0
                      16, 18, 22, // tri1
                      18, 23, 22, // tri2
                      24, 15, 9   // tri3
                      ),
    gsSPNTriangles_5b(24, 25, 15, // tri0
                      25, 13, 15, // tri1
                      16, 26, 17, // tri2
                      26, 20, 17  // tri3
                      ),
    gsSPNTriangles_5b(16, 19, 26, // tri0
                      19, 20, 26, // tri1
                      10, 9, 14,  // tri2
                      5, 3, 7     // tri3
                      ),
    gsSPNTriangles_5b(27, 8, 6,  // tri0
                      28, 6, 3,  // tri1
                      28, 27, 6, // tri2
                      4, 2, 1    // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_tailor_floor_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tailor_floorD_tex, G_IM_FMT_CI, 64, 64, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_tailor_v[76], 28, 0),
    gsSPNTrianglesInit_5b(10,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          0, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(3, 1, 5, // tri0
                      6, 7, 8, // tri1
                      6, 9, 7, // tri2
                      6, 10, 9 // tri3
                      ),
    gsSPNTriangles_5b(6, 11, 10, // tri0
                      7, 9, 12,  // tri1
                      13, 9, 10, // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tailor_floorC_tex, G_IM_FMT_CI, 64, 64, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(10,         // tri count
                          14, 15, 16, // tri0
                          14, 17, 15, // tri1
                          17, 18, 15  // tri2
                          ),
    gsSPNTriangles_5b(18, 19, 15, // tri0
                      20, 17, 14, // tri1
                      18, 17, 21, // tri2
                      22, 23, 24  // tri3
                      ),
    gsSPNTriangles_5b(25, 24, 23, // tri0
                      22, 24, 26, // tri1
                      24, 25, 27, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tailor_floorB_tex, G_IM_FMT_CI, 64, 64, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_tailor_v[104], 28, 0),
    gsSPNTrianglesInit_5b(19,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 2, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(5, 8, 6,   // tri0
                      5, 9, 10,  // tri1
                      11, 12, 6, // tri2
                      13, 14, 15 // tri3
                      ),
    gsSPNTriangles_5b(14, 16, 15, // tri0
                      13, 17, 18, // tri1
                      16, 14, 18, // tri2
                      14, 13, 18  // tri3
                      ),
    gsSPNTriangles_5b(19, 16, 18, // tri0
                      20, 21, 22, // tri1
                      20, 23, 21, // tri2
                      24, 25, 22  // tri3
                      ),
    gsSPNTriangles_5b(24, 23, 26, // tri0
                      24, 21, 23, // tri1
                      24, 22, 21, // tri2
                      0, 2, 27    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tailor_floorA_tex, G_IM_FMT_CI, 64, 64, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_tailor_v[132], 26, 0),
    gsSPNTrianglesInit_5b(19,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          3, 0, 4  // tri2
                          ),
    gsSPNTriangles_5b(3, 1, 0, // tri0
                      3, 6, 1, // tri1
                      7, 8, 9, // tri2
                      8, 10, 9 // tri3
                      ),
    gsSPNTriangles_5b(9, 11, 12,  // tri0
                      13, 14, 15, // tri1
                      14, 16, 15, // tri2
                      17, 16, 18  // tri3
                      ),
    gsSPNTriangles_5b(13, 19, 18, // tri0
                      16, 14, 18, // tri1
                      14, 13, 18, // tri2
                      20, 21, 22  // tri3
                      ),
    gsSPNTriangles_5b(20, 23, 21, // tri0
                      23, 24, 21, // tri1
                      25, 23, 20, // tri2
                      4, 0, 2     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_tailor_table_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tailor_table_reji_tex, G_IM_FMT_CI, 16, 16, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_tailor_v[158], 16, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6, // tri0
                      2, 1, 5, // tri1
                      2, 5, 4, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tailor_table_ue_tex, G_IM_FMT_CI, 32, 16, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4,         // tri count
                          8, 9, 10,  // tri0
                          8, 10, 11, // tri1
                          12, 13, 14 // tri2
                          ),
    gsSPNTriangles_5b(12, 14, 15, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_tailor_reji_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tailor_reji_tex, G_IM_FMT_CI, 32, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_tailor_v[174], 16, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,   // tri0
                      7, 10, 8,  // tri1
                      4, 6, 11,  // tri2
                      12, 13, 14 // tri3
                      ),
    gsSPNTriangles_5b(13, 15, 14, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_tailor_dogu_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tailor_dogu2_tex, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_tailor_v[190], 18, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          3, 2, 4  // tri2
                          ),
    gsSPNTriangles_5b(3, 4, 5, // tri0
                      6, 5, 4, // tri1
                      6, 4, 7, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tailor_cloth1_tex, G_IM_FMT_CI, 16, 16, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPNTrianglesInit_5b(6,        // tri count
                          8, 9, 10, // tri0
                          8, 11, 9, // tri1
                          11, 12, 9 // tri2
                          ),
    gsSPNTriangles_5b(13, 14, 15, // tri0
                      13, 16, 14, // tri1
                      14, 17, 15, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_tailor_box_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tailor_box7_tex, G_IM_FMT_CI, 16, 16, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&rom_tailor_v[208], 30, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 1  // tri2
                          ),
    gsSPNTriangles_5b(4, 1, 0, // tri0
                      6, 7, 5, // tri1
                      6, 5, 4, // tri2
                      8, 9, 7  // tri3
                      ),
    gsSPNTriangles_5b(8, 7, 6, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tailor_box5_tex, G_IM_FMT_CI, 16, 16, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPNTrianglesInit_5b(8,          // tri count
                          10, 11, 12, // tri0
                          10, 12, 13, // tri1
                          14, 15, 11  // tri2
                          ),
    gsSPNTriangles_5b(14, 11, 10, // tri0
                      16, 17, 15, // tri1
                      16, 15, 14, // tri2
                      18, 19, 17  // tri3
                      ),
    gsSPNTriangles_5b(18, 17, 16, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tailor_box3_tex, G_IM_FMT_CI, 16, 16, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPNTrianglesInit_5b(8,          // tri count
                          20, 21, 22, // tri0
                          20, 22, 23, // tri1
                          23, 22, 24  // tri2
                          ),
    gsSPNTriangles_5b(23, 24, 25, // tri0
                      25, 24, 26, // tri1
                      25, 26, 27, // tri2
                      27, 26, 28  // tri3
                      ),
    gsSPNTriangles_5b(27, 28, 29, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tailor_box1_tex, G_IM_FMT_CI, 16, 16, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&rom_tailor_v[238], 10, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 1  // tri2
                          ),
    gsSPNTriangles_5b(4, 1, 0, // tri0
                      6, 7, 5, // tri1
                      6, 5, 4, // tri2
                      8, 9, 7  // tri3
                      ),
    gsSPNTriangles_5b(8, 7, 6, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_tailor_ent_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tailor_ent_tex, G_IM_FMT_CI, 32, 16, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_tailor_v[248], 26, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          2, 4, 0  // tri2
                          ),
    gsSPNTriangles_5b(0, 5, 3, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_tailor_mado_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tailor_pic7_tex, G_IM_FMT_CI, 32, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          6, 7, 8, // tri0
                          6, 9, 7, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tailor_pic4_tex, G_IM_FMT_CI, 32, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2,          // tri count
                          10, 11, 12, // tri0
                          10, 12, 13, // tri1
                          0, 0, 0     // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tailor_pic3_tex, G_IM_FMT_CI, 32, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2,          // tri count
                          14, 15, 16, // tri0
                          14, 17, 15, // tri1
                          0, 0, 0     // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tailor_pic2_tex, G_IM_FMT_CI, 32, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2,          // tri count
                          18, 19, 20, // tri0
                          18, 21, 19, // tri1
                          0, 0, 0     // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tailor_pic1_tex, G_IM_FMT_CI, 32, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2,          // tri count
                          22, 23, 24, // tri0
                          22, 25, 23, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_field_bg_acre_rom_tailor_rom_tailor_c(void) {
    pc_load_asset("assets/field/bg/rom_tailor_wall_pal.bin", rom_tailor_wall_pal, 0x20, 0xBB90A0, 0, 1);
    pc_load_asset("assets/field/bg/rom_tailor_floor_pal.bin", rom_tailor_floor_pal, 0x20, 0xBB90C0, 0, 1);
    pc_load_asset("assets/field/bg/rom_tailor_mado_pal.bin", rom_tailor_mado_pal, 0x20, 0xBB90E0, 0, 1);
    pc_load_asset("assets/field/bg/rom_tailor_reji_pal.bin", rom_tailor_reji_pal, 0x20, 0xBB9100, 0, 1);
    pc_load_asset("assets/field/bg/rom_tailor_dogu_pal.bin", rom_tailor_dogu_pal, 0x20, 0xBB9120, 0, 1);
    pc_load_asset("assets/field/bg/rom_tailor_misin_pal.bin", rom_tailor_misin_pal, 0x20, 0xBB9140, 0, 1);
    pc_load_asset("assets/field/bg/rom_tailor_table_pal.bin", rom_tailor_table_pal, 0x20, 0xBB9160, 0, 1);
    pc_load_asset("assets/field/bg/rom_tailor_box_pal.bin", rom_tailor_box_pal, 0x20, 0xBB9180, 0, 1);
    pc_load_asset("assets/field/bg/rom_tailor_quilt_pal.bin", rom_tailor_quilt_pal, 0x20, 0xBB91A0, 0, 1);
    pc_load_asset("assets/field/bg/rom_tailor_ent_pal.bin", rom_tailor_ent_pal, 0x20, 0xBB91C0, 0, 1);
    pc_load_asset("assets/field/bg/rom_tailor_wallA_tex.bin", rom_tailor_wallA_tex, 0x800, 0xBB91E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_tailor_wallB_tex.bin", rom_tailor_wallB_tex, 0x800, 0xBB99E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_tailor_floorA_tex.bin", rom_tailor_floorA_tex, 0x800, 0xBBA1E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_tailor_floorB_tex.bin", rom_tailor_floorB_tex, 0x800, 0xBBA9E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_tailor_floorC_tex.bin", rom_tailor_floorC_tex, 0x800, 0xBBB1E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_tailor_floorD_tex.bin", rom_tailor_floorD_tex, 0x800, 0xBBB9E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_tailor_kage1_tex.bin", rom_tailor_kage1_tex, 0x100, 0xBBC1E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_tailor_mado_tex.bin", rom_tailor_mado_tex, 0x200, 0xBBC2E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_tailor_pic1_tex.bin", rom_tailor_pic1_tex, 0x200, 0xBBC4E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_tailor_pic2_tex.bin", rom_tailor_pic2_tex, 0x200, 0xBBC6E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_tailor_pic3_tex.bin", rom_tailor_pic3_tex, 0x200, 0xBBC8E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_tailor_pic4_tex.bin", rom_tailor_pic4_tex, 0x200, 0xBBCAE0, 0, 0);
    pc_load_asset("assets/field/bg/rom_tailor_pic5_tex.bin", rom_tailor_pic5_tex, 0x200, 0xBBCCE0, 0, 0);
    pc_load_asset("assets/field/bg/rom_tailor_pic6_tex.bin", rom_tailor_pic6_tex, 0x200, 0xBBCEE0, 0, 0);
    pc_load_asset("assets/field/bg/rom_tailor_pic7_tex.bin", rom_tailor_pic7_tex, 0x200, 0xBBD0E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_tailor_pic8_tex.bin", rom_tailor_pic8_tex, 0x200, 0xBBD2E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_tailor_tyoki_tex.bin", rom_tailor_tyoki_tex, 0x100, 0xBBD4E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_tailor_cloth1_tex.bin", rom_tailor_cloth1_tex, 0x80, 0xBBD5E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_tailor_misin2_tex.bin", rom_tailor_misin2_tex, 0x200, 0xBBD660, 0, 0);
    pc_load_asset("assets/field/bg/rom_tailor_table_mae_tex.bin", rom_tailor_table_mae_tex, 0x100, 0xBBD860, 0, 0);
    pc_load_asset("assets/field/bg/rom_tailor_table_yoko_tex.bin", rom_tailor_table_yoko_tex, 0x80, 0xBBD960, 0, 0);
    pc_load_asset("assets/field/bg/rom_tailor_table_ue_tex.bin", rom_tailor_table_ue_tex, 0x100, 0xBBD9E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_tailor_ito_tex.bin", rom_tailor_ito_tex, 0x200, 0xBBDAE0, 0, 0);
    pc_load_asset("assets/field/bg/rom_tailor_table_reji_tex.bin", rom_tailor_table_reji_tex, 0x80, 0xBBDCE0, 0, 0);
    pc_load_asset("assets/field/bg/rom_tailor_misin1_tex.bin", rom_tailor_misin1_tex, 0x200, 0xBBDD60, 0, 0);
    pc_load_asset("assets/field/bg/rom_tailor_misindai_tex.bin", rom_tailor_misindai_tex, 0x200, 0xBBDF60, 0, 0);
    pc_load_asset("assets/field/bg/rom_tailor_table_misin1_tex.bin", rom_tailor_table_misin1_tex, 0x100, 0xBBE160, 0, 0);
    pc_load_asset("assets/field/bg/rom_tailor_reji_tex.bin", rom_tailor_reji_tex, 0x200, 0xBBE260, 0, 0);
    pc_load_asset("assets/field/bg/rom_tailor_table_misin2_tex.bin", rom_tailor_table_misin2_tex, 0x80, 0xBBE460, 0, 0);
    pc_load_asset("assets/field/bg/rom_tailor_box_tex.bin", rom_tailor_box_tex, 0x100, 0xBBE4E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_tailor_box1_tex.bin", rom_tailor_box1_tex, 0x80, 0xBBE5E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_tailor_box2_tex.bin", rom_tailor_box2_tex, 0x80, 0xBBE660, 0, 0);
    pc_load_asset("assets/field/bg/rom_tailor_box3_tex.bin", rom_tailor_box3_tex, 0x80, 0xBBE6E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_tailor_box4_tex.bin", rom_tailor_box4_tex, 0x80, 0xBBE760, 0, 0);
    pc_load_asset("assets/field/bg/rom_tailor_box5_tex.bin", rom_tailor_box5_tex, 0x80, 0xBBE7E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_tailor_box6_tex.bin", rom_tailor_box6_tex, 0x80, 0xBBE860, 0, 0);
    pc_load_asset("assets/field/bg/rom_tailor_box7_tex.bin", rom_tailor_box7_tex, 0x80, 0xBBE8E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_tailor_box8_tex.bin", rom_tailor_box8_tex, 0x80, 0xBBE960, 0, 0);
    pc_load_asset("assets/field/bg/rom_tailor_kage2_tex.bin", rom_tailor_kage2_tex, 0x80, 0xBBE9E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_tailor_quilt_tex.bin", rom_tailor_quilt_tex, 0x800, 0xBBEA60, 0, 0);
    pc_load_asset("assets/field/bg/rom_tailor_ent_tex.bin", rom_tailor_ent_tex, 0x100, 0xBBF260, 0, 0);
    pc_load_asset("assets/field/bg/rom_tailor_misinbari1_tex.bin", rom_tailor_misinbari1_tex, 0x80, 0xBBF360, 0, 0);
    pc_load_asset("assets/field/bg/rom_tailor_misinbari2_tex.bin", rom_tailor_misinbari2_tex, 0x80, 0xBBF3E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_tailor_tape_tex.bin", rom_tailor_tape_tex, 0x200, 0xBBF460, 0, 0);
    pc_load_asset("assets/field/bg/rom_tailor_dogu1_tex.bin", rom_tailor_dogu1_tex, 0x80, 0xBBF660, 0, 0);
    pc_load_asset("assets/field/bg/rom_tailor_dogu2_tex.bin", rom_tailor_dogu2_tex, 0x80, 0xBBF6E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_tailor_v.bin", rom_tailor_v, 0x1DE0, 0xBBF760, 0, 2);
}
#endif

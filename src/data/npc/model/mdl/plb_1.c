#include "c_keyframe.h"
#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
static Vtx plb_1_v[0x1A80 / sizeof(Vtx)];
#else
static Vtx plb_1_v[] = {
#include "assets/npc/mdl/plb_1_v.inc"
};
#endif

static Gfx head_plb_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x180, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&plb_1_v[40], 27, 0),
    gsSPNTrianglesInit_5b(3,       // tri count
                          0, 1, 2, // tri0
                          2, 3, 4, // tri1
                          4, 0, 2  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x200, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(20,       // tri count
                          5, 6, 7,  // tri0
                          8, 9, 10, // tri1
                          5, 11, 12 // tri2
                          ),
    gsSPNTriangles_5b(7, 11, 5,  // tri0
                      13, 14, 8, // tri1
                      15, 8, 16, // tri2
                      17, 12, 11 // tri3
                      ),
    gsSPNTriangles_5b(7, 13, 15, // tri0
                      14, 13, 7, // tri1
                      18, 9, 8,  // tri2
                      16, 19, 17 // tri3
                      ),
    gsSPNTriangles_5b(18, 14, 7,  // tri0
                      15, 17, 11, // tri1
                      8, 15, 13,  // tri2
                      19, 16, 10  // tri3
                      ),
    gsSPNTriangles_5b(10, 16, 8,  // tri0
                      16, 17, 15, // tri1
                      11, 7, 15,  // tri2
                      8, 14, 18   // tri3
                      ),
    gsSPNTriangles_5b(7, 6, 18, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x100, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(5,          // tri count
                          20, 21, 22, // tri0
                          20, 22, 23, // tri1
                          24, 25, 26  // tri2
                          ),
    gsSPNTriangles_5b(23, 22, 26, // tri0
                      23, 26, 25, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&plb_1_v[67], 28, 0),
    gsSPNTrianglesInit_5b(41,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(6, 9, 10,  // tri0
                      7, 11, 12, // tri1
                      7, 12, 3,  // tri2
                      7, 10, 11  // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 2,  // tri0
                      15, 16, 13, // tri1
                      13, 1, 17,  // tri2
                      12, 11, 18  // tri3
                      ),
    gsSPNTriangles_5b(12, 18, 19, // tri0
                      4, 12, 19,  // tri1
                      4, 16, 15,  // tri2
                      5, 4, 15    // tri3
                      ),
    gsSPNTriangles_5b(14, 20, 2,  // tri0
                      14, 18, 20, // tri1
                      20, 10, 9,  // tri2
                      13, 16, 14  // tri3
                      ),
    gsSPNTriangles_5b(14, 16, 19, // tri0
                      19, 18, 14, // tri1
                      2, 9, 0,    // tri2
                      1, 13, 2    // tri3
                      ),
    gsSPNTriangles_5b(21, 22, 23, // tri0
                      17, 15, 13, // tri1
                      2, 20, 9,   // tri2
                      12, 4, 3    // tri3
                      ),
    gsSPNTriangles_5b(10, 20, 18, // tri0
                      18, 11, 10, // tri1
                      19, 16, 4,  // tri2
                      3, 24, 23   // tri3
                      ),
    gsSPNTriangles_5b(21, 8, 7,   // tri0
                      23, 24, 25, // tri1
                      23, 25, 21, // tri2
                      7, 3, 22    // tri3
                      ),
    gsSPNTriangles_5b(22, 21, 7, // tri0
                      3, 23, 22, // tri1
                      24, 3, 5,  // tri2
                      8, 26, 6   // tri3
                      ),
    gsSPNTriangles_5b(5, 27, 24, // tri0
                      10, 7, 6,  // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_1_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&plb_1_v[95], 30, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 3  // tri2
                          ),
    gsSPNTriangles_5b(2, 7, 6, // tri0
                      8, 0, 2, // tri1
                      5, 9, 6, // tri2
                      6, 9, 10 // tri3
                      ),
    gsSPNTriangles_5b(10, 8, 2,  // tri0
                      3, 11, 12, // tri1
                      3, 12, 4,  // tri2
                      11, 3, 7   // tri3
                      ),
    gsSPNTriangles_5b(7, 2, 1,  // tri0
                      10, 2, 6, // tri1
                      6, 3, 5,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x2C0, G_IM_FMT_CI, 16, 16, 15, GX_MIRROR, GX_REPEAT, 0, 0),
    gsSPNTrianglesInit_5b(13,         // tri count
                          13, 14, 15, // tri0
                          16, 17, 18, // tri1
                          19, 20, 16  // tri2
                          ),
    gsSPNTriangles_5b(13, 21, 22, // tri0
                      16, 18, 19, // tri1
                      15, 23, 13, // tri2
                      24, 22, 21  // tri3
                      ),
    gsSPNTriangles_5b(25, 26, 27, // tri0
                      25, 24, 28, // tri1
                      13, 22, 14, // tri2
                      21, 28, 24  // tri3
                      ),
    gsSPNTriangles_5b(28, 26, 25, // tri0
                      27, 29, 25, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx mouth_plb_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*13, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&plb_1_v[0], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*12, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&plb_1_v[5], 15, 5),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 5, 6, // tri0
                          4, 8, 7, // tri1
                          2, 4, 9  // tri2
                          ),
    gsSPNTriangles_5b(4, 0, 10,  // tri0
                      2, 11, 12, // tri1
                      0, 13, 14, // tri2
                      2, 15, 16  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x100, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2,         // tri count
                          1, 3, 17,  // tri0
                          3, 19, 18, // tri1
                          0, 0, 0    // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&plb_1_v[20], 20, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          0, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(0, 8, 6,   // tri0
                      9, 10, 4,  // tri1
                      11, 10, 9, // tri2
                      12, 8, 10  // tri3
                      ),
    gsSPNTriangles_5b(12, 10, 11, // tri0
                      8, 0, 4,    // tri1
                      4, 10, 8,   // tri2
                      4, 0, 2     // tri3
                      ),
    gsSPNTriangles_5b(4, 2, 5,  // tri0
                      13, 9, 4, // tri1
                      6, 8, 12, // tri2
                      7, 1, 0   // tri3
                      ),
    gsSPNTriangles_5b(4, 3, 13, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x100, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4,          // tri count
                          14, 15, 16, // tri0
                          17, 15, 14, // tri1
                          17, 14, 18  // tri2
                          ),
    gsSPNTriangles_5b(14, 16, 19, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rarm2_plb_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&plb_1_v[168], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*11, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x340, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&plb_1_v[172], 25, 4),
    gsSPNTrianglesInit_5b(9,       // tri count
                          2, 4, 5, // tri0
                          1, 3, 6, // tri1
                          0, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(2, 0, 9,   // tri0
                      0, 10, 11, // tri1
                      1, 12, 13, // tri2
                      3, 2, 14   // tri3
                      ),
    gsSPNTriangles_5b(0, 1, 15,  // tri0
                      2, 16, 17, // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(3,          // tri count
                          18, 19, 20, // tri0
                          21, 19, 18, // tri1
                          22, 19, 21  // tri2
                          ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(4,          // tri count
                          23, 24, 25, // tri0
                          25, 26, 27, // tri1
                          24, 28, 25  // tri2
                          ),
    gsSPNTriangles_5b(25, 27, 23, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rarm1_plb_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&plb_1_v[197], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x340, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&plb_1_v[200], 11, 3),
    gsSPNTrianglesInit_5b(7,       // tri count
                          1, 3, 4, // tri0
                          2, 5, 6, // tri1
                          1, 2, 7  // tri2
                          ),
    gsSPNTriangles_5b(2, 8, 9,  // tri0
                      0, 1, 10, // tri1
                      2, 0, 11, // tri2
                      0, 12, 13 // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Larm2_plb_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&plb_1_v[125], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*9, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x340, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&plb_1_v[129], 25, 4),
    gsSPNTrianglesInit_5b(9,       // tri count
                          2, 4, 5, // tri0
                          3, 1, 6, // tri1
                          0, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(0, 2, 9,   // tri0
                      0, 10, 11, // tri1
                      1, 12, 13, // tri2
                      2, 3, 14   // tri3
                      ),
    gsSPNTriangles_5b(1, 0, 15,  // tri0
                      2, 16, 17, // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(3,          // tri count
                          18, 19, 20, // tri0
                          20, 19, 21, // tri1
                          21, 19, 22  // tri2
                          ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(4,          // tri count
                          23, 24, 25, // tri0
                          26, 27, 23, // tri1
                          23, 28, 24  // tri2
                          ),
    gsSPNTriangles_5b(25, 26, 23, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Larm1_plb_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&plb_1_v[154], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x340, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&plb_1_v[157], 11, 3),
    gsSPNTrianglesInit_5b(7,       // tri count
                          1, 3, 4, // tri0
                          2, 5, 6, // tri1
                          2, 1, 7  // tri2
                          ),
    gsSPNTriangles_5b(2, 8, 9,  // tri0
                      1, 0, 10, // tri1
                      0, 2, 11, // tri2
                      0, 12, 13 // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx chest_plb_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&plb_1_v[211], 13, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x480, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&plb_1_v[224], 6, 13),
    gsSPNTrianglesInit_5b(4,         // tri count
                          12, 9, 13, // tri0
                          9, 14, 15, // tri1
                          11, 10, 16 // tri2
                          ),
    gsSPNTriangles_5b(11, 17, 18, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x4C0, G_IM_FMT_CI, 32, 24, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&plb_1_v[230], 19, 13),
    gsSPNTrianglesInit_5b(13,        // tri count
                          2, 13, 3,  // tri0
                          8, 14, 15, // tri1
                          6, 8, 16   // tri2
                          ),
    gsSPNTriangles_5b(2, 1, 17,  // tri0
                      1, 0, 18,  // tri1
                      1, 20, 19, // tri2
                      0, 21, 22  // tri3
                      ),
    gsSPNTriangles_5b(0, 7, 23,  // tri0
                      4, 25, 24, // tri1
                      3, 26, 27, // tri2
                      4, 3, 28   // tri3
                      ),
    gsSPNTriangles_5b(8, 5, 29,  // tri0
                      8, 30, 31, // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&plb_1_v[249], 11, 13),
    gsSPNTrianglesInit_5b(1,        // tri count
                          5, 4, 13, // tri0
                          0, 0, 0,  // tri1
                          0, 0, 0   // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x480, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(8,          // tri count
                          14, 15, 16, // tri0
                          14, 16, 17, // tri1
                          18, 19, 20  // tri2
                          ),
    gsSPNTriangles_5b(15, 21, 22, // tri0
                      14, 17, 19, // tri1
                      19, 18, 14, // tri2
                      22, 16, 15  // tri3
                      ),
    gsSPNTriangles_5b(20, 23, 18, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x4C0, G_IM_FMT_CI, 32, 24, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&plb_1_v[260], 21, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(9, 10, 11, // tri0
                      12, 13, 5, // tri1
                      7, 13, 12, // tri2
                      12, 14, 7  // tri3
                      ),
    gsSPNTriangles_5b(5, 1, 12,  // tri0
                      12, 1, 0,  // tri1
                      12, 0, 14, // tri2
                      15, 14, 0  // tri3
                      ),
    gsSPNTriangles_5b(16, 4, 3,  // tri0
                      8, 17, 6,  // tri1
                      11, 10, 6, // tri2
                      6, 17, 11  // tri3
                      ),
    gsSPNTriangles_5b(11, 18, 9, // tri0
                      19, 0, 2,  // tri1
                      15, 0, 20, // tri2
                      14, 8, 7   // tri3
                      ),
    gsSPNTriangles_5b(5, 4, 1, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot3_plb_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&plb_1_v[328], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*6, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x640, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&plb_1_v[331], 18, 3),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 3, 4, // tri0
                          1, 0, 5, // tri1
                          0, 2, 6  // tri2
                          ),
    gsSPNTriangles_5b(2, 1, 7,   // tri0
                      2, 8, 9,   // tri1
                      0, 10, 11, // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(5,          // tri count
                          12, 13, 14, // tri0
                          12, 14, 15, // tri1
                          16, 17, 18  // tri2
                          ),
    gsSPNTriangles_5b(18, 19, 16, // tri0
                      16, 20, 17, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot2_plb_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*4, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&plb_1_v[349], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x640, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&plb_1_v[353], 14, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          3, 4, 5, // tri0
                          2, 6, 7, // tri1
                          3, 0, 8  // tri2
                          ),
    gsSPNTriangles_5b(1, 2, 9,   // tri0
                      2, 10, 11, // tri1
                      2, 3, 12,  // tri2
                      3, 13, 14  // tri3
                      ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          15, 16, 17, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot1_plb_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x640, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&plb_1_v[367], 8, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          3, 2, 4  // tri2
                          ),
    gsSPNTriangles_5b(5, 0, 6, // tri0
                      4, 7, 3, // tri1
                      0, 5, 1, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot3_plb_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&plb_1_v[281], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x640, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&plb_1_v[284], 18, 3),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 3, 4, // tri0
                          0, 1, 5, // tri1
                          2, 0, 6  // tri2
                          ),
    gsSPNTriangles_5b(1, 7, 8,   // tri0
                      1, 2, 9,   // tri1
                      0, 10, 11, // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(5,          // tri count
                          12, 13, 14, // tri0
                          12, 14, 15, // tri1
                          16, 17, 18  // tri2
                          ),
    gsSPNTriangles_5b(18, 19, 16, // tri0
                      17, 20, 18, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot2_plb_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&plb_1_v[302], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x640, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&plb_1_v[306], 14, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          3, 4, 5, // tri0
                          2, 6, 7, // tri1
                          0, 3, 8  // tri2
                          ),
    gsSPNTriangles_5b(2, 1, 9,   // tri0
                      2, 10, 11, // tri1
                      3, 2, 12,  // tri2
                      3, 13, 14  // tri3
                      ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          15, 16, 17, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot1_plb_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x640, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&plb_1_v[320], 8, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 1, 0  // tri2
                          ),
    gsSPNTriangles_5b(5, 3, 6, // tri0
                      0, 7, 4, // tri1
                      2, 6, 3, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx base_plb_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&plb_1_v[375], 31, 0),
    gsSPNTrianglesInit_5b(26,      // tri count
                          0, 1, 2, // tri0
                          2, 1, 3, // tri1
                          4, 0, 2  // tri2
                          ),
    gsSPNTriangles_5b(3, 1, 5,   // tri0
                      6, 7, 8,   // tri1
                      9, 10, 11, // tri2
                      12, 13, 14 // tri3
                      ),
    gsSPNTriangles_5b(12, 14, 15, // tri0
                      13, 8, 14,  // tri1
                      12, 15, 16, // tri2
                      9, 17, 18   // tri3
                      ),
    gsSPNTriangles_5b(19, 20, 21, // tri0
                      1, 0, 22,   // tri1
                      23, 24, 25, // tri2
                      22, 0, 26   // tri3
                      ),
    gsSPNTriangles_5b(12, 22, 26, // tri0
                      0, 6, 26,   // tri1
                      12, 26, 13, // tri2
                      23, 25, 27  // tri3
                      ),
    gsSPNTriangles_5b(27, 28, 23, // tri0
                      6, 0, 4,    // tri1
                      8, 13, 6,   // tri2
                      13, 26, 6   // tri3
                      ),
    gsSPNTriangles_5b(4, 7, 6,   // tri0
                      5, 20, 29, // tri1
                      20, 5, 30, // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x680, G_IM_FMT_CI, 16, 8, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&plb_1_v[406], 18, 0),
    gsSPNTrianglesInit_5b(13,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 4, // tri1
                          1, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7,   // tri0
                      5, 7, 8,   // tri1
                      9, 10, 11, // tri2
                      9, 11, 12  // tri3
                      ),
    gsSPNTriangles_5b(7, 2, 4,  // tri0
                      7, 4, 8,  // tri1
                      12, 6, 5, // tri2
                      12, 5, 9  // tri3
                      ),
    gsSPNTriangles_5b(7, 6, 0, // tri0
                      2, 7, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x6C0, G_IM_FMT_CI, 16, 24, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3,          // tri count
                          13, 14, 15, // tri0
                          13, 15, 16, // tri1
                          16, 17, 13  // tri2
                          ),
    gsSPEndDisplayList(),
};

// clang-format off
static cKF_Joint_R_c cKF_je_r_plb_1_tbl[] = {
    /* joint 0 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,1000,0 },
    /* joint 1 */ { base_plb_model, 4, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 2 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,-250,0 },
    /* joint 3 */ { Lfoot1_plb_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 4 */ { Lfoot2_plb_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 5 */ { Lfoot3_plb_model, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 6 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,250,0 },
    /* joint 7 */ { Rfoot1_plb_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 8 */ { Rfoot2_plb_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 9 */ { Rfoot3_plb_model, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 10 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 75,0,-650 },
    /* joint 11 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 12 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 650,0,0 },
    /* joint 13 */ { chest_plb_model, 3, cKF_JOINT_FLAG_DISP_OPA, 325,0,0 },
    /* joint 14 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 1150,-500,0 },
    /* joint 15 */ { Larm1_plb_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 16 */ { Larm2_plb_model, 0, cKF_JOINT_FLAG_DISP_OPA, 1000,0,0 },
    /* joint 17 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 1150,500,0 },
    /* joint 18 */ { Rarm1_plb_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 19 */ { Rarm2_plb_model, 1, cKF_JOINT_FLAG_DISP_OPA, 998,0,0 },
    /* joint 20 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 1000,0,0 },
    /* joint 21 */ { NULL, 2, cKF_JOINT_FLAG_DISP_OPA, 1274,0,0 },
    /* joint 22 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 1050,0,1350 },
    /* joint 23 */ { mouth_plb_model, 0, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 24 */ { head_plb_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 25 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 1601,0,0 },
};
// clang-format on

extern cKF_Skeleton_R_c cKF_bs_r_plb_1 = { 26, 14, cKF_je_r_plb_1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_npc_model_mdl_plb_1_c(void) {
    pc_load_asset("assets/npc/mdl/plb_1_v.bin", plb_1_v, 0x1A80, 0x635240, 0, 2);
}
#endif

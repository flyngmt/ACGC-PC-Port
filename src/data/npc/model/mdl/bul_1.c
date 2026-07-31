#include "c_keyframe.h"
#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
static Vtx bul_1_v[0x1680 / sizeof(Vtx)];
#else
static Vtx bul_1_v[] = {
#include "assets/npc/mdl/bul_1_v.inc"
};
#endif

static Gfx head_bul_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bul_1_v[0], 19, 0),
    gsSPNTrianglesInit_5b(24,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 9, 10,   // tri0
                      11, 12, 13, // tri1
                      3, 7, 9,    // tri2
                      14, 15, 2   // tri3
                      ),
    gsSPNTriangles_5b(16, 15, 10, // tri0
                      8, 3, 9,    // tri1
                      5, 7, 3,    // tri2
                      8, 14, 17   // tri3
                      ),
    gsSPNTriangles_5b(14, 8, 15, // tri0
                      17, 5, 4,  // tri1
                      8, 4, 3,   // tri2
                      10, 15, 8  // tri3
                      ),
    gsSPNTriangles_5b(0, 18, 1,  // tri0
                      1, 14, 2,  // tri1
                      13, 12, 5, // tri2
                      13, 5, 17  // tri3
                      ),
    gsSPNTriangles_5b(17, 4, 8,   // tri0
                      13, 17, 14, // tri1
                      11, 13, 1,  // tri2
                      1, 18, 11   // tri3
                      ),
    gsSPNTriangles_5b(14, 1, 13, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&bul_1_v[19], 27, 0),
    gsSPNTrianglesInit_5b(24,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 3  // tri2
                          ),
    gsSPNTriangles_5b(8, 9, 10,   // tri0
                      11, 12, 13, // tri1
                      9, 6, 5,    // tri2
                      0, 14, 15   // tri3
                      ),
    gsSPNTriangles_5b(8, 14, 16, // tri0
                      9, 5, 10,  // tri1
                      5, 6, 3,   // tri2
                      17, 15, 10 // tri3
                      ),
    gsSPNTriangles_5b(14, 10, 15, // tri0
                      4, 3, 17,   // tri1
                      5, 4, 10,   // tri2
                      10, 14, 8   // tri3
                      ),
    gsSPNTriangles_5b(1, 18, 2,  // tri0
                      0, 15, 1,  // tri1
                      17, 3, 12, // tri2
                      17, 12, 11 // tri3
                      ),
    gsSPNTriangles_5b(10, 4, 17,  // tri0
                      15, 17, 11, // tri1
                      1, 11, 13,  // tri2
                      13, 18, 1   // tri3
                      ),
    gsSPNTriangles_5b(11, 1, 15, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x080, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(5,          // tri count
                          19, 20, 21, // tri0
                          22, 23, 24, // tri1
                          21, 25, 19  // tri2
                          ),
    gsSPNTriangles_5b(26, 22, 24, // tri0
                      24, 25, 26, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPSetPrimColor(0, 128, 253, 255, 255, 255),
    gsSPVertex(&bul_1_v[46], 21, 0),
    gsSPNTrianglesInit_5b(5,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          5, 0, 3  // tri2
                          ),
    gsSPNTriangles_5b(1, 6, 2, // tri0
                      1, 7, 6, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_2_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPNTrianglesInit_5b(14,       // tri count
                          8, 9, 10, // tri0
                          9, 8, 11, // tri1
                          12, 11, 8 // tri2
                          ),
    gsSPNTriangles_5b(13, 14, 15, // tri0
                      16, 10, 9,  // tri1
                      10, 14, 8,  // tri2
                      17, 13, 18  // tri3
                      ),
    gsSPNTriangles_5b(15, 18, 13, // tri0
                      14, 13, 19, // tri1
                      13, 17, 12, // tri2
                      19, 8, 14   // tri3
                      ),
    gsSPNTriangles_5b(18, 15, 20, // tri0
                      12, 19, 13, // tri1
                      8, 19, 12,  // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x100, G_IM_FMT_CI, 16, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&bul_1_v[67], 26, 0),
    gsSPNTrianglesInit_5b(36,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(9, 3, 10,   // tri0
                      10, 11, 12, // tri1
                      8, 7, 13,   // tri2
                      9, 12, 14   // tri3
                      ),
    gsSPNTriangles_5b(15, 14, 16, // tri0
                      12, 17, 14, // tri1
                      14, 17, 16, // tri2
                      16, 18, 15  // tri3
                      ),
    gsSPNTriangles_5b(18, 19, 7, // tri0
                      6, 15, 18, // tri1
                      20, 9, 15, // tri2
                      14, 15, 9  // tri3
                      ),
    gsSPNTriangles_5b(18, 7, 6,  // tri0
                      21, 1, 22, // tri1
                      21, 4, 3,  // tri2
                      3, 9, 20   // tri3
                      ),
    gsSPNTriangles_5b(15, 6, 20, // tri0
                      10, 12, 9, // tri1
                      20, 23, 3, // tri2
                      2, 23, 20  // tri3
                      ),
    gsSPNTriangles_5b(8, 2, 6,    // tri0
                      5, 24, 10,  // tri1
                      16, 19, 18, // tri2
                      22, 1, 0    // tri3
                      ),
    gsSPNTriangles_5b(5, 4, 22, // tri0
                      8, 25, 0, // tri1
                      2, 1, 21, // tri2
                      5, 10, 3  // tri3
                      ),
    gsSPNTriangles_5b(3, 23, 21, // tri0
                      21, 23, 2, // tri1
                      2, 8, 0,   // tri2
                      20, 6, 2   // tri3
                      ),
    gsSPNTriangles_5b(22, 4, 21, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x200, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&bul_1_v[93], 26, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 4, 7  // tri2
                          ),
    gsSPNTriangles_5b(3, 8, 4,   // tri0
                      9, 10, 11, // tri1
                      2, 6, 7,   // tri2
                      1, 6, 2    // tri3
                      ),
    gsSPNTriangles_5b(9, 3, 10, // tri0
                      8, 3, 9,  // tri1
                      5, 4, 6,  // tri2
                      4, 8, 12  // tri3
                      ),
    gsSPNTriangles_5b(12, 7, 4, // tri0
                      5, 10, 3, // tri1
                      6, 1, 5,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_1_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(14,         // tri count
                          13, 14, 15, // tri0
                          16, 17, 14, // tri1
                          18, 19, 20  // tri2
                          ),
    gsSPNTriangles_5b(21, 22, 15, // tri0
                      23, 21, 14, // tri1
                      23, 14, 17, // tri2
                      15, 14, 21  // tri3
                      ),
    gsSPNTriangles_5b(20, 23, 17, // tri0
                      20, 17, 24, // tri1
                      20, 24, 18, // tri2
                      16, 14, 13  // tri3
                      ),
    gsSPNTriangles_5b(16, 24, 17, // tri0
                      25, 24, 16, // tri1
                      18, 24, 25, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rarm2_bul_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bul_1_v[155], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*11, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&bul_1_v[160], 16, 5),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 5, 6, // tri0
                          4, 7, 8, // tri1
                          4, 9, 10 // tri2
                          ),
    gsSPNTriangles_5b(0, 1, 11,  // tri0
                      2, 4, 12,  // tri1
                      0, 13, 14, // tri2
                      3, 0, 15   // tri3
                      ),
    gsSPNTriangles_5b(4, 3, 16, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPNTrianglesInit_5b(2,          // tri count
                          17, 18, 19, // tri0
                          20, 19, 18, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rarm1_bul_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bul_1_v[176], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&bul_1_v[180], 11, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          3, 4, 5, // tri0
                          0, 6, 7, // tri1
                          2, 0, 8  // tri2
                          ),
    gsSPNTriangles_5b(3, 2, 9,   // tri0
                      2, 11, 10, // tri1
                      3, 13, 12, // tri2
                      1, 3, 14   // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Larm2_bul_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bul_1_v[119], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*9, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&bul_1_v[124], 16, 5),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 5, 6, // tri0
                          4, 7, 8, // tri1
                          4, 9, 10 // tri2
                          ),
    gsSPNTriangles_5b(1, 0, 11,  // tri0
                      4, 2, 12,  // tri1
                      0, 13, 14, // tri2
                      0, 3, 15   // tri3
                      ),
    gsSPNTriangles_5b(3, 4, 16, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPNTrianglesInit_5b(2,          // tri count
                          17, 18, 19, // tri0
                          18, 17, 20, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Larm1_bul_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bul_1_v[140], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&bul_1_v[144], 11, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          3, 4, 5, // tri0
                          0, 6, 7, // tri1
                          0, 2, 8  // tri2
                          ),
    gsSPNTriangles_5b(2, 3, 9,   // tri0
                      2, 11, 10, // tri1
                      3, 13, 12, // tri2
                      3, 1, 14   // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx chest_bul_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bul_1_v[191], 7, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_3_txt, G_IM_FMT_CI, 32, 32, 14, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&bul_1_v[198], 20, 7),
    gsSPNTrianglesInit_5b(13,       // tri count
                          0, 2, 7,  // tri0
                          6, 8, 9,  // tri1
                          0, 10, 11 // tri2
                          ),
    gsSPNTriangles_5b(1, 12, 5,  // tri0
                      1, 13, 14, // tri1
                      2, 16, 15, // tri2
                      5, 17, 18  // tri3
                      ),
    gsSPNTriangles_5b(5, 19, 20, // tri0
                      2, 21, 22, // tri1
                      6, 0, 23,  // tri2
                      1, 6, 24   // tri3
                      ),
    gsSPNTriangles_5b(3, 5, 25, // tri0
                      4, 26, 2, // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPVertex(&bul_1_v[218], 10, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          0, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(5, 4, 8, // tri0
                      2, 6, 0, // tri1
                      1, 9, 2, // tri2
                      7, 4, 3  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx tail1_bul_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bul_1_v[242], 8, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          1, 0, 4  // tri2
                          ),
    gsSPNTriangles_5b(4, 3, 1, // tri0
                      0, 2, 6, // tri1
                      7, 5, 6, // tri2
                      6, 2, 7  // tri3
                      ),
    gsSPNTriangles_5b(5, 7, 3, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx tail2_bul_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bul_1_v[228], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*6, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&bul_1_v[232], 10, 4),
    gsSPNTrianglesInit_5b(4,       // tri count
                          2, 1, 4, // tri0
                          3, 2, 5, // tri1
                          0, 3, 6  // tri2
                          ),
    gsSPNTriangles_5b(1, 0, 7, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPNTrianglesInit_5b(8,         // tri count
                          8, 9, 10,  // tri0
                          11, 9, 12, // tri1
                          12, 9, 8   // tri2
                          ),
    gsSPNTriangles_5b(10, 9, 11,  // tri0
                      10, 11, 13, // tri1
                      13, 11, 12, // tri2
                      13, 8, 10   // tri3
                      ),
    gsSPNTriangles_5b(12, 8, 13, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot2_bul_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bul_1_v[290], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*4, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&bul_1_v[295], 16, 5),
    gsSPNTrianglesInit_5b(7,       // tri count
                          2, 3, 5, // tri0
                          0, 2, 6, // tri1
                          3, 8, 7  // tri2
                          ),
    gsSPNTriangles_5b(1, 10, 9,  // tri0
                      4, 1, 11,  // tri1
                      2, 12, 13, // tri2
                      3, 4, 14   // tri3
                      ),
    gsSPNTrianglesInit_5b(3,          // tri count
                          15, 16, 17, // tri0
                          17, 18, 19, // tri1
                          15, 20, 16  // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot1_bul_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bul_1_v[311], 6, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&bul_1_v[317], 13, 6),
    gsSPNTrianglesInit_5b(9,       // tri count
                          0, 6, 7, // tri0
                          2, 5, 8, // tri1
                          5, 9, 10 // tri2
                          ),
    gsSPNTriangles_5b(5, 1, 11, // tri0
                      0, 3, 12, // tri1
                      4, 2, 13, // tri2
                      3, 4, 14  // tri3
                      ),
    gsSPNTriangles_5b(3, 15, 16, // tri0
                      2, 17, 18, // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot2_bul_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bul_1_v[250], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&bul_1_v[255], 16, 5),
    gsSPNTrianglesInit_5b(7,       // tri count
                          3, 2, 5, // tri0
                          2, 0, 6, // tri1
                          3, 8, 7  // tri2
                          ),
    gsSPNTriangles_5b(1, 10, 9,  // tri0
                      1, 4, 11,  // tri1
                      2, 12, 13, // tri2
                      4, 3, 14   // tri3
                      ),
    gsSPNTrianglesInit_5b(3,          // tri count
                          15, 16, 17, // tri0
                          18, 19, 15, // tri1
                          16, 20, 17  // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot1_bul_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bul_1_v[271], 6, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&bul_1_v[277], 13, 6),
    gsSPNTrianglesInit_5b(9,       // tri count
                          4, 6, 7, // tri0
                          3, 1, 8, // tri1
                          3, 9, 10 // tri2
                          ),
    gsSPNTriangles_5b(5, 3, 11, // tri0
                      2, 4, 12, // tri1
                      1, 0, 13, // tri2
                      0, 2, 14  // tri3
                      ),
    gsSPNTriangles_5b(2, 15, 16, // tri0
                      1, 17, 18, // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx base_bul_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 16, 16, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bul_1_v[330], 30, 0),
    gsSPNTrianglesInit_5b(3,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          2, 1, 6  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_3_txt, G_IM_FMT_CI, 32, 32, 14, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPNTrianglesInit_5b(14,         // tri count
                          7, 8, 9,    // tri0
                          10, 11, 12, // tri1
                          13, 14, 15  // tri2
                          ),
    gsSPNTriangles_5b(16, 17, 18, // tri0
                      9, 19, 7,   // tri1
                      20, 11, 21, // tri2
                      20, 21, 17  // tri3
                      ),
    gsSPNTriangles_5b(12, 15, 14, // tri0
                      11, 20, 12, // tri1
                      8, 7, 13,   // tri2
                      13, 15, 8   // tri3
                      ),
    gsSPNTriangles_5b(21, 18, 17, // tri0
                      14, 10, 12, // tri1
                      18, 22, 16, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3,          // tri count
                          23, 24, 25, // tri0
                          26, 27, 28, // tri1
                          29, 24, 23  // tri2
                          ),
    gsSPEndDisplayList(),
};

// clang-format off
static cKF_Joint_R_c cKF_je_r_bul_1_tbl[] = {
    /* joint 0 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,1000,0 },
    /* joint 1 */ { base_bul_model, 4, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 2 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,-250,0 },
    /* joint 3 */ { Lfoot1_bul_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 4 */ { Lfoot2_bul_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 5 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 6 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,250,0 },
    /* joint 7 */ { Rfoot1_bul_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 8 */ { Rfoot2_bul_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 9 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 10 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 75,0,-475 },
    /* joint 11 */ { tail1_bul_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 12 */ { tail2_bul_model, 0, cKF_JOINT_FLAG_DISP_OPA, 650,0,0 },
    /* joint 13 */ { chest_bul_model, 3, cKF_JOINT_FLAG_DISP_OPA, 325,0,0 },
    /* joint 14 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 425,-450,0 },
    /* joint 15 */ { Larm1_bul_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 16 */ { Larm2_bul_model, 0, cKF_JOINT_FLAG_DISP_OPA, 350,0,0 },
    /* joint 17 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 425,450,0 },
    /* joint 18 */ { Rarm1_bul_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 19 */ { Rarm2_bul_model, 1, cKF_JOINT_FLAG_DISP_OPA, 350,0,0 },
    /* joint 20 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 350,0,0 },
    /* joint 21 */ { NULL, 2, cKF_JOINT_FLAG_DISP_OPA, 675,0,0 },
    /* joint 22 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,600 },
    /* joint 23 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 24 */ { head_bul_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 25 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 1600,0,0 },
};
// clang-format on

extern cKF_Skeleton_R_c cKF_bs_r_bul_1 = { 26, 13, cKF_je_r_bul_1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_npc_model_mdl_bul_1_c(void) {
    pc_load_asset("assets/npc/mdl/bul_1_v.bin", bul_1_v, 0x1680, 0x468E00, 0, 2);
}
#endif

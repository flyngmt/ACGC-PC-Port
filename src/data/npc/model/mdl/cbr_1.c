#include "c_keyframe.h"
#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
static Vtx cbr_1_v[0x15A0 / sizeof(Vtx)];
#else
static Vtx cbr_1_v[] = {
#include "assets/npc/mdl/cbr_1_v.inc"
};
#endif

static Gfx head_cbr_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&cbr_1_v[0], 30, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          3, 2, 4, // tri1
                          3, 4, 5  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7, // tri0
                      7, 3, 5, // tri1
                      3, 7, 0, // tri2
                      0, 2, 3  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_2_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(30,        // tri count
                          8, 9, 10,  // tri0
                          11, 12, 8, // tri1
                          13, 14, 15 // tri2
                          ),
    gsSPNTriangles_5b(16, 17, 10, // tri0
                      17, 11, 8,  // tri1
                      12, 13, 9,  // tri2
                      8, 12, 9    // tri3
                      ),
    gsSPNTriangles_5b(16, 18, 19, // tri0
                      18, 9, 15,  // tri1
                      20, 21, 22, // tri2
                      20, 23, 24  // tri3
                      ),
    gsSPNTriangles_5b(24, 25, 17, // tri0
                      26, 11, 27, // tri1
                      24, 23, 25, // tri2
                      25, 27, 11  // tri3
                      ),
    gsSPNTriangles_5b(28, 23, 22, // tri0
                      16, 20, 24, // tri1
                      25, 11, 17, // tri2
                      23, 28, 27  // tri3
                      ),
    gsSPNTriangles_5b(23, 27, 25, // tri0
                      21, 20, 16, // tri1
                      22, 23, 20, // tri2
                      22, 29, 28  // tri3
                      ),
    gsSPNTriangles_5b(15, 9, 13,  // tri0
                      24, 17, 16, // tri1
                      10, 18, 16, // tri2
                      15, 19, 18  // tri3
                      ),
    gsSPNTriangles_5b(10, 9, 18,  // tri0
                      17, 8, 10,  // tri1
                      12, 11, 26, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x040, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&cbr_1_v[30], 10, 0),
    gsSPNTrianglesInit_5b(3,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          3, 4, 0  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x080, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3,       // tri count
                          5, 6, 7, // tri0
                          5, 7, 8, // tri1
                          8, 9, 5  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x0C0, G_IM_FMT_CI, 32, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&cbr_1_v[40], 32, 0),
    gsSPNTrianglesInit_5b(42,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          3, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,    // tri0
                      10, 11, 4,  // tri1
                      12, 13, 14, // tri2
                      15, 16, 14  // tri3
                      ),
    gsSPNTriangles_5b(1, 0, 17,   // tri0
                      11, 10, 18, // tri1
                      5, 15, 19,  // tri2
                      20, 7, 21   // tri3
                      ),
    gsSPNTriangles_5b(22, 19, 15, // tri0
                      4, 20, 5,   // tri1
                      12, 21, 9,  // tri2
                      6, 19, 23   // tri3
                      ),
    gsSPNTriangles_5b(15, 5, 20, // tri0
                      2, 1, 24,  // tri1
                      23, 10, 3, // tri2
                      17, 4, 11  // tri3
                      ),
    gsSPNTriangles_5b(9, 8, 25,  // tri0
                      17, 0, 7,  // tri1
                      24, 1, 26, // tri2
                      14, 27, 15 // tri3
                      ),
    gsSPNTriangles_5b(15, 27, 22, // tri0
                      20, 16, 15, // tri1
                      21, 16, 20, // tri2
                      9, 21, 7    // tri3
                      ),
    gsSPNTriangles_5b(19, 22, 23, // tri0
                      23, 18, 10, // tri1
                      3, 6, 23,   // tri2
                      28, 26, 11  // tri3
                      ),
    gsSPNTriangles_5b(17, 7, 20, // tri0
                      0, 2, 8,   // tri1
                      4, 17, 20, // tri2
                      25, 2, 29  // tri3
                      ),
    gsSPNTriangles_5b(30, 9, 25, // tri0
                      19, 6, 5,  // tri1
                      4, 3, 10,  // tri2
                      16, 21, 12 // tri3
                      ),
    gsSPNTriangles_5b(12, 14, 16, // tri0
                      28, 31, 24, // tri1
                      24, 26, 28, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&cbr_1_v[72], 20, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          3, 1, 0, // tri1
                          0, 4, 5  // tri2
                          ),
    gsSPNTriangles_5b(5, 4, 6,   // tri0
                      7, 8, 9,   // tri1
                      8, 10, 11, // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x2C0, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(7,          // tri count
                          12, 13, 14, // tri0
                          15, 12, 16, // tri1
                          17, 15, 16  // tri2
                          ),
    gsSPNTriangles_5b(18, 19, 17, // tri0
                      14, 18, 16, // tri1
                      16, 12, 14, // tri2
                      17, 16, 18  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_1_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&cbr_1_v[92], 20, 0),
    gsSPNTrianglesInit_5b(26,      // tri count
                          0, 1, 2, // tri0
                          3, 2, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 9, 5,   // tri0
                      10, 3, 11, // tri1
                      6, 11, 12, // tri2
                      13, 14, 15 // tri3
                      ),
    gsSPNTriangles_5b(10, 6, 5,  // tri0
                      3, 16, 17, // tri1
                      12, 7, 6,  // tri2
                      14, 13, 9  // tri3
                      ),
    gsSPNTriangles_5b(13, 2, 18, // tri0
                      9, 8, 14,  // tri1
                      2, 1, 4,   // tri2
                      18, 9, 13  // tri3
                      ),
    gsSPNTriangles_5b(4, 16, 3,  // tri0
                      11, 6, 10, // tri1
                      17, 11, 3, // tri2
                      11, 17, 19 // tri3
                      ),
    gsSPNTriangles_5b(2, 13, 0,  // tri0
                      15, 0, 13, // tri1
                      3, 10, 18, // tri2
                      5, 18, 10  // tri3
                      ),
    gsSPNTriangles_5b(5, 9, 18,   // tri0
                      3, 18, 2,   // tri1
                      19, 12, 11, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rarm2_cbr_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*9, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&cbr_1_v[112], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 16, 16, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTileSize(0, 0, 0, 124, 60),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&cbr_1_v[116], 16, 4),
    gsSPNTrianglesInit_5b(8,       // tri count
                          2, 0, 4, // tri0
                          0, 5, 6, // tri1
                          0, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(3, 9, 10,  // tri0
                      3, 11, 12, // tri1
                      0, 1, 13,  // tri2
                      1, 3, 14   // tri3
                      ),
    gsSPNTriangles_5b(3, 2, 15, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPNTrianglesInit_5b(2,          // tri count
                          16, 17, 18, // tri0
                          19, 18, 17, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rarm1_cbr_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*6, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&cbr_1_v[132], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*9, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 16, 16, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTileSize(0, 0, 0, 124, 60),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&cbr_1_v[136], 12, 4),
    gsSPNTrianglesInit_5b(8,       // tri count
                          3, 5, 4, // tri0
                          1, 7, 6, // tri1
                          3, 8, 1  // tri2
                          ),
    gsSPNTriangles_5b(0, 1, 9,   // tri0
                      2, 10, 11, // tri1
                      3, 2, 12,  // tri2
                      0, 13, 2   // tri3
                      ),
    gsSPNTriangles_5b(0, 14, 15, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Larm2_cbr_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&cbr_1_v[200], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 16, 16, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTileSize(0, 0, 0, 124, 60),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&cbr_1_v[204], 16, 4),
    gsSPNTrianglesInit_5b(8,       // tri count
                          2, 3, 4, // tri0
                          0, 2, 5, // tri1
                          0, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(3, 1, 8,   // tri0
                      0, 9, 10,  // tri1
                      3, 11, 12, // tri2
                      1, 0, 13   // tri3
                      ),
    gsSPNTriangles_5b(3, 14, 15, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(2,          // tri count
                          16, 17, 18, // tri0
                          17, 16, 19, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Larm1_cbr_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*6, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&cbr_1_v[220], 6, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 16, 16, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTileSize(0, 0, 0, 124, 60),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&cbr_1_v[226], 12, 6),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 6, 7, // tri0
                          2, 8, 5, // tri1
                          2, 10, 9 // tri2
                          ),
    gsSPNTriangles_5b(5, 12, 11, // tri0
                      3, 13, 1,  // tri1
                      5, 14, 4,  // tri2
                      4, 15, 16  // tri3
                      ),
    gsSPNTriangles_5b(2, 0, 17, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx chest_cbr_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&cbr_1_v[148], 9, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*6, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_3_txt, G_IM_FMT_CI, 32, 32, 14, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTileSize(0, 0, 0, 252, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&cbr_1_v[157], 22, 9),
    gsSPNTrianglesInit_5b(15,       // tri count
                          7, 0, 9,  // tri0
                          1, 4, 10, // tri1
                          6, 7, 11  // tri2
                          ),
    gsSPNTriangles_5b(4, 13, 12, // tri0
                      3, 15, 14, // tri1
                      0, 2, 16,  // tri2
                      5, 17, 18  // tri3
                      ),
    gsSPNTriangles_5b(2, 19, 20, // tri0
                      5, 6, 21,  // tri1
                      6, 22, 23, // tri2
                      3, 5, 24   // tri3
                      ),
    gsSPNTriangles_5b(0, 25, 26, // tri0
                      4, 8, 27,  // tri1
                      8, 3, 28,  // tri2
                      8, 29, 30  // tri3
                      ),
    gsSPVertex(&cbr_1_v[179], 21, 9),
    gsSPNTrianglesInit_5b(2,         // tri count
                          7, 9, 10,  // tri0
                          7, 11, 12, // tri1
                          0, 0, 0    // tri2
                          ),
    gsSPNTrianglesInit_5b(15,         // tri count
                          13, 14, 15, // tri0
                          14, 13, 16, // tri1
                          17, 18, 19  // tri2
                          ),
    gsSPNTriangles_5b(20, 16, 13, // tri0
                      21, 22, 17, // tri1
                      20, 23, 16, // tri2
                      24, 23, 20  // tri3
                      ),
    gsSPNTriangles_5b(25, 19, 18, // tri0
                      23, 18, 16, // tri1
                      22, 21, 26, // tri2
                      18, 17, 16  // tri3
                      ),
    gsSPNTriangles_5b(22, 27, 28, // tri0
                      17, 22, 16, // tri1
                      19, 29, 17, // tri2
                      17, 29, 21  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx tail1_cbr_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsDPSetTileSize(0, 0, 0, 60, 60),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&cbr_1_v[306], 6, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          1, 0, 3, // tri1
                          4, 0, 2  // tri2
                          ),
    gsSPNTriangles_5b(0, 4, 3, // tri0
                      1, 5, 2, // tri1
                      5, 1, 3, // tri2
                      5, 4, 2  // tri3
                      ),
    gsSPNTriangles_5b(4, 5, 3, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot2_cbr_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&cbr_1_v[272], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*4, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 16, 16, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTileSize(0, 0, 0, 124, 60),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&cbr_1_v[277], 19, 5),
    gsSPNTrianglesInit_5b(8,       // tri count
                          2, 5, 3, // tri0
                          1, 0, 6, // tri1
                          3, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(1, 9, 10,  // tri0
                      3, 11, 12, // tri1
                      4, 13, 0,  // tri2
                      1, 15, 14  // tri3
                      ),
    gsSPNTriangles_5b(2, 1, 16, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPNTrianglesInit_5b(4,          // tri count
                          17, 18, 19, // tri0
                          20, 19, 18, // tri1
                          21, 22, 20  // tri2
                          ),
    gsSPNTriangles_5b(18, 23, 20, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot1_cbr_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 16, 16, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTileSize(0, 0, 0, 124, 60),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&cbr_1_v[296], 10, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 6, 7, // tri0
                      5, 8, 9, // tri1
                      5, 9, 6, // tri2
                      8, 0, 3  // tri3
                      ),
    gsSPNTriangles_5b(8, 3, 9, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot2_cbr_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&cbr_1_v[238], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 16, 16, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTileSize(0, 0, 0, 124, 60),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&cbr_1_v[243], 19, 5),
    gsSPNTrianglesInit_5b(8,       // tri count
                          4, 5, 6, // tri0
                          2, 7, 8, // tri1
                          4, 9, 10 // tri2
                          ),
    gsSPNTriangles_5b(4, 11, 0, // tri0
                      3, 12, 4, // tri1
                      3, 2, 13, // tri2
                      2, 1, 14  // tri3
                      ),
    gsSPNTriangles_5b(2, 16, 15, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(4,          // tri count
                          17, 18, 19, // tri0
                          20, 18, 21, // tri1
                          18, 17, 21  // tri2
                          ),
    gsSPNTriangles_5b(20, 22, 23, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot1_cbr_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 16, 16, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTileSize(0, 0, 0, 124, 60),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&cbr_1_v[262], 10, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 6, 7, // tri0
                      5, 0, 3, // tri1
                      5, 3, 6, // tri2
                      1, 8, 9  // tri3
                      ),
    gsSPNTriangles_5b(1, 9, 2, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx base_cbr_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x3C0, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsDPSetTileSize(0, 0, 0, 60, 60),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&cbr_1_v[312], 16, 0),
    gsSPNTrianglesInit_5b(22,      // tri count
                          0, 1, 2, // tri0
                          2, 3, 0, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(6, 5, 7,   // tri0
                      7, 8, 9,   // tri1
                      10, 11, 9, // tri2
                      3, 2, 11   // tri3
                      ),
    gsSPNTriangles_5b(12, 1, 13, // tri0
                      11, 2, 14, // tri1
                      2, 1, 14,  // tri2
                      6, 12, 4   // tri3
                      ),
    gsSPNTriangles_5b(12, 6, 14, // tri0
                      6, 15, 14, // tri1
                      15, 9, 14, // tri2
                      9, 8, 10   // tri3
                      ),
    gsSPNTriangles_5b(9, 11, 14, // tri0
                      11, 10, 3, // tri1
                      0, 13, 1,  // tri2
                      1, 12, 14  // tri3
                      ),
    gsSPNTriangles_5b(13, 4, 12, // tri0
                      9, 15, 7,  // tri1
                      7, 15, 6,  // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTextureBlock_4b_Dolphin(anime_3_txt, G_IM_FMT_CI, 32, 32, 14, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTileSize(0, 0, 0, 252, 124),
    gsSPVertex(&cbr_1_v[328], 18, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          2, 3, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 9, 10,   // tri0
                      11, 12, 13, // tri1
                      13, 7, 11,  // tri2
                      14, 12, 11  // tri3
                      ),
    gsSPNTriangles_5b(7, 13, 5,  // tri0
                      11, 8, 14, // tri1
                      10, 14, 8, // tri2
                      4, 15, 2   // tri3
                      ),
    gsSPNTriangles_5b(2, 15, 0,  // tri0
                      3, 10, 9,  // tri1
                      16, 17, 1, // tri2
                      1, 0, 16   // tri3
                      ),
    gsSPNTriangles_5b(9, 4, 3, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

// clang-format off
static cKF_Joint_R_c cKF_je_r_cbr_1_tbl[] = {
    /* joint 0 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,1000,0 },
    /* joint 1 */ { base_cbr_model, 4, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 2 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,-525,0 },
    /* joint 3 */ { Lfoot1_cbr_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 4 */ { Lfoot2_cbr_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 5 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 6 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,525,0 },
    /* joint 7 */ { Rfoot1_cbr_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 8 */ { Rfoot2_cbr_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 9 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 10 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,-932 },
    /* joint 11 */ { tail1_cbr_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 12 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 650,0,0 },
    /* joint 13 */ { chest_cbr_model, 3, cKF_JOINT_FLAG_DISP_OPA, 426,0,0 },
    /* joint 14 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 950,-1000,100 },
    /* joint 15 */ { Larm1_cbr_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 16 */ { Larm2_cbr_model, 0, cKF_JOINT_FLAG_DISP_OPA, 550,0,0 },
    /* joint 17 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 950,1000,100 },
    /* joint 18 */ { Rarm1_cbr_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 19 */ { Rarm2_cbr_model, 1, cKF_JOINT_FLAG_DISP_OPA, 550,0,0 },
    /* joint 20 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 550,0,0 },
    /* joint 21 */ { NULL, 2, cKF_JOINT_FLAG_DISP_OPA, 1295,0,0 },
    /* joint 22 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 1050,0,1650 },
    /* joint 23 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 24 */ { head_cbr_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 25 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 2000,0,0 },
};
// clang-format on

extern cKF_Skeleton_R_c cKF_bs_r_cbr_1 = { 26, 12, cKF_je_r_cbr_1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_npc_model_mdl_cbr_1_c(void) {
    pc_load_asset("assets/npc/mdl/cbr_1_v.bin", cbr_1_v, 0x15A0, 0x48F580, 0, 2);
}
#endif

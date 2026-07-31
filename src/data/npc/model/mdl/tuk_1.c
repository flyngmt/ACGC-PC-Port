#include "c_keyframe.h"
#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
static Vtx tuk_1_v[0x1D50 / sizeof(Vtx)];
#else
static Vtx tuk_1_v[] = {
#include "assets/npc/mdl/tuk_1_v.inc"
};
#endif

static Gfx head_tuk_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tuk_1_v[11], 9, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*14, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x200, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&tuk_1_v[20], 19, 9),
    gsSPNTrianglesInit_5b(9,        // tri count
                          5, 3, 9,  // tri0
                          1, 6, 10, // tri1
                          5, 11, 12 // tri2
                          ),
    gsSPNTriangles_5b(6, 13, 14, // tri0
                      7, 15, 16, // tri1
                      8, 17, 18, // tri2
                      7, 5, 19   // tri3
                      ),
    gsSPNTriangles_5b(6, 8, 20, // tri0
                      8, 7, 21, // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPNTrianglesInit_5b(4,         // tri count
                          2, 4, 22,  // tri0
                          4, 23, 24, // tri1
                          4, 25, 26  // tri2
                          ),
    gsSPNTriangles_5b(4, 0, 27, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x040, G_IM_FMT_CI, 16, 16, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(0, 0, 0, 124, 124),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tuk_1_v[39], 23, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 2, // tri1
                          2, 4, 5  // tri2
                          ),
    gsSPNTriangles_5b(1, 6, 2, // tri0
                      2, 6, 7, // tri1
                      8, 3, 2, // tri2
                      2, 7, 8  // tri3
                      ),
    gsSPNTriangles_5b(2, 5, 0, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x0C0, G_IM_FMT_CI, 16, 16, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(0, 0, 0, 124, 124),
    gsSPNTrianglesInit_5b(14,         // tri count
                          9, 10, 11,  // tri0
                          11, 10, 12, // tri1
                          13, 12, 14  // tri2
                          ),
    gsSPNTriangles_5b(15, 16, 17, // tri0
                      15, 18, 19, // tri1
                      19, 20, 15, // tri2
                      14, 21, 22  // tri3
                      ),
    gsSPNTriangles_5b(22, 13, 14, // tri0
                      12, 13, 11, // tri1
                      11, 20, 9,  // tri2
                      17, 16, 22  // tri3
                      ),
    gsSPNTriangles_5b(17, 18, 15, // tri0
                      22, 21, 17, // tri1
                      19, 9, 20,  // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x140, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsDPSetTileSize(0, 0, 0, 60, 124),
    gsSPVertex(&tuk_1_v[62], 27, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(9, 10, 6, // tri0
                      1, 0, 11, // tri1
                      11, 7, 1, // tri2
                      12, 5, 4  // tri3
                      ),
    gsSPNTriangles_5b(12, 4, 10, // tri0
                      10, 9, 12, // tri1
                      11, 8, 7,  // tri2
                      2, 13, 0   // tri3
                      ),
    gsSPNTriangles_5b(5, 14, 3, // tri0
                      6, 15, 9, // tri1
                      8, 15, 6, // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x180, G_IM_FMT_CI, 16, 16, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 124, 60),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(12,         // tri count
                          16, 17, 18, // tri0
                          19, 20, 21, // tri1
                          19, 21, 22  // tri2
                          ),
    gsSPNTriangles_5b(23, 18, 17, // tri0
                      17, 16, 24, // tri1
                      20, 25, 21, // tri2
                      26, 21, 25  // tri3
                      ),
    gsSPNTriangles_5b(22, 17, 24, // tri0
                      22, 24, 19, // tri1
                      21, 26, 23, // tri2
                      17, 22, 23  // tri3
                      ),
    gsSPNTriangles_5b(23, 22, 21, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x200, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&tuk_1_v[89], 13, 0),
    gsSPNTrianglesInit_5b(13,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          3, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(2, 7, 0, // tri0
                      8, 5, 0, // tri1
                      7, 9, 0, // tri2
                      5, 10, 6 // tri3
                      ),
    gsSPNTriangles_5b(8, 10, 5, // tri0
                      11, 9, 7, // tri1
                      0, 9, 8,  // tri2
                      5, 4, 1   // tri3
                      ),
    gsSPNTriangles_5b(5, 1, 0,   // tri0
                      6, 10, 12, // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&tuk_1_v[102], 21, 0),
    gsSPNTrianglesInit_5b(18,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(4, 9, 5,  // tri0
                      8, 2, 10, // tri1
                      11, 4, 3, // tri2
                      10, 2, 4  // tri3
                      ),
    gsSPNTriangles_5b(12, 8, 7, // tri0
                      9, 4, 1,  // tri1
                      6, 8, 13, // tri2
                      4, 11, 10 // tri3
                      ),
    gsSPNTriangles_5b(4, 2, 1,   // tri0
                      10, 14, 8, // tri1
                      13, 8, 14, // tri2
                      2, 12, 0   // tri3
                      ),
    gsSPNTriangles_5b(12, 2, 8,   // tri0
                      15, 16, 17, // tri1
                      18, 19, 20, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x240, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&tuk_1_v[123], 14, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          3, 6, 4  // tri2
                          ),
    gsSPNTriangles_5b(2, 7, 8,   // tri0
                      9, 5, 10,  // tri1
                      7, 11, 12, // tri2
                      5, 9, 3    // tri3
                      ),
    gsSPNTriangles_5b(8, 0, 2,   // tri0
                      4, 13, 10, // tri1
                      12, 11, 0, // tri2
                      10, 5, 4   // tri3
                      ),
    gsSPNTriangles_5b(0, 8, 12,  // tri0
                      12, 8, 7,  // tri1
                      10, 13, 9, // tri2
                      0, 11, 1   // tri3
                      ),
    gsSPNTriangles_5b(6, 13, 4, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_1_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&tuk_1_v[137], 29, 0),
    gsSPNTrianglesInit_5b(23,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(5, 9, 3,  // tri0
                      2, 10, 0, // tri1
                      8, 11, 6, // tri2
                      6, 12, 7  // tri3
                      ),
    gsSPNTriangles_5b(4, 13, 5, // tri0
                      5, 13, 1, // tri1
                      10, 6, 0, // tri2
                      0, 5, 1   // tri3
                      ),
    gsSPNTriangles_5b(10, 12, 6, // tri0
                      0, 6, 14,  // tri1
                      14, 6, 11, // tri2
                      14, 11, 15 // tri3
                      ),
    gsSPNTriangles_5b(16, 9, 5,   // tri0
                      16, 5, 17,  // tri1
                      16, 18, 15, // tri2
                      15, 18, 14  // tri3
                      ),
    gsSPNTriangles_5b(17, 18, 16, // tri0
                      14, 18, 17, // tri1
                      17, 5, 0,   // tri2
                      0, 14, 17   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(0, 0, 0, 60, 60),
    gsSPNTrianglesInit_5b(10,         // tri count
                          19, 20, 21, // tri0
                          22, 23, 19, // tri1
                          21, 24, 25  // tri2
                          ),
    gsSPNTriangles_5b(25, 22, 19, // tri0
                      25, 19, 21, // tri1
                      23, 26, 27, // tri2
                      24, 21, 20  // tri3
                      ),
    gsSPNTriangles_5b(27, 19, 23, // tri0
                      20, 28, 24, // tri1
                      19, 27, 20, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&tuk_1_v[166], 5, 0),
    gsSPNTrianglesInit_5b(3,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          1, 3, 4  // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx mouth_tuk_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*14, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tuk_1_v[0], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*13, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&tuk_1_v[4], 7, 4),
    gsSPNTrianglesInit_5b(5,       // tri count
                          0, 3, 4, // tri0
                          2, 1, 5, // tri1
                          3, 7, 6  // tri2
                          ),
    gsSPNTriangles_5b(1, 9, 8,  // tri0
                      3, 2, 10, // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rarm2_tuk_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*11, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tuk_1_v[204], 6, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*12, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x2C0, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&tuk_1_v[210], 15, 6),
    gsSPNTrianglesInit_5b(7,       // tri count
                          4, 6, 7, // tri0
                          2, 4, 8, // tri1
                          4, 9, 10 // tri2
                          ),
    gsSPNTriangles_5b(3, 11, 12, // tri0
                      3, 13, 0,  // tri1
                      5, 14, 15, // tri2
                      5, 1, 16   // tri3
                      ),
    gsSPNTrianglesInit_5b(2,          // tri count
                          17, 18, 19, // tri0
                          20, 17, 19, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rarm1_tuk_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tuk_1_v[225], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*11, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x2C0, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&tuk_1_v[228], 9, 3),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 3, // tri0
                          2, 0, 4, // tri1
                          0, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(1, 7, 8,   // tri0
                      1, 2, 9,   // tri1
                      2, 10, 11, // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Larm2_tuk_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*9, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tuk_1_v[171], 6, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x2C0, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&tuk_1_v[177], 15, 6),
    gsSPNTrianglesInit_5b(7,       // tri count
                          4, 6, 7, // tri0
                          4, 2, 8, // tri1
                          4, 9, 10 // tri2
                          ),
    gsSPNTriangles_5b(0, 11, 12, // tri0
                      0, 13, 3,  // tri1
                      5, 14, 15, // tri2
                      1, 5, 16   // tri3
                      ),
    gsSPNTrianglesInit_5b(2,          // tri count
                          17, 18, 19, // tri0
                          17, 19, 20, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Larm1_tuk_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tuk_1_v[192], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*9, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x2C0, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&tuk_1_v[195], 9, 3),
    gsSPNTrianglesInit_5b(6,       // tri count
                          1, 0, 3, // tri0
                          0, 2, 4, // tri1
                          0, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(1, 7, 8,   // tri0
                      2, 1, 9,   // tri1
                      2, 10, 11, // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx chest_tuk_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tuk_1_v[237], 8, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 32, 24, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&tuk_1_v[245], 20, 8),
    gsSPNTrianglesInit_5b(14,       // tri count
                          5, 8, 0,  // tri0
                          0, 9, 6,  // tri1
                          5, 11, 10 // tri2
                          ),
    gsSPNTriangles_5b(4, 3, 12,  // tri0
                      7, 13, 3,  // tri1
                      3, 14, 15, // tri2
                      4, 17, 16  // tri3
                      ),
    gsSPNTriangles_5b(5, 4, 18,  // tri0
                      6, 20, 19, // tri1
                      7, 2, 21,  // tri2
                      2, 1, 22   // tri3
                      ),
    gsSPNTriangles_5b(1, 6, 23,  // tri0
                      1, 24, 25, // tri1
                      2, 27, 26, // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&tuk_1_v[265], 18, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 2, 1  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 4, // tri0
                      2, 8, 0, // tri1
                      5, 9, 3, // tri2
                      1, 7, 6  // tri3
                      ),
    gsSPNTriangles_5b(4, 3, 6, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPNTrianglesInit_5b(6,          // tri count
                          10, 11, 12, // tri0
                          10, 12, 13, // tri1
                          11, 10, 14  // tri2
                          ),
    gsSPNTriangles_5b(12, 15, 16, // tri0
                      14, 17, 11, // tri1
                      16, 13, 12, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 32, 24, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&tuk_1_v[283], 26, 0),
    gsSPNTrianglesInit_5b(32,      // tri count
                          0, 1, 2, // tri0
                          3, 2, 4, // tri1
                          5, 2, 1  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 2,   // tri0
                      7, 8, 9,   // tri1
                      9, 10, 11, // tri2
                      9, 12, 7   // tri3
                      ),
    gsSPNTriangles_5b(2, 6, 4,   // tri0
                      13, 14, 2, // tri1
                      11, 12, 9, // tri2
                      11, 0, 15  // tri3
                      ),
    gsSPNTriangles_5b(11, 15, 16, // tri0
                      13, 7, 17,  // tri1
                      13, 17, 18, // tri2
                      0, 19, 20   // tri3
                      ),
    gsSPNTriangles_5b(0, 20, 15,  // tri0
                      14, 13, 18, // tri1
                      14, 18, 21, // tri2
                      12, 11, 16  // tri3
                      ),
    gsSPNTriangles_5b(12, 16, 22, // tri0
                      7, 23, 8,   // tri1
                      10, 24, 11, // tri2
                      0, 24, 1    // tri3
                      ),
    gsSPNTriangles_5b(23, 13, 3, // tri0
                      1, 24, 10, // tri1
                      3, 8, 23,  // tri2
                      9, 25, 10  // tri3
                      ),
    gsSPNTriangles_5b(8, 25, 9, // tri0
                      2, 19, 0, // tri1
                      2, 3, 13, // tri2
                      7, 12, 22 // tri3
                      ),
    gsSPNTriangles_5b(7, 22, 17, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx tail_tuk_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tuk_1_v[309], 6, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x580, G_IM_FMT_CI, 16, 24, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tuk_1_v[315], 20, 6),
    gsSPNTrianglesInit_5b(3,        // tri count
                          1, 6, 7,  // tri0
                          3, 8, 9,  // tri1
                          3, 10, 11 // tri2
                          ),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(2,        // tri count
                          1, 0, 12, // tri0
                          5, 2, 13, // tri1
                          0, 0, 0   // tri2
                          ),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(1,         // tri count
                          1, 14, 15, // tri0
                          0, 0, 0,   // tri1
                          0, 0, 0    // tri2
                          ),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(6,         // tri count
                          0, 3, 16,  // tri0
                          3, 17, 18, // tri1
                          1, 19, 20  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 21,  // tri0
                      4, 22, 23, // tri1
                      2, 24, 25, // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tuk_1_v[335], 21, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          2, 1, 3, // tri1
                          2, 4, 0  // tri2
                          ),
    gsSPNTriangles_5b(3, 5, 6, // tri0
                      7, 8, 4, // tri1
                      2, 9, 7, // tri2
                      10, 7, 9 // tri3
                      ),
    gsSPNTriangles_5b(10, 8, 7, // tri0
                      6, 11, 9, // tri1
                      1, 5, 3,  // tri2
                      3, 9, 2   // tri3
                      ),
    gsSPNTriangles_5b(7, 4, 2,   // tri0
                      9, 11, 10, // tri1
                      9, 3, 6,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(8,          // tri count
                          12, 13, 14, // tri0
                          14, 13, 15, // tri1
                          14, 16, 12  // tri2
                          ),
    gsSPNTriangles_5b(17, 18, 16, // tri0
                      14, 19, 17, // tri1
                      13, 20, 15, // tri2
                      15, 19, 14  // tri3
                      ),
    gsSPNTriangles_5b(17, 16, 14, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot3_tuk_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tuk_1_v[406], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*6, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x640, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&tuk_1_v[410], 20, 4),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 3, 4, // tri0
                          1, 0, 5, // tri1
                          3, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(2, 8, 9,   // tri0
                      2, 10, 3,  // tri1
                      1, 11, 12, // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(6,          // tri count
                          13, 14, 15, // tri0
                          13, 16, 14, // tri1
                          13, 17, 18  // tri2
                          ),
    gsSPNTriangles_5b(13, 19, 17, // tri0
                      15, 19, 13, // tri1
                      18, 20, 13, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(1,          // tri count
                          21, 22, 23, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot2_tuk_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*4, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tuk_1_v[430], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x640, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&tuk_1_v[434], 14, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          3, 4, 5, // tri0
                          1, 6, 7, // tri1
                          3, 0, 8  // tri2
                          ),
    gsSPNTriangles_5b(0, 2, 9,   // tri0
                      2, 10, 11, // tri1
                      1, 3, 12,  // tri2
                      3, 13, 14  // tri3
                      ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          15, 16, 17, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot1_tuk_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x640, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tuk_1_v[448], 8, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          1, 0, 3, // tri1
                          2, 4, 0  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 4, // tri0
                      5, 4, 2, // tri1
                      3, 7, 1, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot3_tuk_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tuk_1_v[356], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x640, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&tuk_1_v[360], 20, 4),
    gsSPNTrianglesInit_5b(6,       // tri count
                          3, 0, 4, // tri0
                          0, 1, 5, // tri1
                          3, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(3, 8, 9,   // tri0
                      3, 10, 2,  // tri1
                      1, 11, 12, // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(6,          // tri count
                          13, 14, 15, // tri0
                          14, 16, 15, // tri1
                          17, 18, 15  // tri2
                          ),
    gsSPNTriangles_5b(18, 19, 15, // tri0
                      15, 19, 13, // tri1
                      15, 20, 17, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(1,          // tri count
                          21, 22, 23, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot2_tuk_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tuk_1_v[380], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x640, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&tuk_1_v[384], 14, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          3, 4, 5, // tri0
                          1, 6, 7, // tri1
                          0, 3, 8  // tri2
                          ),
    gsSPNTriangles_5b(2, 0, 9,   // tri0
                      2, 10, 11, // tri1
                      3, 1, 12,  // tri2
                      3, 13, 14  // tri3
                      ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          15, 16, 17, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot1_tuk_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x640, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tuk_1_v[398], 8, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          3, 2, 1, // tri1
                          2, 4, 0  // tri2
                          ),
    gsSPNTriangles_5b(0, 4, 5, // tri0
                      0, 5, 6, // tri1
                      1, 7, 3, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx base_tuk_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 32, 24, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tuk_1_v[456], 13, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 1, 7  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 6,  // tri0
                      7, 0, 3,  // tri1
                      3, 8, 7,  // tri2
                      9, 10, 11 // tri3
                      ),
    gsSPNTriangles_5b(10, 2, 11, // tri0
                      3, 0, 10,  // tri1
                      3, 10, 4,  // tri2
                      12, 4, 9   // tri3
                      ),
    gsSPNTriangles_5b(5, 4, 12, // tri0
                      10, 9, 4, // tri1
                      7, 1, 0,  // tri2
                      5, 8, 3   // tri3
                      ),
    gsSPNTriangles_5b(2, 10, 0, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPEndDisplayList(),
};

// clang-format off
static cKF_Joint_R_c cKF_je_r_tuk_1_tbl[] = {
    /* joint 0 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,1000,0 },
    /* joint 1 */ { base_tuk_model, 4, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 2 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,-400,0 },
    /* joint 3 */ { Lfoot1_tuk_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 4 */ { Lfoot2_tuk_model, 1, cKF_JOINT_FLAG_DISP_OPA, 348,0,0 },
    /* joint 5 */ { Lfoot3_tuk_model, 0, cKF_JOINT_FLAG_DISP_OPA, 351,0,0 },
    /* joint 6 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,400,0 },
    /* joint 7 */ { Rfoot1_tuk_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 8 */ { Rfoot2_tuk_model, 1, cKF_JOINT_FLAG_DISP_OPA, 349,0,0 },
    /* joint 9 */ { Rfoot3_tuk_model, 0, cKF_JOINT_FLAG_DISP_OPA, 349,0,0 },
    /* joint 10 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,-800 },
    /* joint 11 */ { tail_tuk_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 12 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 650,0,0 },
    /* joint 13 */ { chest_tuk_model, 3, cKF_JOINT_FLAG_DISP_OPA, 201,0,0 },
    /* joint 14 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 575,-700,150 },
    /* joint 15 */ { Larm1_tuk_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 16 */ { Larm2_tuk_model, 0, cKF_JOINT_FLAG_DISP_OPA, 349,0,0 },
    /* joint 17 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 575,700,150 },
    /* joint 18 */ { Rarm1_tuk_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 19 */ { Rarm2_tuk_model, 1, cKF_JOINT_FLAG_DISP_OPA, 350,0,0 },
    /* joint 20 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 350,0,0 },
    /* joint 21 */ { NULL, 2, cKF_JOINT_FLAG_DISP_OPA, 1202,0,0 },
    /* joint 22 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 600,0,950 },
    /* joint 23 */ { mouth_tuk_model, 0, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 24 */ { head_tuk_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 25 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 1198,0,0 },
};
// clang-format on

extern cKF_Skeleton_R_c cKF_bs_r_tuk_1 = { 26, 15, cKF_je_r_tuk_1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_npc_model_mdl_tuk_1_c(void) {
    pc_load_asset("assets/npc/mdl/tuk_1_v.bin", tuk_1_v, 0x1D50, 0x8DB550, 0, 2);
}
#endif

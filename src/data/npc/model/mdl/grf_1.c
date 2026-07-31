#include "c_keyframe.h"
#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
static Vtx grf_1_v[0x1AE0 / sizeof(Vtx)];
#else
static Vtx grf_1_v[] = {
#include "assets/npc/mdl/grf_1_v.inc"
};
#endif

static Gfx head_grf_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grf_1_v[32], 6, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*13, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x100, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&grf_1_v[38], 20, 6),
    gsSPNTrianglesInit_5b(10,      // tri count
                          1, 2, 6, // tri0
                          3, 5, 7, // tri1
                          5, 0, 8  // tri2
                          ),
    gsSPNTriangles_5b(0, 10, 9,  // tri0
                      5, 11, 12, // tri1
                      2, 4, 13,  // tri2
                      1, 14, 15  // tri3
                      ),
    gsSPNTriangles_5b(0, 16, 17, // tri0
                      0, 1, 18,  // tri1
                      2, 19, 20, // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3,          // tri count
                          21, 22, 23, // tri0
                          21, 24, 22, // tri1
                          25, 22, 24  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x0C0, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&grf_1_v[58], 10, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 2  // tri2
                          ),
    gsSPNTriangles_5b(2, 1, 6, // tri0
                      5, 4, 8, // tri1
                      5, 9, 3, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x200, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&grf_1_v[68], 30, 0),
    gsSPNTrianglesInit_5b(22,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(1, 9, 2,  // tri0
                      8, 10, 6, // tri1
                      7, 11, 8, // tri2
                      4, 12, 13 // tri3
                      ),
    gsSPNTriangles_5b(4, 13, 14,  // tri0
                      0, 2, 15,   // tri1
                      16, 13, 12, // tri2
                      17, 18, 19  // tri3
                      ),
    gsSPNTriangles_5b(20, 21, 22, // tri0
                      12, 4, 3,   // tri1
                      12, 3, 23,  // tri2
                      18, 24, 19  // tri3
                      ),
    gsSPNTriangles_5b(25, 5, 4,   // tri0
                      4, 14, 25,  // tri1
                      12, 26, 16, // tri2
                      20, 22, 27  // tri3
                      ),
    gsSPNTriangles_5b(26, 12, 23, // tri0
                      1, 28, 9,   // tri1
                      29, 6, 10,  // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_1_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&grf_1_v[98], 26, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          2, 1, 3, // tri1
                          4, 5, 0  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 3,  // tri0
                      2, 3, 8,  // tri1
                      3, 1, 9,  // tri2
                      0, 10, 11 // tri3
                      ),
    gsSPNTriangles_5b(12, 8, 3,  // tri0
                      13, 0, 11, // tri1
                      12, 3, 7,  // tri2
                      0, 13, 4   // tri3
                      ),
    gsSPNTriangles_5b(5, 1, 0,  // tri0
                      3, 9, 6,  // tri1
                      10, 0, 2, // tri2
                      2, 14, 10 // tri3
                      ),
    gsSPNTriangles_5b(8, 14, 2, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x240, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(12,         // tri count
                          15, 16, 17, // tri0
                          17, 18, 15, // tri1
                          17, 16, 19  // tri2
                          ),
    gsSPNTriangles_5b(19, 20, 21, // tri0
                      21, 22, 18, // tri1
                      18, 19, 21, // tri2
                      21, 20, 22  // tri3
                      ),
    gsSPNTriangles_5b(23, 19, 16, // tri0
                      24, 16, 15, // tri1
                      22, 20, 25, // tri2
                      20, 19, 23  // tri3
                      ),
    gsSPNTriangles_5b(17, 19, 18, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x2C0, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&grf_1_v[124], 19, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 8, // tri0
                      2, 1, 3, // tri1
                      4, 6, 9, // tri2
                      8, 5, 4  // tri3
                      ),
    gsSPNTriangles_5b(9, 7, 4, // tri0
                      6, 5, 8, // tri1
                      6, 8, 9, // tri2
                      3, 1, 10 // tri3
                      ),
    gsSPNTriangles_5b(10, 11, 3, // tri0
                      3, 11, 0,  // tri1
                      0, 10, 1,  // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 16, 8, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 124, 28),
    gsSPNTrianglesInit_5b(5,          // tri count
                          12, 13, 14, // tri0
                          12, 15, 16, // tri1
                          14, 13, 17  // tri2
                          ),
    gsSPNTriangles_5b(16, 13, 12, // tri0
                      17, 18, 14, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x340, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&grf_1_v[143], 21, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(9, 10, 5,   // tri0
                      11, 9, 12,  // tri1
                      12, 13, 11, // tri2
                      7, 6, 14    // tri3
                      ),
    gsSPNTriangles_5b(13, 12, 15, // tri0
                      13, 15, 16, // tri1
                      3, 5, 17,   // tri2
                      6, 15, 18   // tri3
                      ),
    gsSPNTriangles_5b(1, 14, 6,  // tri0
                      11, 19, 9, // tri1
                      8, 16, 15, // tri2
                      10, 9, 19  // tri3
                      ),
    gsSPNTriangles_5b(1, 18, 20, // tri0
                      15, 6, 8,  // tri1
                      5, 4, 9,   // tri2
                      4, 12, 9   // tri3
                      ),
    gsSPNTriangles_5b(18, 1, 6, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx mouth_grf_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*13, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grf_1_v[0], 7, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*12, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&grf_1_v[7], 18, 7),
    gsSPNTrianglesInit_5b(2,       // tri count
                          3, 7, 1, // tri0
                          1, 8, 9, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x040, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(8,        // tri count
                          2, 5, 10, // tri0
                          6, 0, 11, // tri1
                          4, 6, 12  // tri2
                          ),
    gsSPNTriangles_5b(5, 13, 14, // tri0
                      6, 15, 16, // tri1
                      2, 17, 18, // tri2
                      0, 19, 20  // tri3
                      ),
    gsSPNTriangles_5b(5, 4, 21, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1,          // tri count
                          22, 23, 24, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x040, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&grf_1_v[25], 7, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          3, 2, 1, // tri1
                          2, 4, 0  // tri2
                          ),
    gsSPNTriangles_5b(3, 5, 4, // tri0
                      1, 6, 3, // tri1
                      4, 2, 3, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rarm2_grf_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grf_1_v[198], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*11, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x440, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&grf_1_v[202], 16, 4),
    gsSPNTrianglesInit_5b(8,       // tri count
                          2, 4, 5, // tri0
                          3, 6, 7, // tri1
                          3, 8, 9  // tri2
                          ),
    gsSPNTriangles_5b(2, 0, 10,  // tri0
                      0, 3, 11,  // tri1
                      2, 12, 13, // tri2
                      1, 2, 14   // tri3
                      ),
    gsSPNTriangles_5b(3, 1, 15, // tri0
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

static Gfx Rarm1_grf_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grf_1_v[218], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x440, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&grf_1_v[221], 11, 3),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 3, // tri0
                          1, 5, 4, // tri1
                          2, 7, 6  // tri2
                          ),
    gsSPNTriangles_5b(1, 2, 8,   // tri0
                      2, 0, 9,   // tri1
                      0, 10, 11, // tri2
                      1, 12, 13  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Larm2_grf_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grf_1_v[164], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*9, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x440, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&grf_1_v[168], 16, 4),
    gsSPNTrianglesInit_5b(8,       // tri count
                          2, 4, 5, // tri0
                          3, 6, 7, // tri1
                          3, 8, 9  // tri2
                          ),
    gsSPNTriangles_5b(0, 2, 10,  // tri0
                      3, 0, 11,  // tri1
                      2, 12, 13, // tri2
                      2, 1, 14   // tri3
                      ),
    gsSPNTriangles_5b(1, 3, 15, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPNTrianglesInit_5b(2,          // tri count
                          16, 17, 18, // tri0
                          17, 16, 19, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Larm1_grf_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grf_1_v[184], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x440, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&grf_1_v[187], 11, 3),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 2, 3, // tri0
                          0, 5, 4, // tri1
                          1, 7, 6  // tri2
                          ),
    gsSPNTriangles_5b(1, 0, 8,   // tri0
                      2, 1, 9,   // tri1
                      2, 10, 11, // tri2
                      0, 12, 13  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx chest_grf_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grf_1_v[232], 10, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x480, G_IM_FMT_CI, 32, 24, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&grf_1_v[242], 22, 10),
    gsSPNTrianglesInit_5b(14,        // tri count
                          9, 10, 11, // tri0
                          9, 12, 13, // tri1
                          8, 0, 14   // tri2
                          ),
    gsSPNTriangles_5b(9, 6, 15,  // tri0
                      0, 7, 16,  // tri1
                      8, 17, 18, // tri2
                      4, 8, 19   // tri3
                      ),
    gsSPNTriangles_5b(3, 20, 21, // tri0
                      4, 22, 23, // tri1
                      7, 1, 24,  // tri2
                      1, 25, 26  // tri3
                      ),
    gsSPNTriangles_5b(6, 27, 28, // tri0
                      3, 9, 29,  // tri1
                      7, 30, 31, // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&grf_1_v[264], 21, 10),
    gsSPNTrianglesInit_5b(2,        // tri count
                          2, 3, 10, // tri0
                          6, 5, 11, // tri1
                          0, 0, 0   // tri2
                          ),
    gsSPNTrianglesInit_5b(15,         // tri count
                          12, 13, 14, // tri0
                          15, 16, 12, // tri1
                          17, 18, 19  // tri2
                          ),
    gsSPNTriangles_5b(20, 21, 22, // tri0
                      22, 21, 23, // tri1
                      17, 19, 23, // tri2
                      14, 13, 24  // tri3
                      ),
    gsSPNTriangles_5b(20, 22, 25, // tri0
                      15, 26, 16, // tri1
                      13, 12, 16, // tri2
                      27, 19, 18  // tri3
                      ),
    gsSPNTriangles_5b(28, 23, 21, // tri0
                      28, 17, 23, // tri1
                      26, 15, 29, // tri2
                      30, 14, 24  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x600, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&grf_1_v[285], 20, 0),
    gsSPNTrianglesInit_5b(22,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 2, // tri1
                          3, 1, 4  // tri2
                          ),
    gsSPNTriangles_5b(1, 3, 2, // tri0
                      5, 6, 7, // tri1
                      7, 6, 8, // tri2
                      4, 0, 2  // tri3
                      ),
    gsSPNTriangles_5b(1, 0, 4,    // tri0
                      9, 5, 10,   // tri1
                      11, 12, 13, // tri2
                      12, 11, 14  // tri3
                      ),
    gsSPNTriangles_5b(12, 14, 13, // tri0
                      15, 11, 13, // tri1
                      11, 15, 14, // tri2
                      14, 15, 13  // tri3
                      ),
    gsSPNTriangles_5b(16, 8, 17, // tri0
                      18, 17, 9, // tri1
                      18, 9, 19, // tri2
                      17, 18, 16 // tri3
                      ),
    gsSPNTriangles_5b(8, 16, 7,  // tri0
                      7, 10, 5,  // tri1
                      10, 19, 9, // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x100, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&grf_1_v[305], 12, 0),
    gsSPNTrianglesInit_5b(10,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,  // tri0
                      9, 10, 7, // tri1
                      2, 8, 7,  // tri2
                      1, 0, 6   // tri3
                      ),
    gsSPNTriangles_5b(6, 11, 4, // tri0
                      7, 3, 2,  // tri1
                      6, 5, 1,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx tail1_grf_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x640, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grf_1_v[328], 6, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 3  // tri2
                          ),
    gsSPNTriangles_5b(4, 3, 2, // tri0
                      0, 5, 4, // tri1
                      0, 4, 1, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx tail2_grf_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grf_1_v[317], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*6, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x640, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&grf_1_v[320], 8, 3),
    gsSPNTrianglesInit_5b(3,       // tri count
                          2, 3, 0, // tri0
                          1, 4, 2, // tri1
                          0, 5, 1  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x440, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          6, 7, 8, // tri0
                          7, 6, 9, // tri1
                          9, 6, 10 // tri2
                          ),
    gsSPNTriangles_5b(9, 8, 7,  // tri0
                      10, 6, 8, // tri1
                      8, 9, 10, // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot2_grf_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grf_1_v[374], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*4, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x680, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&grf_1_v[378], 18, 4),
    gsSPNTrianglesInit_5b(12,      // tri count
                          0, 1, 4, // tri0
                          0, 5, 6, // tri1
                          1, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(2, 9, 10, // tri0
                      2, 1, 11, // tri1
                      1, 2, 12, // tri2
                      0, 13, 14 // tri3
                      ),
    gsSPNTriangles_5b(2, 0, 15,  // tri0
                      2, 16, 17, // tri1
                      1, 3, 18,  // tri2
                      3, 2, 19   // tri3
                      ),
    gsSPNTriangles_5b(2, 20, 21, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&grf_1_v[396], 10, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(9, 7, 6, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot1_grf_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x680, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grf_1_v[406], 8, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          2, 3, 4, // tri1
                          4, 3, 5  // tri2
                          ),
    gsSPNTriangles_5b(5, 1, 6, // tri0
                      2, 7, 0, // tri1
                      4, 7, 2, // tri2
                      6, 4, 5  // tri3
                      ),
    gsSPNTriangles_5b(0, 6, 1, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot2_grf_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grf_1_v[334], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x680, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&grf_1_v[338], 18, 4),
    gsSPNTrianglesInit_5b(12,      // tri count
                          1, 0, 4, // tri0
                          0, 5, 6, // tri1
                          1, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(2, 9, 10, // tri0
                      1, 2, 11, // tri1
                      2, 1, 12, // tri2
                      0, 13, 14 // tri3
                      ),
    gsSPNTriangles_5b(0, 2, 15,  // tri0
                      2, 16, 17, // tri1
                      3, 1, 18,  // tri2
                      2, 3, 19   // tri3
                      ),
    gsSPNTriangles_5b(2, 20, 21, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&grf_1_v[356], 10, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(8, 7, 9, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot1_grf_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x680, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grf_1_v[366], 8, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 0, // tri1
                          5, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(6, 1, 5, // tri0
                      2, 7, 0, // tri1
                      0, 7, 3, // tri2
                      5, 3, 6  // tri3
                      ),
    gsSPNTriangles_5b(1, 6, 2, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx base_grf_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x680, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grf_1_v[414], 16, 0),
    gsSPNTrianglesInit_5b(22,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          3, 6, 4  // tri2
                          ),
    gsSPNTriangles_5b(3, 7, 6, // tri0
                      4, 6, 8, // tri1
                      8, 9, 4, // tri2
                      10, 9, 8 // tri3
                      ),
    gsSPNTriangles_5b(2, 5, 11,   // tri0
                      2, 11, 12,  // tri1
                      13, 14, 15, // tri2
                      15, 12, 13  // tri3
                      ),
    gsSPNTriangles_5b(12, 11, 13, // tri0
                      3, 2, 1,    // tri1
                      3, 5, 2,    // tri2
                      13, 10, 14  // tri3
                      ),
    gsSPNTriangles_5b(9, 13, 11, // tri0
                      7, 3, 1,   // tri1
                      9, 10, 13, // tri2
                      9, 11, 5   // tri3
                      ),
    gsSPNTriangles_5b(9, 5, 4,   // tri0
                      12, 15, 0, // tri1
                      2, 12, 0,  // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

// clang-format off
static cKF_Joint_R_c cKF_je_r_grf_1_tbl[] = {
    /* joint 0 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,1000,0 },
    /* joint 1 */ { base_grf_model, 4, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 2 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,-400,0 },
    /* joint 3 */ { Lfoot1_grf_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 4 */ { Lfoot2_grf_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 5 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 6 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,400,0 },
    /* joint 7 */ { Rfoot1_grf_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 8 */ { Rfoot2_grf_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 9 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 10 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 650,0,-800 },
    /* joint 11 */ { tail1_grf_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 12 */ { tail2_grf_model, 0, cKF_JOINT_FLAG_DISP_OPA, 650,0,0 },
    /* joint 13 */ { chest_grf_model, 3, cKF_JOINT_FLAG_DISP_OPA, 667,0,0 },
    /* joint 14 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 800,-800,0 },
    /* joint 15 */ { Larm1_grf_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 16 */ { Larm2_grf_model, 0, cKF_JOINT_FLAG_DISP_OPA, 550,0,0 },
    /* joint 17 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 800,800,0 },
    /* joint 18 */ { Rarm1_grf_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 19 */ { Rarm2_grf_model, 1, cKF_JOINT_FLAG_DISP_OPA, 550,0,0 },
    /* joint 20 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 550,0,0 },
    /* joint 21 */ { NULL, 2, cKF_JOINT_FLAG_DISP_OPA, 2279,0,0 },
    /* joint 22 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 350,0,750 },
    /* joint 23 */ { mouth_grf_model, 0, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 24 */ { head_grf_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 25 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 1153,0,400 },
};
// clang-format on

extern cKF_Skeleton_R_c cKF_bs_r_grf_1 = { 26, 14, cKF_je_r_grf_1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_npc_model_mdl_grf_1_c(void) {
    pc_load_asset("assets/npc/mdl/grf_1_v.bin", grf_1_v, 0x1AE0, 0x4B33C0, 0, 2);
}
#endif

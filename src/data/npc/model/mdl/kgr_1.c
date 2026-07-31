#include "c_keyframe.h"
#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
static Vtx kgr_1_v[0x1AF0 / sizeof(Vtx)];
#else
static Vtx kgr_1_v[] = {
#include "assets/npc/mdl/kgr_1_v.inc"
};
#endif

static Gfx head_kgr_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&kgr_1_v[18], 6, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*14, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x080, G_IM_FMT_CI, 16, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&kgr_1_v[24], 19, 6),
    gsSPNTrianglesInit_5b(12,      // tri count
                          4, 6, 7, // tri0
                          0, 9, 8, // tri1
                          3, 1, 10 // tri2
                          ),
    gsSPNTriangles_5b(1, 12, 11, // tri0
                      1, 0, 13,  // tri1
                      3, 14, 15, // tri2
                      2, 17, 16  // tri3
                      ),
    gsSPNTriangles_5b(4, 2, 18,  // tri0
                      0, 5, 19,  // tri1
                      5, 20, 21, // tri2
                      2, 3, 22   // tri3
                      ),
    gsSPNTriangles_5b(1, 23, 24, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&kgr_1_v[43], 29, 0),
    gsSPNTrianglesInit_5b(11,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 0, 2  // tri2
                          ),
    gsSPNTriangles_5b(6, 2, 4, // tri0
                      7, 6, 8, // tri1
                      4, 2, 5, // tri2
                      8, 9, 7  // tri3
                      ),
    gsSPNTriangles_5b(5, 10, 3, // tri0
                      7, 0, 6,  // tri1
                      6, 4, 3,  // tri2
                      6, 3, 8   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x180, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(18,         // tri count
                          11, 12, 13, // tri0
                          14, 15, 16, // tri1
                          17, 18, 19  // tri2
                          ),
    gsSPNTriangles_5b(14, 20, 13, // tri0
                      21, 22, 17, // tri1
                      15, 23, 17, // tri2
                      15, 14, 23  // tri3
                      ),
    gsSPNTriangles_5b(12, 11, 24, // tri0
                      17, 24, 21, // tri1
                      19, 15, 17, // tri2
                      11, 25, 26  // tri3
                      ),
    gsSPNTriangles_5b(11, 26, 27, // tri0
                      16, 28, 20, // tri1
                      16, 20, 14, // tri2
                      13, 25, 11  // tri3
                      ),
    gsSPNTriangles_5b(13, 23, 14, // tri0
                      17, 12, 24, // tri1
                      27, 24, 11, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&kgr_1_v[72], 31, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          3, 0, 2, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x1C0, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          4, 5, 6, // tri0
                          7, 8, 9, // tri1
                          7, 9, 10 // tri2
                          ),
    gsSPNTriangles_5b(7, 11, 8,  // tri0
                      10, 4, 7,  // tri1
                      9, 12, 13, // tri2
                      8, 12, 9   // tri3
                      ),
    gsSPNTriangles_5b(11, 7, 4,  // tri0
                      12, 8, 11, // tri1
                      6, 14, 11, // tri2
                      5, 4, 10   // tri3
                      ),
    gsSPNTriangles_5b(14, 13, 12, // tri0
                      11, 14, 12, // tri1
                      4, 6, 11,   // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_1_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(14,         // tri count
                          15, 16, 17, // tri0
                          18, 19, 20, // tri1
                          16, 21, 17  // tri2
                          ),
    gsSPNTriangles_5b(22, 23, 24, // tri0
                      25, 19, 26, // tri1
                      26, 19, 27, // tri2
                      23, 21, 28  // tri3
                      ),
    gsSPNTriangles_5b(29, 27, 30, // tri0
                      22, 21, 23, // tri1
                      29, 26, 27, // tri2
                      18, 20, 15  // tri3
                      ),
    gsSPNTriangles_5b(17, 18, 15, // tri0
                      16, 28, 21, // tri1
                      19, 25, 20, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx mouth_kgr_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*14, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&kgr_1_v[0], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*13, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&kgr_1_v[5], 13, 5),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 5, // tri0
                          2, 3, 6, // tri1
                          0, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(4, 0, 9,   // tri0
                      4, 10, 11, // tri1
                      3, 13, 12, // tri2
                      3, 4, 14   // tri3
                      ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          15, 16, 17, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rarm2_kgr_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*11, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&kgr_1_v[137], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*12, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x2C0, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&kgr_1_v[141], 16, 4),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 4, 5, // tri0
                          1, 6, 7, // tri1
                          1, 8, 9  // tri2
                          ),
    gsSPNTriangles_5b(0, 2, 10,  // tri0
                      2, 1, 11,  // tri1
                      0, 12, 13, // tri2
                      3, 0, 14   // tri3
                      ),
    gsSPNTriangles_5b(1, 3, 15, // tri0
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

static Gfx Rarm1_kgr_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&kgr_1_v[157], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*11, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x2C0, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&kgr_1_v[160], 11, 3),
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

static Gfx Larm2_kgr_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*9, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&kgr_1_v[103], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x2C0, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&kgr_1_v[107], 16, 4),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 4, 5, // tri0
                          1, 6, 7, // tri1
                          1, 8, 9  // tri2
                          ),
    gsSPNTriangles_5b(2, 0, 10,  // tri0
                      1, 2, 11,  // tri1
                      0, 12, 13, // tri2
                      0, 3, 14   // tri3
                      ),
    gsSPNTriangles_5b(3, 1, 15, // tri0
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

static Gfx Larm1_kgr_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&kgr_1_v[123], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*9, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x2C0, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&kgr_1_v[126], 11, 3),
    gsSPNTrianglesInit_5b(7,       // tri count
                          1, 0, 3, // tri0
                          1, 5, 4, // tri1
                          2, 7, 6  // tri2
                          ),
    gsSPNTriangles_5b(2, 1, 8,   // tri0
                      0, 2, 9,   // tri1
                      0, 10, 11, // tri2
                      1, 12, 13  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx chest_kgr_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&kgr_1_v[171], 8, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_3_txt, G_IM_FMT_CI, 32, 32, 14, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 508, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&kgr_1_v[179], 24, 8),
    gsSPNTrianglesInit_5b(15,       // tri count
                          4, 2, 8,  // tri0
                          7, 9, 10, // tri1
                          4, 11, 12 // tri2
                          ),
    gsSPNTriangles_5b(3, 13, 1,  // tri0
                      3, 14, 15, // tri1
                      2, 17, 16, // tri2
                      1, 18, 19  // tri3
                      ),
    gsSPNTriangles_5b(1, 20, 21, // tri0
                      2, 22, 23, // tri1
                      7, 4, 24,  // tri2
                      3, 7, 25   // tri3
                      ),
    gsSPNTriangles_5b(5, 1, 26,  // tri0
                      6, 27, 2,  // tri1
                      7, 28, 29, // tri2
                      7, 30, 31  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x080, G_IM_FMT_CI, 16, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&kgr_1_v[203], 18, 8),
    gsSPNTrianglesInit_5b(3,         // tri count
                          0, 9, 8,   // tri0
                          0, 10, 11, // tri1
                          0, 13, 12  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_3_txt, G_IM_FMT_CI, 32, 32, 14, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 508, 124),
    gsSPNTrianglesInit_5b(4,          // tri count
                          14, 15, 16, // tri0
                          17, 18, 19, // tri1
                          20, 21, 22  // tri2
                          ),
    gsSPNTriangles_5b(23, 24, 25, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x1C0, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&kgr_1_v[221], 30, 0),
    gsSPNTrianglesInit_5b(15,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          4, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 5, 7,  // tri0
                      9, 10, 8, // tri1
                      3, 5, 8,  // tri2
                      9, 1, 11  // tri3
                      ),
    gsSPNTriangles_5b(2, 6, 0, // tri0
                      7, 6, 2, // tri1
                      2, 9, 8, // tri2
                      2, 8, 7  // tri3
                      ),
    gsSPNTriangles_5b(4, 7, 5,   // tri0
                      8, 10, 3,  // tri1
                      11, 10, 9, // tri2
                      9, 2, 1    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_1_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(6,          // tri count
                          12, 13, 14, // tri0
                          15, 16, 13, // tri1
                          14, 17, 12  // tri2
                          ),
    gsSPNTriangles_5b(16, 18, 13, // tri0
                      14, 19, 17, // tri1
                      12, 15, 13, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(3,          // tri count
                          20, 21, 22, // tri0
                          23, 24, 20, // tri1
                          22, 23, 20  // tri2
                          ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x080, G_IM_FMT_CI, 16, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(4,          // tri count
                          25, 26, 27, // tri0
                          26, 28, 29, // tri1
                          26, 25, 28  // tri2
                          ),
    gsSPNTriangles_5b(29, 27, 26, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx tail1_kgr_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&kgr_1_v[251], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x340, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&kgr_1_v[255], 18, 4),
    gsSPNTrianglesInit_5b(9,       // tri count
                          2, 4, 5, // tri0
                          1, 6, 7, // tri1
                          2, 0, 8  // tri2
                          ),
    gsSPNTriangles_5b(0, 1, 9,   // tri0
                      0, 10, 11, // tri1
                      3, 12, 1,  // tri2
                      1, 13, 14  // tri3
                      ),
    gsSPNTriangles_5b(2, 15, 16, // tri0
                      2, 17, 3,  // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(3,          // tri count
                          18, 19, 20, // tri0
                          21, 19, 18, // tri1
                          20, 19, 21  // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot3_kgr_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&kgr_1_v[332], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*6, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&kgr_1_v[335], 13, 3),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 3, 4, // tri0
                          2, 1, 5, // tri1
                          2, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(2, 8, 9,  // tri0
                      1, 0, 10, // tri1
                      0, 2, 11, // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPNTrianglesInit_5b(3,          // tri count
                          12, 13, 14, // tri0
                          14, 15, 12, // tri1
                          14, 13, 15  // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot2_kgr_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*4, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&kgr_1_v[348], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&kgr_1_v[351], 14, 3),
    gsSPNTrianglesInit_5b(7,       // tri count
                          2, 3, 4, // tri0
                          1, 2, 5, // tri1
                          1, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(0, 1, 8,   // tri0
                      2, 0, 9,   // tri1
                      1, 10, 11, // tri2
                      2, 12, 13  // tri3
                      ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          14, 15, 16, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot1_kgr_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&kgr_1_v[365], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*4, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_3_txt, G_IM_FMT_CI, 32, 32, 14, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 508, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&kgr_1_v[370], 20, 5),
    gsSPNTrianglesInit_5b(8,       // tri count
                          3, 2, 5, // tri0
                          0, 6, 1, // tri1
                          0, 4, 7  // tri2
                          ),
    gsSPNTriangles_5b(0, 9, 8,   // tri0
                      4, 3, 10,  // tri1
                      1, 11, 12, // tri2
                      3, 13, 14  // tri3
                      ),
    gsSPNTriangles_5b(2, 1, 15, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(6,          // tri count
                          16, 17, 18, // tri0
                          17, 19, 20, // tri1
                          17, 16, 19  // tri2
                          ),
    gsSPNTriangles_5b(20, 21, 17, // tri0
                      16, 18, 21, // tri1
                      16, 21, 20, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_3_txt, G_IM_FMT_CI, 32, 32, 14, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 508, 124),
    gsSPNTrianglesInit_5b(1,          // tri count
                          22, 23, 24, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot3_kgr_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&kgr_1_v[273], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&kgr_1_v[276], 13, 3),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 3, 4, // tri0
                          1, 5, 6, // tri1
                          1, 2, 7  // tri2
                          ),
    gsSPNTriangles_5b(2, 8, 9,  // tri0
                      0, 1, 10, // tri1
                      2, 0, 11, // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPNTrianglesInit_5b(3,          // tri count
                          12, 13, 14, // tri0
                          14, 15, 12, // tri1
                          15, 13, 12  // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot2_kgr_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&kgr_1_v[289], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&kgr_1_v[292], 14, 3),
    gsSPNTrianglesInit_5b(7,       // tri count
                          2, 3, 4, // tri0
                          2, 1, 5, // tri1
                          1, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(1, 0, 8,   // tri0
                      0, 2, 9,   // tri1
                      1, 10, 11, // tri2
                      2, 12, 13  // tri3
                      ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          14, 15, 16, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot1_kgr_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&kgr_1_v[306], 6, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_3_txt, G_IM_FMT_CI, 32, 32, 14, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 508, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&kgr_1_v[312], 20, 6),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 2, 6, // tri0
                          4, 7, 8, // tri1
                          1, 9, 10 // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 11,  // tri0
                      3, 13, 12, // tri1
                      5, 1, 14,  // tri2
                      4, 15, 3   // tri3
                      ),
    gsSPNTriangles_5b(2, 3, 16, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(6,          // tri count
                          17, 18, 19, // tri0
                          20, 21, 18, // tri1
                          21, 19, 18  // tri2
                          ),
    gsSPNTriangles_5b(18, 22, 20, // tri0
                      20, 22, 17, // tri1
                      20, 17, 19, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_3_txt, G_IM_FMT_CI, 32, 32, 14, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 508, 124),
    gsSPNTrianglesInit_5b(1,          // tri count
                          23, 24, 25, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx base_kgr_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_3_txt, G_IM_FMT_CI, 32, 32, 14, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 508, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&kgr_1_v[390], 28, 0),
    gsSPNTrianglesInit_5b(28,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(9, 10, 4, // tri0
                      9, 4, 3,  // tri1
                      10, 6, 5, // tri2
                      10, 5, 4  // tri3
                      ),
    gsSPNTriangles_5b(11, 12, 13, // tri0
                      11, 13, 2,  // tri1
                      12, 14, 0,  // tri2
                      12, 0, 13   // tri3
                      ),
    gsSPNTriangles_5b(15, 16, 11, // tri0
                      6, 17, 7,   // tri1
                      2, 13, 0,   // tri2
                      5, 18, 3    // tri3
                      ),
    gsSPNTriangles_5b(9, 19, 10,  // tri0
                      11, 16, 12, // tri1
                      20, 21, 22, // tri2
                      20, 23, 24  // tri3
                      ),
    gsSPNTriangles_5b(24, 25, 20, // tri0
                      11, 26, 15, // tri1
                      25, 16, 15, // tri2
                      12, 27, 14  // tri3
                      ),
    gsSPNTriangles_5b(21, 7, 17,  // tri0
                      21, 17, 22, // tri1
                      22, 23, 20, // tri2
                      10, 17, 6   // tri3
                      ),
    gsSPNTriangles_5b(24, 16, 25, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&kgr_1_v[418], 13, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 4, // tri1
                          4, 5, 0  // tri2
                          ),
    gsSPNTriangles_5b(0, 5, 1, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x340, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(7,        // tri count
                          6, 7, 8,  // tri0
                          9, 10, 6, // tri1
                          10, 9, 11 // tri2
                          ),
    gsSPNTriangles_5b(12, 8, 11, // tri0
                      11, 9, 12, // tri1
                      11, 8, 7,  // tri2
                      8, 9, 6    // tri3
                      ),
    gsSPEndDisplayList(),
};

// clang-format off
static cKF_Joint_R_c cKF_je_r_kgr_1_tbl[] = {
    /* joint 0 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,1000,0 },
    /* joint 1 */ { base_kgr_model, 4, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 2 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,-400,0 },
    /* joint 3 */ { Lfoot1_kgr_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 4 */ { Lfoot2_kgr_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 5 */ { Lfoot3_kgr_model, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 6 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,400,0 },
    /* joint 7 */ { Rfoot1_kgr_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 8 */ { Rfoot2_kgr_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 9 */ { Rfoot3_kgr_model, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 10 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, -350,0,-800 },
    /* joint 11 */ { tail1_kgr_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 12 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 399,0,0 },
    /* joint 13 */ { chest_kgr_model, 3, cKF_JOINT_FLAG_DISP_OPA, 450,0,0 },
    /* joint 14 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 650,-650,0 },
    /* joint 15 */ { Larm1_kgr_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 16 */ { Larm2_kgr_model, 0, cKF_JOINT_FLAG_DISP_OPA, 450,0,0 },
    /* joint 17 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 650,650,0 },
    /* joint 18 */ { Rarm1_kgr_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 19 */ { Rarm2_kgr_model, 1, cKF_JOINT_FLAG_DISP_OPA, 450,0,0 },
    /* joint 20 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 451,0,0 },
    /* joint 21 */ { NULL, 2, cKF_JOINT_FLAG_DISP_OPA, 1150,0,0 },
    /* joint 22 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 300,0,1100 },
    /* joint 23 */ { mouth_kgr_model, 0, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 24 */ { head_kgr_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 25 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 1100,0,0 },
};
// clang-format on

extern cKF_Skeleton_R_c cKF_bs_r_kgr_1 = { 26, 15, cKF_je_r_kgr_1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_npc_model_mdl_kgr_1_c(void) {
    pc_load_asset("assets/npc/mdl/kgr_1_v.bin", kgr_1_v, 0x1AF0, 0x55BB80, 0, 2);
}
#endif

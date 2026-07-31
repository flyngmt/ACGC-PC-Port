#include "c_keyframe.h"
#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
static Vtx bea_1_v[0x1720 / sizeof(Vtx)];
#else
static Vtx bea_1_v[] = {
#include "assets/npc/mdl/bea_1_v.inc"
};
#endif

static Gfx head_bea_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 32, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bea_1_v[0], 24, 0),
    gsSPNTrianglesInit_5b(28,      // tri count
                          0, 1, 2, // tri0
                          2, 1, 3, // tri1
                          4, 0, 5  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 8,  // tri0
                      6, 8, 3,  // tri1
                      9, 5, 10, // tri2
                      3, 8, 2   // tri3
                      ),
    gsSPNTriangles_5b(10, 5, 11, // tri0
                      5, 0, 2,   // tri1
                      8, 7, 12,  // tri2
                      10, 11, 13 // tri3
                      ),
    gsSPNTriangles_5b(2, 11, 5,  // tri0
                      8, 11, 2,  // tri1
                      12, 11, 8, // tri2
                      13, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(14, 15, 6, // tri0
                      14, 6, 3,  // tri1
                      14, 3, 16, // tri2
                      6, 15, 7   // tri3
                      ),
    gsSPNTriangles_5b(16, 3, 1,  // tri0
                      16, 1, 17, // tri1
                      17, 1, 18, // tri2
                      0, 19, 18  // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 20, // tri0
                      13, 12, 21, // tri1
                      22, 15, 14, // tri2
                      15, 23, 7   // tri3
                      ),
    gsSPNTriangles_5b(18, 1, 0, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_1_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&bea_1_v[24], 15, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 2, // tri1
                          3, 2, 4  // tri2
                          ),
    gsSPNTriangles_5b(2, 1, 5, // tri0
                      2, 6, 7, // tri1
                      7, 8, 2, // tri2
                      5, 6, 2  // tri3
                      ),
    gsSPNTriangles_5b(8, 7, 9,   // tri0
                      8, 10, 11, // tri1
                      12, 5, 1,  // tri2
                      13, 14, 1  // tri3
                      ),
    gsSPNTriangles_5b(8, 11, 4, // tri0
                      0, 13, 1, // tri1
                      2, 8, 4,  // tri2
                      9, 10, 8  // tri3
                      ),
    gsSPNTriangles_5b(1, 14, 12, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_2_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&bea_1_v[39], 18, 0),
    gsSPNTrianglesInit_5b(22,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          5, 4, 6  // tri2
                          ),
    gsSPNTriangles_5b(1, 3, 7,  // tri0
                      8, 6, 9,  // tri1
                      8, 9, 10, // tri2
                      7, 8, 10  // tri3
                      ),
    gsSPNTriangles_5b(1, 0, 3, // tri0
                      8, 7, 5, // tri1
                      8, 5, 6, // tri2
                      3, 5, 7  // tri3
                      ),
    gsSPNTriangles_5b(3, 0, 4,  // tri0
                      11, 4, 0, // tri1
                      9, 6, 11, // tri2
                      12, 11, 0 // tri3
                      ),
    gsSPNTriangles_5b(11, 13, 9, // tri0
                      6, 4, 14,  // tri1
                      12, 0, 15, // tri2
                      9, 16, 17  // tri3
                      ),
    gsSPNTriangles_5b(17, 10, 9, // tri0
                      2, 15, 0,  // tri1
                      9, 13, 16, // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x200, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&bea_1_v[57], 26, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          2, 1, 3, // tri1
                          4, 0, 5  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 8,    // tri0
                      9, 8, 10,   // tri1
                      11, 12, 13, // tri2
                      10, 13, 9   // tri3
                      ),
    gsSPNTriangles_5b(11, 13, 10, // tri0
                      14, 15, 16, // tri1
                      17, 18, 19, // tri2
                      7, 10, 8    // tri3
                      ),
    gsSPNTriangles_5b(7, 11, 10,  // tri0
                      16, 20, 21, // tri1
                      16, 21, 14, // tri2
                      19, 22, 23  // tri3
                      ),
    gsSPNTriangles_5b(19, 23, 17, // tri0
                      24, 3, 1,   // tri1
                      2, 3, 25,   // tri2
                      25, 5, 2    // tri3
                      ),
    gsSPNTriangles_5b(5, 0, 2, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rarm2_bea_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*9, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bea_1_v[120], 6, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 16, 16, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&bea_1_v[126], 13, 6),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 6, 7, // tri0
                          4, 5, 8, // tri1
                          1, 4, 9  // tri2
                          ),
    gsSPNTriangles_5b(5, 10, 11, // tri0
                      3, 2, 12,  // tri1
                      4, 13, 14, // tri2
                      5, 3, 15   // tri3
                      ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          16, 17, 18, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rarm1_bea_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*6, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bea_1_v[139], 6, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*9, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 16, 16, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&bea_1_v[145], 12, 6),
    gsSPNTrianglesInit_5b(8,        // tri count
                          4, 6, 7,  // tri0
                          0, 8, 9,  // tri1
                          1, 10, 11 // tri2
                          ),
    gsSPNTriangles_5b(2, 12, 13, // tri0
                      1, 0, 14,  // tri1
                      2, 1, 15,  // tri2
                      5, 3, 16   // tri3
                      ),
    gsSPNTriangles_5b(0, 4, 17, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Larm2_bea_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bea_1_v[83], 6, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 16, 16, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&bea_1_v[89], 13, 6),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 6, 7, // tri0
                          5, 4, 8, // tri1
                          4, 1, 9  // tri2
                          ),
    gsSPNTriangles_5b(5, 10, 11, // tri0
                      2, 3, 12,  // tri1
                      4, 13, 14, // tri2
                      3, 5, 15   // tri3
                      ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          16, 17, 18, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Larm1_bea_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*6, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bea_1_v[102], 6, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 16, 16, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&bea_1_v[108], 12, 6),
    gsSPNTrianglesInit_5b(8,        // tri count
                          4, 6, 7,  // tri0
                          0, 8, 9,  // tri1
                          1, 10, 11 // tri2
                          ),
    gsSPNTriangles_5b(2, 12, 13, // tri0
                      0, 1, 14,  // tri1
                      1, 2, 15,  // tri2
                      3, 5, 16   // tri3
                      ),
    gsSPNTriangles_5b(4, 0, 17, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx chest_bea_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bea_1_v[157], 10, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*6, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_3_txt, G_IM_FMT_CI, 32, 32, 14, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&bea_1_v[167], 21, 10),
    gsSPNTrianglesInit_5b(14,        // tri count
                          0, 2, 10,  // tri0
                          3, 11, 12, // tri1
                          4, 6, 13   // tri2
                          ),
    gsSPNTriangles_5b(7, 1, 14,  // tri0
                      9, 15, 16, // tri1
                      6, 9, 17,  // tri2
                      4, 18, 19  // tri3
                      ),
    gsSPNTriangles_5b(8, 20, 21, // tri0
                      8, 3, 22,  // tri1
                      2, 23, 24, // tri2
                      8, 25, 2   // tri3
                      ),
    gsSPNTriangles_5b(2, 26, 27, // tri0
                      9, 7, 28,  // tri1
                      1, 29, 30, // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&bea_1_v[188], 21, 10),
    gsSPNTrianglesInit_5b(3,         // tri count
                          3, 11, 10, // tri0
                          3, 5, 12,  // tri1
                          9, 13, 14  // tri2
                          ),
    gsSPNTrianglesInit_5b(13,         // tri count
                          15, 16, 17, // tri0
                          17, 18, 15, // tri1
                          16, 15, 19  // tri2
                          ),
    gsSPNTriangles_5b(16, 19, 20, // tri0
                      21, 22, 23, // tri1
                      24, 25, 23, // tri2
                      26, 23, 25  // tri3
                      ),
    gsSPNTriangles_5b(23, 26, 27, // tri0
                      23, 27, 21, // tri1
                      23, 22, 28, // tri2
                      23, 28, 24  // tri3
                      ),
    gsSPNTriangles_5b(19, 29, 30, // tri0
                      20, 19, 30, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx tail1_bea_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bea_1_v[209], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 16, 16, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&bea_1_v[214], 20, 5),
    gsSPNTrianglesInit_5b(7,       // tri count
                          3, 5, 6, // tri0
                          2, 7, 8, // tri1
                          3, 9, 2  // tri2
                          ),
    gsSPNTriangles_5b(0, 2, 10,  // tri0
                      1, 11, 12, // tri1
                      4, 1, 13,  // tri2
                      0, 14, 15  // tri3
                      ),
    gsSPNTrianglesInit_5b(4,          // tri count
                          16, 17, 18, // tri0
                          19, 16, 20, // tri1
                          21, 22, 23  // tri2
                          ),
    gsSPNTriangles_5b(24, 17, 21, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot2_bea_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bea_1_v[285], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*4, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 16, 16, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&bea_1_v[290], 20, 5),
    gsSPNTrianglesInit_5b(10,      // tri count
                          3, 5, 6, // tri0
                          1, 7, 8, // tri1
                          3, 9, 10 // tri2
                          ),
    gsSPNTriangles_5b(1, 4, 11,  // tri0
                      2, 12, 13, // tri1
                      3, 0, 14,  // tri2
                      3, 15, 16  // tri3
                      ),
    gsSPNTriangles_5b(2, 17, 0,  // tri0
                      4, 3, 18,  // tri1
                      1, 19, 20, // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(2,          // tri count
                          21, 22, 23, // tri0
                          21, 23, 24, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot1_bea_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bea_1_v[310], 7, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&bea_1_v[317], 19, 7),
    gsSPNTrianglesInit_5b(11,      // tri count
                          2, 7, 4, // tri0
                          2, 0, 8, // tri1
                          3, 9, 1  // tri2
                          ),
    gsSPNTriangles_5b(4, 10, 5,  // tri0
                      4, 11, 12, // tri1
                      3, 6, 13,  // tri2
                      5, 14, 15  // tri3
                      ),
    gsSPNTriangles_5b(4, 17, 16, // tri0
                      0, 18, 19, // tri1
                      6, 5, 20,  // tri2
                      3, 21, 22  // tri3
                      ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          23, 24, 25, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot2_bea_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bea_1_v[234], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 16, 16, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&bea_1_v[239], 20, 5),
    gsSPNTrianglesInit_5b(10,      // tri count
                          3, 5, 6, // tri0
                          1, 7, 8, // tri1
                          3, 9, 10 // tri2
                          ),
    gsSPNTriangles_5b(4, 1, 11,  // tri0
                      2, 12, 13, // tri1
                      0, 14, 15, // tri2
                      0, 3, 16   // tri3
                      ),
    gsSPNTriangles_5b(0, 17, 2,  // tri0
                      3, 4, 18,  // tri1
                      1, 19, 20, // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(2,          // tri count
                          21, 22, 23, // tri0
                          21, 23, 24, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot1_bea_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bea_1_v[259], 7, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&bea_1_v[266], 19, 7),
    gsSPNTrianglesInit_5b(11,      // tri count
                          4, 7, 2, // tri0
                          0, 2, 8, // tri1
                          1, 9, 3  // tri2
                          ),
    gsSPNTriangles_5b(5, 10, 4,  // tri0
                      4, 11, 12, // tri1
                      6, 3, 13,  // tri2
                      5, 14, 15  // tri3
                      ),
    gsSPNTriangles_5b(4, 17, 16, // tri0
                      0, 18, 19, // tri1
                      5, 6, 20,  // tri2
                      3, 21, 22  // tri3
                      ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          23, 24, 25, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx base_bea_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_3_txt, G_IM_FMT_CI, 32, 32, 14, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bea_1_v[336], 20, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,    // tri0
                      10, 5, 4,   // tri1
                      11, 12, 13, // tri2
                      5, 14, 6    // tri3
                      ),
    gsSPNTriangles_5b(0, 3, 14,   // tri0
                      5, 15, 14,  // tri1
                      13, 16, 17, // tri2
                      17, 18, 9   // tri3
                      ),
    gsSPNTriangles_5b(14, 15, 0,  // tri0
                      9, 19, 17,  // tri1
                      17, 19, 13, // tri2
                      13, 12, 16  // tri3
                      ),
    gsSPNTriangles_5b(7, 9, 18, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&bea_1_v[356], 14, 0),
    gsSPNTrianglesInit_5b(11,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 5, 7,  // tri0
                      6, 9, 10, // tri1
                      8, 9, 5,  // tri2
                      6, 10, 7  // tri3
                      ),
    gsSPNTriangles_5b(3, 4, 11,  // tri0
                      12, 11, 4, // tri1
                      3, 1, 0,   // tri2
                      13, 1, 3   // tri3
                      ),
    gsSPEndDisplayList(),
};

// clang-format off
static cKF_Joint_R_c cKF_je_r_bea_1_tbl[] = {
    /* joint 0 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,1000,0 },
    /* joint 1 */ { base_bea_model, 4, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 2 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,-500,0 },
    /* joint 3 */ { Lfoot1_bea_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 4 */ { Lfoot2_bea_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 5 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 6 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,500,0 },
    /* joint 7 */ { Rfoot1_bea_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 8 */ { Rfoot2_bea_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 9 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 10 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 325,0,-973 },
    /* joint 11 */ { tail1_bea_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 12 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 650,0,0 },
    /* joint 13 */ { chest_bea_model, 3, cKF_JOINT_FLAG_DISP_OPA, 939,0,0 },
    /* joint 14 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 775,-700,0 },
    /* joint 15 */ { Larm1_bea_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 16 */ { Larm2_bea_model, 0, cKF_JOINT_FLAG_DISP_OPA, 703,0,0 },
    /* joint 17 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 775,700,0 },
    /* joint 18 */ { Rarm1_bea_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 19 */ { Rarm2_bea_model, 1, cKF_JOINT_FLAG_DISP_OPA, 700,0,0 },
    /* joint 20 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 700,0,0 },
    /* joint 21 */ { NULL, 2, cKF_JOINT_FLAG_DISP_OPA, 1265,0,0 },
    /* joint 22 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,600 },
    /* joint 23 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 24 */ { head_bea_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 25 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 1500,0,0 },
};
// clang-format on

extern cKF_Skeleton_R_c cKF_bs_r_bea_1 = { 26, 12, cKF_je_r_bea_1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_npc_model_mdl_bea_1_c(void) {
    pc_load_asset("assets/npc/mdl/bea_1_v.bin", bea_1_v, 0x1720, 0x37EEB8, 0, 2);
}
#endif

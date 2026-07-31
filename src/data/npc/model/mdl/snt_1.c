#include "c_keyframe.h"
#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
static Vtx snt_1_v[0x13C0 / sizeof(Vtx)];
#else
static Vtx snt_1_v[] = {
#include "assets/npc/mdl/snt_1_v.inc"
};
#endif

static Gfx head_snt_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&snt_1_v[0], 26, 0),
    gsSPNTrianglesInit_5b(10,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          1, 4, 5  // tri2
                          ),
    gsSPNTriangles_5b(1, 5, 2, // tri0
                      5, 6, 7, // tri1
                      6, 0, 3, // tri2
                      7, 2, 5  // tri3
                      ),
    gsSPNTriangles_5b(3, 2, 7, // tri0
                      5, 4, 6, // tri1
                      7, 6, 3, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_1_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(19,         // tri count
                          8, 9, 10,   // tri0
                          11, 12, 13, // tri1
                          13, 14, 11  // tri2
                          ),
    gsSPNTriangles_5b(8, 15, 9,   // tri0
                      16, 12, 17, // tri1
                      17, 8, 16,  // tri2
                      15, 8, 18   // tri3
                      ),
    gsSPNTriangles_5b(19, 20, 18, // tri0
                      21, 11, 22, // tri1
                      23, 19, 8,  // tri2
                      23, 8, 17   // tri3
                      ),
    gsSPNTriangles_5b(10, 16, 8,  // tri0
                      14, 24, 11, // tri1
                      12, 11, 17, // tri2
                      17, 11, 21  // tri3
                      ),
    gsSPNTriangles_5b(17, 21, 23, // tri0
                      18, 8, 19,  // tri1
                      22, 25, 21, // tri2
                      22, 11, 24  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x040, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&snt_1_v[26], 29, 0),
    gsSPNTrianglesInit_5b(37,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(9, 10, 11, // tri0
                      5, 9, 12,  // tri1
                      5, 12, 13, // tri2
                      12, 9, 14  // tri3
                      ),
    gsSPNTriangles_5b(13, 15, 16, // tri0
                      5, 16, 3,   // tri1
                      11, 14, 9,  // tri2
                      17, 2, 1    // tri3
                      ),
    gsSPNTriangles_5b(4, 3, 18,   // tri0
                      8, 7, 19,   // tri1
                      18, 11, 10, // tri2
                      0, 20, 1    // tri3
                      ),
    gsSPNTriangles_5b(21, 2, 17, // tri0
                      8, 11, 6,  // tri1
                      1, 7, 6,   // tri2
                      1, 6, 17   // tri3
                      ),
    gsSPNTriangles_5b(11, 8, 22, // tri0
                      7, 1, 20,  // tri1
                      9, 5, 4,   // tri2
                      9, 4, 10   // tri3
                      ),
    gsSPNTriangles_5b(23, 19, 20, // tri0
                      22, 14, 11, // tri1
                      17, 6, 18,  // tri2
                      3, 21, 17   // tri3
                      ),
    gsSPNTriangles_5b(18, 6, 11, // tri0
                      17, 18, 3, // tri1
                      20, 19, 7, // tri2
                      0, 24, 25  // tri3
                      ),
    gsSPNTriangles_5b(14, 26, 12, // tri0
                      27, 26, 14, // tri1
                      16, 5, 13,  // tri2
                      16, 15, 28  // tri3
                      ),
    gsSPNTriangles_5b(18, 10, 4, // tri0
                      19, 22, 8, // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_2_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 252, 255, 255),
    gsSPVertex(&snt_1_v[55], 23, 0),
    gsSPNTrianglesInit_5b(5,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 2, 4  // tri2
                          ),
    gsSPNTriangles_5b(2, 6, 0, // tri0
                      4, 3, 6, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x080, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPNTrianglesInit_5b(4,        // tri count
                          7, 8, 9,  // tri0
                          9, 10, 7, // tri1
                          7, 10, 11 // tri2
                          ),
    gsSPNTriangles_5b(11, 8, 7, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x100, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(11,         // tri count
                          12, 13, 14, // tri0
                          15, 16, 17, // tri1
                          17, 16, 18  // tri2
                          ),
    gsSPNTriangles_5b(18, 19, 17, // tri0
                      17, 19, 20, // tri1
                      12, 21, 22, // tri2
                      17, 12, 14  // tri3
                      ),
    gsSPNTriangles_5b(17, 14, 15, // tri0
                      22, 13, 12, // tri1
                      20, 21, 12, // tri2
                      12, 17, 20  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x180, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&snt_1_v[78], 16, 0),
    gsSPNTrianglesInit_5b(10,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          1, 6, 2  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 5,  // tri0
                      5, 8, 3,  // tri1
                      9, 10, 2, // tri2
                      11, 12, 3 // tri3
                      ),
    gsSPNTriangles_5b(1, 13, 6,  // tri0
                      3, 14, 11, // tri1
                      2, 15, 9,  // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x200, G_IM_FMT_CI, 32, 24, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&snt_1_v[94], 17, 0),
    gsSPNTrianglesInit_5b(30,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 5,  // tri0
                      7, 9, 10, // tri1
                      11, 8, 7, // tri2
                      11, 7, 12 // tri3
                      ),
    gsSPNTriangles_5b(12, 13, 3, // tri0
                      4, 14, 15, // tri1
                      15, 14, 2, // tri2
                      14, 4, 2   // tri3
                      ),
    gsSPNTriangles_5b(10, 13, 12, // tri0
                      10, 9, 13,  // tri1
                      12, 7, 10,  // tri2
                      4, 6, 0     // tri3
                      ),
    gsSPNTriangles_5b(4, 0, 2,  // tri0
                      5, 8, 11, // tri1
                      5, 11, 1, // tri2
                      0, 6, 5   // tri3
                      ),
    gsSPNTriangles_5b(0, 5, 1,   // tri0
                      11, 12, 1, // tri1
                      16, 9, 7,  // tri2
                      3, 13, 9   // tri3
                      ),
    gsSPNTriangles_5b(3, 9, 16, // tri0
                      16, 7, 5, // tri1
                      1, 12, 3, // tri2
                      4, 16, 5  // tri3
                      ),
    gsSPNTriangles_5b(16, 4, 15, // tri0
                      3, 15, 2,  // tri1
                      16, 15, 3, // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&snt_1_v[111], 17, 0),
    gsSPNTrianglesInit_5b(30,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 8,  // tri0
                      9, 10, 8, // tri1
                      11, 8, 7, // tri2
                      11, 7, 12 // tri3
                      ),
    gsSPNTriangles_5b(3, 13, 11, // tri0
                      14, 15, 6, // tri1
                      0, 15, 14, // tri2
                      0, 6, 15   // tri3
                      ),
    gsSPNTriangles_5b(11, 13, 9, // tri0
                      13, 10, 9, // tri1
                      9, 8, 11,  // tri2
                      0, 2, 4    // tri3
                      ),
    gsSPNTriangles_5b(0, 4, 6,  // tri0
                      1, 12, 7, // tri1
                      1, 7, 5,  // tri2
                      1, 5, 4   // tri3
                      ),
    gsSPNTriangles_5b(1, 4, 2,   // tri0
                      1, 11, 12, // tri1
                      8, 10, 16, // tri2
                      16, 10, 13 // tri3
                      ),
    gsSPNTriangles_5b(16, 13, 3, // tri0
                      5, 8, 16,  // tri1
                      3, 11, 1,  // tri2
                      5, 16, 6   // tri3
                      ),
    gsSPNTriangles_5b(14, 6, 16, // tri0
                      0, 14, 3,  // tri1
                      3, 14, 16, // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Larm2_snt_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*6, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&snt_1_v[128], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&snt_1_v[132], 16, 4),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 4, 5, // tri0
                          3, 6, 7, // tri1
                          3, 8, 9  // tri2
                          ),
    gsSPNTriangles_5b(1, 0, 10,  // tri0
                      3, 1, 11,  // tri1
                      0, 12, 13, // tri2
                      0, 2, 14   // tri3
                      ),
    gsSPNTriangles_5b(2, 3, 15, // tri0
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

static Gfx Larm1_snt_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&snt_1_v[148], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*6, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&snt_1_v[151], 11, 3),
    gsSPNTrianglesInit_5b(7,       // tri count
                          2, 3, 4, // tri0
                          0, 5, 6, // tri1
                          0, 1, 7  // tri2
                          ),
    gsSPNTriangles_5b(1, 2, 8,   // tri0
                      1, 10, 9,  // tri1
                      2, 12, 11, // tri2
                      2, 0, 13   // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx chest_snt_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&snt_1_v[162], 6, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x540, G_IM_FMT_CI, 16, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&snt_1_v[168], 22, 6),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 4, 6, // tri0
                          4, 3, 7, // tri1
                          3, 8, 9  // tri2
                          ),
    gsSPNTriangles_5b(1, 0, 10,  // tri0
                      2, 1, 11,  // tri1
                      2, 12, 13, // tri2
                      0, 14, 15  // tri3
                      ),
    gsSPNTriangles_5b(0, 16, 17, // tri0
                      3, 18, 19, // tri1
                      5, 20, 21, // tri2
                      3, 5, 22   // tri3
                      ),
    gsSPNTriangles_5b(2, 23, 24, // tri0
                      2, 25, 5,  // tri1
                      1, 26, 27, // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x3C0, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&snt_1_v[190], 25, 0),
    gsSPNTrianglesInit_5b(22,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 4, // tri1
                          0, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(6, 5, 7, // tri0
                      2, 8, 0, // tri1
                      8, 9, 5, // tri2
                      9, 10, 7 // tri3
                      ),
    gsSPNTriangles_5b(7, 10, 11, // tri0
                      8, 2, 12,  // tri1
                      9, 12, 13, // tri2
                      10, 13, 14 // tri3
                      ),
    gsSPNTriangles_5b(6, 3, 1,  // tri0
                      12, 9, 8, // tri1
                      5, 0, 8,  // tri2
                      7, 5, 9   // tri3
                      ),
    gsSPNTriangles_5b(13, 10, 9, // tri0
                      13, 12, 4, // tri1
                      2, 1, 4,   // tri2
                      6, 1, 0    // tri3
                      ),
    gsSPNTriangles_5b(4, 12, 2,   // tri0
                      11, 10, 15, // tri1
                      10, 14, 15, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x440, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(8,          // tri count
                          16, 17, 18, // tri0
                          16, 19, 17, // tri1
                          19, 20, 21  // tri2
                          ),
    gsSPNTriangles_5b(19, 16, 20, // tri0
                      21, 22, 19, // tri1
                      17, 19, 22, // tri2
                      23, 17, 22  // tri3
                      ),
    gsSPNTriangles_5b(21, 20, 24, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x540, G_IM_FMT_CI, 16, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&snt_1_v[215], 28, 0),
    gsSPNTrianglesInit_5b(18,      // tri count
                          0, 1, 2, // tri0
                          2, 3, 0, // tri1
                          4, 1, 0  // tri2
                          ),
    gsSPNTriangles_5b(3, 5, 0, // tri0
                      3, 6, 7, // tri1
                      8, 4, 0, // tri2
                      2, 6, 3  // tri3
                      ),
    gsSPNTriangles_5b(8, 9, 10,  // tri0
                      0, 5, 8,   // tri1
                      11, 5, 12, // tri2
                      7, 12, 3   // tri3
                      ),
    gsSPNTriangles_5b(11, 8, 5, // tri0
                      8, 11, 9, // tri1
                      13, 6, 1, // tri2
                      10, 14, 4 // tri3
                      ),
    gsSPNTriangles_5b(14, 13, 1, // tri0
                      10, 4, 8,  // tri1
                      1, 6, 2,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 253, 255, 255),
    gsSPNTrianglesInit_5b(19,         // tri count
                          15, 16, 17, // tri0
                          15, 18, 19, // tri1
                          20, 15, 19  // tri2
                          ),
    gsSPNTriangles_5b(21, 16, 20, // tri0
                      21, 20, 19, // tri1
                      22, 23, 16, // tri2
                      22, 16, 21  // tri3
                      ),
    gsSPNTriangles_5b(24, 25, 19, // tri0
                      25, 26, 22, // tri1
                      26, 27, 22, // tri2
                      24, 19, 18  // tri3
                      ),
    gsSPNTriangles_5b(25, 24, 26, // tri0
                      27, 18, 22, // tri1
                      27, 26, 24, // tri2
                      25, 21, 19  // tri3
                      ),
    gsSPNTriangles_5b(25, 22, 21, // tri0
                      18, 27, 24, // tri1
                      17, 22, 18, // tri2
                      17, 18, 15  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot2_snt_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&snt_1_v[273], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*4, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x640, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&snt_1_v[278], 16, 5),
    gsSPNTrianglesInit_5b(7,       // tri count
                          4, 0, 5, // tri0
                          0, 7, 6, // tri1
                          2, 9, 8  // tri2
                          ),
    gsSPNTriangles_5b(0, 1, 10, // tri0
                      1, 3, 11, // tri1
                      2, 4, 12, // tri2
                      1, 13, 14 // tri3
                      ),
    gsSPNTrianglesInit_5b(3,          // tri count
                          15, 16, 17, // tri0
                          18, 19, 20, // tri1
                          18, 17, 19  // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot1_snt_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x640, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&snt_1_v[294], 9, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 4, // tri1
                          1, 5, 2  // tri2
                          ),
    gsSPNTriangles_5b(6, 4, 3, // tri0
                      6, 3, 7, // tri1
                      7, 8, 6, // tri2
                      4, 5, 1  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot2_snt_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&snt_1_v[243], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x640, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&snt_1_v[248], 16, 5),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 4, 5, // tri0
                          0, 7, 6, // tri1
                          2, 9, 8  // tri2
                          ),
    gsSPNTriangles_5b(1, 0, 10, // tri0
                      3, 1, 11, // tri1
                      4, 2, 12, // tri2
                      1, 13, 14 // tri3
                      ),
    gsSPNTrianglesInit_5b(3,          // tri count
                          15, 16, 17, // tri0
                          18, 19, 20, // tri1
                          19, 15, 20  // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot1_snt_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x640, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&snt_1_v[264], 9, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 1, // tri1
                          0, 5, 1  // tri2
                          ),
    gsSPNTriangles_5b(4, 3, 6, // tri0
                      7, 4, 6, // tri1
                      6, 8, 7, // tri2
                      1, 5, 3  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx base_snt_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x040, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&snt_1_v[303], 13, 0),
    gsSPNTrianglesInit_5b(18,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 4, // tri1
                          0, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 1,   // tri0
                      7, 1, 4,   // tri1
                      9, 10, 11, // tri2
                      11, 12, 9  // tri3
                      ),
    gsSPNTriangles_5b(0, 2, 5,  // tri0
                      9, 7, 10, // tri1
                      12, 2, 8, // tri2
                      8, 7, 9   // tri3
                      ),
    gsSPNTriangles_5b(12, 11, 6, // tri0
                      5, 12, 6,  // tri1
                      6, 3, 0,   // tri2
                      4, 1, 0    // tri3
                      ),
    gsSPNTriangles_5b(8, 9, 12, // tri0
                      2, 1, 8,  // tri1
                      12, 5, 2, // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPEndDisplayList(),
};

// clang-format off
static cKF_Joint_R_c cKF_je_r_snt_1_tbl[] = {
    /* joint 0 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,1000,0 },
    /* joint 1 */ { base_snt_model, 4, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 2 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,-250,0 },
    /* joint 3 */ { Lfoot1_snt_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 4 */ { Lfoot2_snt_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 5 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 6 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,250,0 },
    /* joint 7 */ { Rfoot1_snt_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 8 */ { Rfoot2_snt_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 9 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 10 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 200,0,-500 },
    /* joint 11 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 12 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 650,0,0 },
    /* joint 13 */ { chest_snt_model, 3, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 14 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 850,-500,0 },
    /* joint 15 */ { Larm1_snt_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 16 */ { Larm2_snt_model, 0, cKF_JOINT_FLAG_DISP_OPA, 558,0,0 },
    /* joint 17 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 850,500,0 },
    /* joint 18 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 19 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 550,0,0 },
    /* joint 20 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 550,0,0 },
    /* joint 21 */ { NULL, 2, cKF_JOINT_FLAG_DISP_OPA, 1201,0,0 },
    /* joint 22 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 700,0,1250 },
    /* joint 23 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 24 */ { head_snt_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 25 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 1500,0,0 },
};
// clang-format on

extern cKF_Skeleton_R_c cKF_bs_r_snt_1 = { 26, 9, cKF_je_r_snt_1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_npc_model_mdl_snt_1_c(void) {
    pc_load_asset("assets/npc/mdl/snt_1_v.bin", snt_1_v, 0x13C0, 0x658F88, 0, 2);
}
#endif

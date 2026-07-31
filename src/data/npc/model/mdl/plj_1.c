#include "c_keyframe.h"
#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
static Vtx plj_1_v[0x16A0 / sizeof(Vtx)];
#else
static Vtx plj_1_v[] = {
#include "assets/npc/mdl/plj_1_v.inc"
};
#endif

static Gfx head_plj_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&plj_1_v[0], 18, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(9, 10, 11,  // tri0
                      12, 13, 14, // tri1
                      15, 16, 17, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x080, G_IM_FMT_CI, 16, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&plj_1_v[18], 21, 0),
    gsSPNTrianglesInit_5b(26,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          5, 6, 3  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 6,    // tri0
                      9, 10, 11,  // tri1
                      12, 13, 14, // tri2
                      11, 10, 7   // tri3
                      ),
    gsSPNTriangles_5b(13, 2, 1,   // tri0
                      2, 15, 0,   // tri1
                      16, 17, 18, // tri2
                      14, 9, 12   // tri3
                      ),
    gsSPNTriangles_5b(6, 5, 17, // tri0
                      9, 14, 1, // tri1
                      6, 8, 3,  // tri2
                      4, 3, 19  // tri3
                      ),
    gsSPNTriangles_5b(1, 20, 9,  // tri0
                      6, 16, 7,  // tri1
                      1, 14, 13, // tri2
                      17, 16, 6  // tri3
                      ),
    gsSPNTriangles_5b(18, 12, 11, // tri0
                      7, 16, 18,  // tri1
                      11, 12, 9,  // tri2
                      18, 11, 7   // tri3
                      ),
    gsSPNTriangles_5b(19, 0, 15, // tri0
                      15, 4, 19, // tri1
                      0, 20, 1,  // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x180, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&plj_1_v[39], 30, 0),
    gsSPNTrianglesInit_5b(22,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 3  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 2,    // tri0
                      8, 9, 10,   // tri1
                      10, 11, 12, // tri2
                      10, 12, 8   // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 1, // tri0
                      9, 8, 7,   // tri1
                      2, 14, 6,  // tri2
                      15, 12, 11 // tri3
                      ),
    gsSPNTriangles_5b(7, 15, 3, // tri0
                      7, 3, 2,  // tri1
                      0, 5, 16, // tri2
                      0, 16, 17 // tri3
                      ),
    gsSPNTriangles_5b(7, 6, 9,   // tri0
                      11, 4, 15, // tri1
                      17, 13, 1, // tri2
                      1, 0, 17   // tri3
                      ),
    gsSPNTriangles_5b(3, 15, 4,  // tri0
                      15, 7, 8,  // tri1
                      15, 8, 12, // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_2_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(14,         // tri count
                          18, 19, 20, // tri0
                          21, 22, 20, // tri1
                          18, 22, 23  // tri2
                          ),
    gsSPNTriangles_5b(18, 24, 19, // tri0
                      25, 23, 22, // tri1
                      26, 27, 23, // tri2
                      23, 25, 28  // tri3
                      ),
    gsSPNTriangles_5b(21, 29, 22, // tri0
                      20, 19, 21, // tri1
                      23, 28, 26, // tri2
                      20, 22, 18  // tri3
                      ),
    gsSPNTriangles_5b(27, 24, 18, // tri0
                      18, 23, 27, // tri1
                      22, 29, 25, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_1_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&plj_1_v[69], 10, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          5, 6, 3  // tri2
                          ),
    gsSPNTriangles_5b(1, 7, 8, // tri0
                      8, 9, 1, // tri1
                      0, 7, 1, // tri2
                      2, 5, 4  // tri3
                      ),
    gsSPNTriangles_5b(2, 4, 0, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rarm2_plj_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&plj_1_v[116], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*11, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x1C0, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&plj_1_v[120], 13, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          2, 1, 4, // tri0
                          2, 5, 0, // tri1
                          1, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(0, 8, 9,  // tri0
                      3, 0, 10, // tri1
                      1, 3, 11, // tri2
                      2, 12, 13 // tri3
                      ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          14, 15, 16, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rarm1_plj_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&plj_1_v[133], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x1C0, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&plj_1_v[137], 16, 4),
    gsSPNTrianglesInit_5b(8,       // tri count
                          3, 4, 5, // tri0
                          3, 2, 6, // tri1
                          1, 0, 7  // tri2
                          ),
    gsSPNTriangles_5b(0, 8, 9,   // tri0
                      2, 10, 11, // tri1
                      1, 12, 13, // tri2
                      0, 3, 14   // tri3
                      ),
    gsSPNTriangles_5b(1, 15, 2, // tri0
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

static Gfx Larm2_plj_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&plj_1_v[79], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*9, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x1C0, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&plj_1_v[83], 13, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 3, 4, // tri0
                          3, 1, 5, // tri1
                          2, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(0, 8, 9,   // tri0
                      1, 10, 11, // tri1
                      0, 12, 2,  // tri2
                      1, 2, 13   // tri3
                      ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          14, 15, 16, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Larm1_plj_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&plj_1_v[96], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x1C0, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&plj_1_v[100], 16, 4),
    gsSPNTrianglesInit_5b(8,       // tri count
                          3, 4, 5, // tri0
                          1, 3, 6, // tri1
                          3, 0, 7  // tri2
                          ),
    gsSPNTriangles_5b(2, 8, 9,   // tri0
                      2, 10, 0,  // tri1
                      0, 11, 12, // tri2
                      2, 1, 13   // tri3
                      ),
    gsSPNTriangles_5b(1, 14, 15, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(2,          // tri count
                          16, 17, 18, // tri0
                          19, 18, 17, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx chest_plj_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&plj_1_v[153], 10, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&plj_1_v[163], 10, 10),
    gsSPNTrianglesInit_5b(6,         // tri count
                          2, 10, 11, // tri0
                          0, 12, 13, // tri1
                          9, 0, 14   // tri2
                          ),
    gsSPNTriangles_5b(2, 9, 15,  // tri0
                      0, 16, 17, // tri1
                      2, 18, 19, // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 32, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&plj_1_v[173], 18, 10),
    gsSPNTrianglesInit_5b(12,       // tri count
                          5, 4, 10, // tri0
                          7, 8, 11, // tri1
                          6, 12, 13 // tri2
                          ),
    gsSPNTriangles_5b(8, 3, 14,  // tri0
                      7, 15, 16, // tri1
                      4, 17, 18, // tri2
                      1, 5, 19   // tri3
                      ),
    gsSPNTriangles_5b(6, 7, 20,  // tri0
                      8, 21, 22, // tri1
                      5, 23, 24, // tri2
                      4, 6, 25   // tri3
                      ),
    gsSPNTriangles_5b(6, 26, 27, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x240, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&plj_1_v[191], 24, 0),
    gsSPNTrianglesInit_5b(12,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 6, 7,   // tri0
                      8, 9, 10,  // tri1
                      8, 10, 11, // tri2
                      9, 0, 3    // tri3
                      ),
    gsSPNTriangles_5b(9, 3, 10,  // tri0
                      12, 5, 4,  // tri1
                      12, 4, 13, // tri2
                      3, 2, 11   // tri3
                      ),
    gsSPNTriangles_5b(3, 11, 10, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(9,          // tri count
                          14, 15, 16, // tri0
                          14, 17, 15, // tri1
                          18, 19, 20  // tri2
                          ),
    gsSPNTriangles_5b(14, 21, 17, // tri0
                      14, 20, 21, // tri1
                      18, 20, 14, // tri2
                      18, 14, 22  // tri3
                      ),
    gsSPNTriangles_5b(16, 22, 14, // tri0
                      15, 17, 23, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 32, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&plj_1_v[215], 12, 0),
    gsSPNTrianglesInit_5b(11,      // tri count
                          0, 1, 2, // tri0
                          1, 0, 3, // tri1
                          1, 4, 5  // tri2
                          ),
    gsSPNTriangles_5b(6, 2, 1, // tri0
                      3, 4, 1, // tri1
                      7, 4, 3, // tri2
                      1, 8, 6  // tri3
                      ),
    gsSPNTriangles_5b(5, 8, 1,  // tri0
                      9, 5, 4,  // tri1
                      2, 6, 10, // tri2
                      0, 2, 11  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx tail1_plj_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x500, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&plj_1_v[252], 7, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          2, 3, 0, // tri1
                          4, 3, 2  // tri2
                          ),
    gsSPNTriangles_5b(1, 5, 4, // tri0
                      2, 6, 4, // tri1
                      4, 6, 1, // tri2
                      0, 5, 1  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx tail2_plj_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&plj_1_v[227], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*6, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x500, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&plj_1_v[231], 21, 4),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 4, 5, // tri0
                          0, 6, 7, // tri1
                          3, 1, 8  // tri2
                          ),
    gsSPNTriangles_5b(3, 9, 10,  // tri0
                      2, 11, 12, // tri1
                      2, 3, 13,  // tri2
                      0, 2, 14   // tri3
                      ),
    gsSPNTriangles_5b(1, 0, 15, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPNTrianglesInit_5b(12,         // tri count
                          16, 17, 18, // tri0
                          19, 17, 20, // tri1
                          18, 21, 22  // tri2
                          ),
    gsSPNTriangles_5b(23, 22, 21, // tri0
                      23, 21, 20, // tri1
                      20, 21, 19, // tri2
                      20, 17, 16  // tri3
                      ),
    gsSPNTriangles_5b(20, 16, 23, // tri0
                      21, 18, 19, // tri1
                      19, 18, 17, // tri2
                      18, 24, 16  // tri3
                      ),
    gsSPNTriangles_5b(22, 24, 18, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot2_plj_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&plj_1_v[300], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*4, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x580, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&plj_1_v[305], 17, 5),
    gsSPNTrianglesInit_5b(9,       // tri count
                          3, 4, 5, // tri0
                          3, 6, 7, // tri1
                          0, 8, 9  // tri2
                          ),
    gsSPNTriangles_5b(3, 10, 11, // tri0
                      2, 3, 12,  // tri1
                      1, 2, 13,  // tri2
                      0, 14, 15  // tri3
                      ),
    gsSPNTriangles_5b(4, 0, 16,  // tri0
                      2, 17, 18, // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          19, 20, 21, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot1_plj_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&plj_1_v[322], 6, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x580, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&plj_1_v[328], 13, 6),
    gsSPNTrianglesInit_5b(9,       // tri count
                          4, 6, 7, // tri0
                          5, 3, 8, // tri1
                          3, 9, 10 // tri2
                          ),
    gsSPNTriangles_5b(1, 4, 11, // tri0
                      0, 1, 12, // tri1
                      2, 13, 3, // tri2
                      2, 14, 15 // tri3
                      ),
    gsSPNTriangles_5b(2, 0, 16,  // tri0
                      1, 17, 18, // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot2_plj_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&plj_1_v[259], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x580, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&plj_1_v[264], 17, 5),
    gsSPNTrianglesInit_5b(9,       // tri count
                          4, 3, 5, // tri0
                          3, 6, 7, // tri1
                          3, 2, 8  // tri2
                          ),
    gsSPNTriangles_5b(2, 0, 9,   // tri0
                      1, 4, 10,  // tri1
                      1, 11, 12, // tri2
                      2, 13, 14  // tri3
                      ),
    gsSPNTriangles_5b(3, 15, 16, // tri0
                      1, 17, 18, // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          19, 20, 21, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot1_plj_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&plj_1_v[281], 6, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x580, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&plj_1_v[287], 13, 6),
    gsSPNTrianglesInit_5b(9,       // tri count
                          4, 6, 3, // tri0
                          3, 7, 8, // tri1
                          5, 1, 9  // tri2
                          ),
    gsSPNTriangles_5b(5, 10, 11, // tri0
                      2, 3, 12,  // tri1
                      1, 0, 13,  // tri2
                      0, 2, 14   // tri3
                      ),
    gsSPNTriangles_5b(2, 15, 16, // tri0
                      1, 17, 18, // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx base_plj_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x580, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&plj_1_v[341], 21, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(9, 10, 11, // tri0
                      12, 4, 3,  // tri1
                      3, 5, 13,  // tri2
                      10, 14, 15 // tri3
                      ),
    gsSPNTriangles_5b(6, 16, 17, // tri0
                      9, 12, 3,  // tri1
                      3, 13, 8,  // tri2
                      15, 11, 10 // tri3
                      ),
    gsSPNTriangles_5b(18, 19, 17, // tri0
                      14, 19, 18, // tri1
                      18, 15, 14, // tri2
                      8, 13, 6    // tri3
                      ),
    gsSPNTriangles_5b(17, 7, 6,  // tri0
                      11, 12, 9, // tri1
                      3, 20, 9,  // tri2
                      17, 16, 18 // tri3
                      ),
    gsSPNTriangles_5b(8, 20, 3, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPEndDisplayList(),
};

// clang-format off
static cKF_Joint_R_c cKF_je_r_plj_1_tbl[] = {
    /* joint 0 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,1000,0 },
    /* joint 1 */ { base_plj_model, 4, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 2 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,-250,0 },
    /* joint 3 */ { Lfoot1_plj_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 4 */ { Lfoot2_plj_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 5 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 6 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,250,0 },
    /* joint 7 */ { Rfoot1_plj_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 8 */ { Rfoot2_plj_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 9 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 10 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 150,0,-500 },
    /* joint 11 */ { tail1_plj_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 12 */ { tail2_plj_model, 0, cKF_JOINT_FLAG_DISP_OPA, 650,0,0 },
    /* joint 13 */ { chest_plj_model, 3, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 14 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 800,-900,0 },
    /* joint 15 */ { Larm1_plj_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 16 */ { Larm2_plj_model, 0, cKF_JOINT_FLAG_DISP_OPA, 558,0,0 },
    /* joint 17 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 800,900,0 },
    /* joint 18 */ { Rarm1_plj_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 19 */ { Rarm2_plj_model, 1, cKF_JOINT_FLAG_DISP_OPA, 550,0,0 },
    /* joint 20 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 550,0,0 },
    /* joint 21 */ { NULL, 2, cKF_JOINT_FLAG_DISP_OPA, 1201,0,0 },
    /* joint 22 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 700,0,1250 },
    /* joint 23 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 24 */ { head_plj_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 25 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 1300,0,0 },
};
// clang-format on

extern cKF_Skeleton_R_c cKF_bs_r_plj_1 = { 26, 13, cKF_je_r_plj_1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_npc_model_mdl_plj_1_c(void) {
    pc_load_asset("assets/npc/mdl/plj_1_v.bin", plj_1_v, 0x16A0, 0x548B40, 0, 2);
}
#endif

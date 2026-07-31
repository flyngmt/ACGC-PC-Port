#include "c_keyframe.h"
#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
static Vtx bpt_1_v[0x16E0 / sizeof(Vtx)];
#else
static Vtx bpt_1_v[] = {
#include "assets/npc/mdl/bpt_1_v.inc"
};
#endif

static Gfx head_bpt_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x040, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bpt_1_v[21], 25, 0),
    gsSPNTrianglesInit_5b(34,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 6, 5,   // tri0
                      8, 9, 10,  // tri1
                      11, 12, 5, // tri2
                      5, 12, 10  // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 15, // tri0
                      10, 12, 8,  // tri1
                      13, 9, 16,  // tri2
                      13, 16, 17  // tri3
                      ),
    gsSPNTriangles_5b(9, 8, 16,   // tri0
                      17, 14, 13, // tri1
                      0, 18, 19,  // tri2
                      17, 16, 20  // tri3
                      ),
    gsSPNTriangles_5b(17, 20, 21, // tri0
                      20, 16, 8,  // tri1
                      21, 14, 17, // tri2
                      14, 21, 19  // tri3
                      ),
    gsSPNTriangles_5b(14, 19, 18, // tri0
                      15, 14, 18, // tri1
                      11, 4, 22,  // tri2
                      15, 18, 0   // tri3
                      ),
    gsSPNTriangles_5b(23, 20, 11, // tri0
                      11, 8, 12,  // tri1
                      24, 23, 22, // tri2
                      11, 20, 8   // tri3
                      ),
    gsSPNTriangles_5b(19, 23, 24, // tri0
                      23, 19, 21, // tri1
                      21, 20, 23, // tri2
                      19, 1, 0    // tri3
                      ),
    gsSPNTriangles_5b(5, 4, 11,   // tri0
                      22, 23, 11, // tri1
                      24, 1, 19,  // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_1_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&bpt_1_v[46], 27, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 5, 4, // tri0
                      5, 7, 4, // tri1
                      4, 3, 8, // tri2
                      3, 1, 0  // tri3
                      ),
    gsSPNTriangles_5b(9, 7, 6, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x080, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(24,         // tri count
                          10, 11, 12, // tri0
                          13, 14, 10, // tri1
                          10, 15, 16  // tri2
                          ),
    gsSPNTriangles_5b(17, 18, 19, // tri0
                      20, 21, 12, // tri1
                      14, 18, 17, // tri2
                      10, 22, 13  // tri3
                      ),
    gsSPNTriangles_5b(23, 15, 10, // tri0
                      11, 16, 24, // tri1
                      24, 20, 11, // tri2
                      15, 23, 17  // tri3
                      ),
    gsSPNTriangles_5b(13, 18, 14, // tri0
                      11, 20, 12, // tri1
                      24, 25, 21, // tri2
                      13, 19, 18  // tri3
                      ),
    gsSPNTriangles_5b(12, 22, 10, // tri0
                      16, 11, 10, // tri1
                      10, 14, 23, // tri2
                      19, 26, 17  // tri3
                      ),
    gsSPNTriangles_5b(21, 20, 24, // tri0
                      24, 16, 15, // tri1
                      17, 26, 15, // tri2
                      15, 25, 24  // tri3
                      ),
    gsSPNTriangles_5b(17, 23, 14, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x100, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&bpt_1_v[73], 24, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 5  // tri2
                          ),
    gsSPNTriangles_5b(5, 4, 6,   // tri0
                      8, 7, 6,   // tri1
                      9, 10, 11, // tri2
                      6, 4, 12   // tri3
                      ),
    gsSPNTriangles_5b(5, 13, 3,  // tri0
                      9, 14, 10, // tri1
                      2, 15, 0,  // tri2
                      11, 1, 9   // tri3
                      ),
    gsSPNTriangles_5b(12, 8, 6, // tri0
                      9, 1, 0,  // tri1
                      0, 14, 9, // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x140, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(6,          // tri count
                          16, 17, 18, // tri0
                          17, 16, 19, // tri1
                          19, 20, 21  // tri2
                          ),
    gsSPNTriangles_5b(22, 19, 16, // tri0
                      20, 19, 22, // tri1
                      23, 21, 20, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x1C0, G_IM_FMT_CI, 16, 8, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&bpt_1_v[97], 17, 0),
    gsSPNTrianglesInit_5b(11,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 2, // tri1
                          0, 2, 5  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 5,  // tri0
                      8, 0, 9,  // tri1
                      5, 10, 6, // tri2
                      9, 0, 11  // tri3
                      ),
    gsSPNTriangles_5b(2, 12, 3, // tri0
                      5, 2, 4,  // tri1
                      5, 4, 10, // tri2
                      9, 13, 8  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1,          // tri count
                          14, 15, 16, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx feel_bpt_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x200, G_IM_FMT_CI, 32, 16, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bpt_1_v[114], 14, 0),
    gsSPNTrianglesInit_5b(15,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 1  // tri2
                          ),
    gsSPNTriangles_5b(8, 5, 4,  // tri0
                      9, 1, 7,  // tri1
                      4, 10, 9, // tri2
                      7, 11, 9  // tri3
                      ),
    gsSPNTriangles_5b(5, 12, 3, // tri0
                      4, 3, 10, // tri1
                      9, 10, 1, // tri2
                      2, 13, 0  // tri3
                      ),
    gsSPNTriangles_5b(1, 0, 6,  // tri0
                      9, 11, 4, // tri1
                      10, 2, 1, // tri2
                      4, 11, 8  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx mouth_bpt_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*13, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bpt_1_v[0], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*12, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&bpt_1_v[5], 16, 5),
    gsSPNTrianglesInit_5b(8,       // tri count
                          1, 5, 6, // tri0
                          1, 7, 0, // tri1
                          0, 8, 9  // tri2
                          ),
    gsSPNTriangles_5b(3, 4, 10,  // tri0
                      4, 12, 11, // tri1
                      2, 13, 14, // tri2
                      3, 15, 2   // tri3
                      ),
    gsSPNTriangles_5b(4, 0, 16, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPNTrianglesInit_5b(2,          // tri count
                          17, 18, 19, // tri0
                          17, 19, 20, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rarm2_bpt_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bpt_1_v[169], 6, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*11, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&bpt_1_v[175], 22, 6),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 6, 4, // tri0
                          0, 2, 7, // tri1
                          2, 8, 9  // tri2
                          ),
    gsSPNTriangles_5b(4, 10, 11, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4,         // tri count
                          5, 3, 12,  // tri0
                          3, 13, 14, // tri1
                          1, 5, 15   // tri2
                          ),
    gsSPNTriangles_5b(1, 16, 17, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3,          // tri count
                          18, 19, 20, // tri0
                          20, 21, 18, // tri1
                          18, 22, 19  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3,          // tri count
                          23, 24, 25, // tri0
                          25, 26, 23, // tri1
                          24, 27, 25  // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rarm1_bpt_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bpt_1_v[197], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&bpt_1_v[200], 11, 3),
    gsSPNTrianglesInit_5b(3,       // tri count
                          0, 1, 3, // tri0
                          1, 4, 5, // tri1
                          0, 7, 6  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4,        // tri count
                          2, 0, 8,  // tri0
                          2, 9, 1,  // tri1
                          0, 10, 11 // tri2
                          ),
    gsSPNTriangles_5b(2, 12, 13, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Larm2_bpt_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bpt_1_v[128], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*9, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&bpt_1_v[133], 22, 5),
    gsSPNTrianglesInit_5b(4,       // tri count
                          3, 5, 6, // tri0
                          2, 7, 8, // tri1
                          3, 0, 9  // tri2
                          ),
    gsSPNTriangles_5b(2, 10, 0, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4,         // tri count
                          3, 11, 12, // tri0
                          1, 13, 14, // tri1
                          1, 4, 15   // tri2
                          ),
    gsSPNTriangles_5b(4, 3, 16, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3,          // tri count
                          17, 18, 19, // tri0
                          18, 20, 19, // tri1
                          19, 21, 17  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3,          // tri count
                          22, 23, 24, // tri0
                          22, 24, 25, // tri1
                          25, 26, 22  // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Larm1_bpt_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bpt_1_v[155], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&bpt_1_v[158], 11, 3),
    gsSPNTrianglesInit_5b(3,       // tri count
                          0, 4, 3, // tri0
                          1, 5, 6, // tri1
                          1, 0, 7  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4,        // tri count
                          1, 8, 2,  // tri0
                          2, 9, 10, // tri1
                          0, 2, 11  // tri2
                          ),
    gsSPNTriangles_5b(0, 12, 13, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx chest_bpt_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bpt_1_v[211], 7, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 32, 24, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&bpt_1_v[218], 23, 7),
    gsSPNTrianglesInit_5b(15,      // tri count
                          4, 5, 7, // tri0
                          3, 8, 9, // tri1
                          6, 10, 1 // tri2
                          ),
    gsSPNTriangles_5b(1, 11, 12, // tri0
                      1, 14, 13, // tri1
                      0, 15, 16, // tri2
                      6, 0, 17   // tri3
                      ),
    gsSPNTriangles_5b(5, 18, 19, // tri0
                      6, 20, 21, // tri1
                      2, 22, 23, // tri2
                      2, 24, 3   // tri3
                      ),
    gsSPNTriangles_5b(1, 25, 2,  // tri0
                      3, 26, 5,  // tri1
                      4, 27, 28, // tri2
                      4, 29, 0   // tri3
                      ),
    gsSPVertex(&bpt_1_v[241], 16, 0),
    gsSPNTrianglesInit_5b(18,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 0  // tri2
                          ),
    gsSPNTriangles_5b(8, 9, 10, // tri0
                      8, 10, 3, // tri1
                      5, 8, 3,  // tri2
                      2, 11, 6  // tri3
                      ),
    gsSPNTriangles_5b(0, 7, 12,  // tri0
                      1, 0, 4,   // tri1
                      12, 13, 4, // tri2
                      5, 13, 14  // tri3
                      ),
    gsSPNTriangles_5b(0, 2, 6,  // tri0
                      12, 4, 0, // tri1
                      8, 15, 9, // tri2
                      10, 9, 11 // tri3
                      ),
    gsSPNTriangles_5b(8, 14, 15, // tri0
                      5, 14, 8,  // tri1
                      2, 3, 10,  // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx tail1_bpt_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x580, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bpt_1_v[276], 6, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          2, 1, 3  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 3, // tri0
                      3, 5, 2, // tri1
                      2, 4, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx tail2_bpt_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bpt_1_v[257], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*6, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x580, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&bpt_1_v[260], 16, 3),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 3, 4, // tri0
                          0, 5, 6, // tri1
                          2, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(2, 1, 9,  // tri0
                      1, 0, 10, // tri1
                      0, 2, 11, // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPNTrianglesInit_5b(9,          // tri count
                          12, 13, 14, // tri0
                          15, 13, 16, // tri1
                          14, 16, 17  // tri2
                          ),
    gsSPNTriangles_5b(16, 13, 12, // tri0
                      12, 17, 16, // tri1
                      16, 14, 15, // tri2
                      15, 14, 13  // tri3
                      ),
    gsSPNTriangles_5b(14, 18, 12, // tri0
                      17, 18, 14, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot2_bpt_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x580, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bpt_1_v[312], 8, 0),
    gsSPNTrianglesInit_5b(10,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 0, // tri1
                          5, 1, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 3, 7, // tri0
                      5, 7, 2, // tri1
                      2, 7, 3, // tri2
                      2, 1, 5  // tri3
                      ),
    gsSPNTriangles_5b(5, 4, 3, // tri0
                      5, 6, 4, // tri1
                      2, 3, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot1_bpt_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bpt_1_v[320], 8, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x600, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&bpt_1_v[328], 13, 8),
    gsSPNTrianglesInit_5b(9,       // tri count
                          0, 2, 8, // tri0
                          3, 1, 9, // tri1
                          3, 10, 6 // tri2
                          ),
    gsSPNTriangles_5b(4, 11, 2,  // tri0
                      2, 12, 13, // tri1
                      1, 14, 15, // tri2
                      5, 7, 16   // tri3
                      ),
    gsSPNTriangles_5b(7, 17, 18, // tri0
                      5, 19, 20, // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot2_bpt_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x580, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bpt_1_v[282], 8, 0),
    gsSPNTrianglesInit_5b(10,      // tri count
                          0, 1, 2, // tri0
                          3, 1, 4, // tri1
                          5, 6, 4  // tri2
                          ),
    gsSPNTriangles_5b(2, 3, 4, // tri0
                      2, 6, 0, // tri1
                      0, 7, 1, // tri2
                      1, 3, 2  // tri3
                      ),
    gsSPNTriangles_5b(4, 6, 2, // tri0
                      1, 7, 4, // tri1
                      7, 5, 4, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot1_bpt_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bpt_1_v[290], 6, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x600, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&bpt_1_v[296], 16, 6),
    gsSPNTrianglesInit_5b(8,       // tri count
                          1, 6, 7, // tri0
                          4, 8, 0, // tri1
                          1, 9, 2  // tri2
                          ),
    gsSPNTriangles_5b(3, 11, 10, // tri0
                      5, 3, 12,  // tri1
                      5, 13, 14, // tri2
                      1, 15, 16  // tri3
                      ),
    gsSPNTriangles_5b(0, 18, 17, // tri0
                      0, 0, 0,   // tri1
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

static Gfx base_bpt_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 32, 24, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bpt_1_v[341], 25, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          2, 3, 0, // tri1
                          0, 3, 4  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7, // tri0
                      2, 1, 6, // tri1
                      2, 6, 5, // tri2
                      4, 8, 0  // tri3
                      ),
    gsSPNTriangles_5b(9, 8, 4, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x600, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(9,          // tri count
                          10, 11, 12, // tri0
                          10, 13, 11, // tri1
                          14, 15, 13  // tri2
                          ),
    gsSPNTriangles_5b(14, 13, 10, // tri0
                      12, 11, 16, // tri1
                      17, 18, 19, // tri2
                      17, 19, 20  // tri3
                      ),
    gsSPNTriangles_5b(21, 22, 23, // tri0
                      23, 24, 21, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

// clang-format off
static cKF_Joint_R_c cKF_je_r_bpt_1_tbl[] = {
    /* joint 0 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,1000,0 },
    /* joint 1 */ { base_bpt_model, 4, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 2 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,-250,0 },
    /* joint 3 */ { Lfoot1_bpt_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 4 */ { Lfoot2_bpt_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 5 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 6 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,250,0 },
    /* joint 7 */ { Rfoot1_bpt_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 8 */ { Rfoot2_bpt_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 9 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 10 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,-500 },
    /* joint 11 */ { tail1_bpt_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 12 */ { tail2_bpt_model, 0, cKF_JOINT_FLAG_DISP_OPA, 999,0,0 },
    /* joint 13 */ { chest_bpt_model, 3, cKF_JOINT_FLAG_DISP_OPA, 425,0,0 },
    /* joint 14 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 750,-500,0 },
    /* joint 15 */ { Larm1_bpt_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 16 */ { Larm2_bpt_model, 0, cKF_JOINT_FLAG_DISP_OPA, 750,0,0 },
    /* joint 17 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 750,500,0 },
    /* joint 18 */ { Rarm1_bpt_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 19 */ { Rarm2_bpt_model, 1, cKF_JOINT_FLAG_DISP_OPA, 750,0,0 },
    /* joint 20 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 750,0,0 },
    /* joint 21 */ { NULL, 2, cKF_JOINT_FLAG_DISP_OPA, 1074,0,0 },
    /* joint 22 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 250,0,900 },
    /* joint 23 */ { mouth_bpt_model, 0, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 24 */ { head_bpt_model, 1, cKF_JOINT_FLAG_DISP_OPA, -199,0,0 },
    /* joint 25 */ { feel_bpt_model, 0, cKF_JOINT_FLAG_DISP_OPA, 1400,0,0 },
};
// clang-format on

extern cKF_Skeleton_R_c cKF_bs_r_bpt_1 = { 26, 15, cKF_je_r_bpt_1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_npc_model_mdl_bpt_1_c(void) {
    pc_load_asset("assets/npc/mdl/bpt_1_v.bin", bpt_1_v, 0x16E0, 0x524768, 0, 2);
}
#endif

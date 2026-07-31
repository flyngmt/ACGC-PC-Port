#include "c_keyframe.h"
#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
static Vtx squ_1_v[0x16F0 / sizeof(Vtx)];
#else
static Vtx squ_1_v[] = {
#include "assets/npc/mdl/squ_1_v.inc"
};
#endif

static Gfx head_squ_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&squ_1_v[0], 12, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          3, 2, 4, // tri1
                          3, 4, 5  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 8,  // tri0
                      8, 9, 6,  // tri1
                      10, 6, 9, // tri2
                      10, 9, 11 // tri3
                      ),
    gsSPNTriangles_5b(2, 3, 0, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x040, G_IM_FMT_CI, 32, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&squ_1_v[12], 25, 0),
    gsSPNTrianglesInit_5b(32,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          2, 1, 4  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7, // tri0
                      4, 1, 8, // tri1
                      4, 8, 9, // tri2
                      10, 4, 9 // tri3
                      ),
    gsSPNTriangles_5b(11, 0, 12, // tri0
                      12, 3, 13, // tri1
                      12, 0, 3,  // tri2
                      11, 8, 1   // tri3
                      ),
    gsSPNTriangles_5b(1, 0, 11, // tri0
                      14, 2, 4, // tri1
                      15, 3, 2, // tri2
                      16, 15, 2 // tri3
                      ),
    gsSPNTriangles_5b(10, 17, 18, // tri0
                      7, 13, 3,   // tri1
                      14, 4, 10,  // tri2
                      3, 15, 7    // tri3
                      ),
    gsSPNTriangles_5b(19, 5, 15,  // tri0
                      20, 21, 19, // tri1
                      18, 14, 10, // tri2
                      7, 15, 5    // tri3
                      ),
    gsSPNTriangles_5b(14, 18, 22, // tri0
                      23, 16, 14, // tri1
                      2, 14, 16,  // tri2
                      15, 16, 23  // tri3
                      ),
    gsSPNTriangles_5b(22, 24, 20, // tri0
                      14, 22, 23, // tri1
                      23, 19, 15, // tri2
                      19, 23, 20  // tri3
                      ),
    gsSPNTriangles_5b(20, 23, 22, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_1_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&squ_1_v[37], 20, 0),
    gsSPNTrianglesInit_5b(24,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          2, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 9, 3,   // tri0
                      10, 8, 3,  // tri1
                      11, 0, 2,  // tri2
                      12, 13, 11 // tri3
                      ),
    gsSPNTriangles_5b(10, 13, 12, // tri0
                      7, 14, 15,  // tri1
                      6, 14, 7,   // tri2
                      10, 5, 16   // tri3
                      ),
    gsSPNTriangles_5b(2, 7, 11,  // tri0
                      17, 0, 11, // tri1
                      9, 8, 18,  // tri2
                      3, 5, 10   // tri3
                      ),
    gsSPNTriangles_5b(12, 8, 10,  // tri0
                      16, 19, 13, // tri1
                      13, 10, 16, // tri2
                      11, 7, 12   // tri3
                      ),
    gsSPNTriangles_5b(13, 17, 11, // tri0
                      8, 12, 15,  // tri1
                      15, 12, 7,  // tri2
                      15, 18, 8   // tri3
                      ),
    gsSPNTriangles_5b(13, 19, 17, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_2_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&squ_1_v[57], 14, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          3, 6, 4  // tri2
                          ),
    gsSPNTriangles_5b(1, 7, 2, // tri0
                      2, 7, 8, // tri1
                      7, 1, 5, // tri2
                      7, 5, 9  // tri3
                      ),
    gsSPNTriangles_5b(7, 10, 8, // tri0
                      7, 9, 10, // tri1
                      8, 11, 2, // tri2
                      9, 5, 4   // tri3
                      ),
    gsSPNTriangles_5b(11, 12, 2,  // tri0
                      11, 13, 12, // tri1
                      0, 3, 5,    // tri2
                      5, 1, 0     // tri3
                      ),
    gsSPNTriangles_5b(2, 12, 0, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x240, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&squ_1_v[71], 20, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 0, 3  // tri2
                          ),
    gsSPNTriangles_5b(4, 3, 5,  // tri0
                      6, 7, 8,  // tri1
                      0, 4, 9,  // tri2
                      10, 8, 11 // tri3
                      ),
    gsSPNTriangles_5b(4, 5, 12,   // tri0
                      4, 12, 13,  // tri1
                      14, 15, 16, // tri2
                      14, 16, 17  // tri3
                      ),
    gsSPNTriangles_5b(10, 14, 17, // tri0
                      10, 17, 6,  // tri1
                      9, 1, 0,    // tri2
                      6, 8, 10    // tri3
                      ),
    gsSPNTriangles_5b(18, 9, 4,   // tri0
                      14, 11, 19, // tri1
                      11, 14, 10, // tri2
                      19, 15, 14  // tri3
                      ),
    gsSPNTriangles_5b(4, 13, 18, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rarm2_squ_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&squ_1_v[127], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*11, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&squ_1_v[132], 16, 5),
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

static Gfx Rarm1_squ_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&squ_1_v[148], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&squ_1_v[152], 11, 4),
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

static Gfx Larm2_squ_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&squ_1_v[91], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*9, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&squ_1_v[96], 16, 5),
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

static Gfx Larm1_squ_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&squ_1_v[112], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&squ_1_v[116], 11, 4),
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

static Gfx chest_squ_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&squ_1_v[163], 7, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_3_txt, G_IM_FMT_CI, 32, 32, 14, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 508, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&squ_1_v[170], 20, 7),
    gsSPNTrianglesInit_5b(13,       // tri count
                          3, 1, 7,  // tri0
                          6, 8, 9,  // tri1
                          3, 10, 11 // tri2
                          ),
    gsSPNTriangles_5b(2, 12, 0,  // tri0
                      2, 13, 14, // tri1
                      1, 16, 15, // tri2
                      0, 17, 18  // tri3
                      ),
    gsSPNTriangles_5b(0, 19, 20, // tri0
                      1, 21, 22, // tri1
                      6, 3, 23,  // tri2
                      2, 6, 24   // tri3
                      ),
    gsSPNTriangles_5b(4, 0, 25, // tri0
                      5, 26, 1, // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPVertex(&squ_1_v[190], 9, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 4, // tri1
                          0, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 3, 7, // tri0
                      2, 5, 0, // tri1
                      1, 8, 2, // tri2
                      6, 3, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx tail1_squ_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 16, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&squ_1_v[242], 13, 0),
    gsSPNTrianglesInit_5b(17,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 3, 5  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 8,   // tri0
                      8, 9, 6,   // tri1
                      10, 9, 11, // tri2
                      6, 3, 4    // tri3
                      ),
    gsSPNTriangles_5b(4, 7, 6,  // tri0
                      9, 2, 6,  // tri1
                      5, 3, 10, // tri2
                      2, 9, 0   // tri3
                      ),
    gsSPNTriangles_5b(0, 10, 3,  // tri0
                      9, 10, 0,  // tri1
                      11, 9, 8,  // tri2
                      11, 12, 10 // tri3
                      ),
    gsSPNTriangles_5b(10, 12, 5, // tri0
                      6, 1, 3,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx tail2_squ_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&squ_1_v[199], 6, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*6, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 16, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&squ_1_v[205], 16, 6),
    gsSPNTrianglesInit_5b(11,      // tri count
                          3, 6, 7, // tri0
                          5, 1, 8, // tri1
                          5, 9, 10 // tri2
                          ),
    gsSPNTriangles_5b(2, 0, 11,  // tri0
                      0, 3, 12,  // tri1
                      0, 13, 14, // tri2
                      2, 15, 16  // tri3
                      ),
    gsSPNTriangles_5b(2, 17, 1, // tri0
                      4, 18, 3, // tri1
                      4, 5, 19, // tri2
                      5, 20, 21 // tri3
                      ),
    gsSPVertex(&squ_1_v[221], 21, 0),
    gsSPNTrianglesInit_5b(35,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 4, // tri1
                          0, 4, 5  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 8,   // tri0
                      9, 10, 11, // tri1
                      9, 11, 5,  // tri2
                      6, 12, 7   // tri3
                      ),
    gsSPNTriangles_5b(13, 10, 14, // tri0
                      9, 7, 12,   // tri1
                      5, 4, 7,    // tri2
                      5, 7, 9     // tri3
                      ),
    gsSPNTriangles_5b(8, 7, 4,    // tri0
                      13, 15, 16, // tri1
                      17, 18, 19, // tri2
                      17, 19, 15  // tri3
                      ),
    gsSPNTriangles_5b(13, 17, 15, // tri0
                      19, 18, 8,  // tri1
                      11, 10, 13, // tri2
                      20, 2, 16   // tri3
                      ),
    gsSPNTriangles_5b(11, 13, 1,  // tri0
                      10, 12, 14, // tri1
                      12, 10, 9,  // tri2
                      14, 17, 13  // tri3
                      ),
    gsSPNTriangles_5b(8, 18, 6,   // tri0
                      19, 20, 16, // tri1
                      19, 16, 15, // tri2
                      20, 19, 8   // tri3
                      ),
    gsSPNTriangles_5b(2, 3, 0,  // tri0
                      3, 8, 4,  // tri1
                      5, 11, 1, // tri2
                      5, 1, 0   // tri3
                      ),
    gsSPNTriangles_5b(1, 13, 16, // tri0
                      20, 8, 3,  // tri1
                      1, 16, 2,  // tri2
                      2, 20, 3   // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot2_squ_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&squ_1_v[305], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*4, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&squ_1_v[310], 17, 5),
    gsSPNTrianglesInit_5b(7,       // tri count
                          4, 0, 5, // tri0
                          0, 7, 6, // tri1
                          3, 9, 8  // tri2
                          ),
    gsSPNTriangles_5b(1, 2, 10, // tri0
                      2, 3, 11, // tri1
                      3, 4, 12, // tri2
                      2, 13, 14 // tri3
                      ),
    gsSPNTrianglesInit_5b(3,          // tri count
                          15, 16, 17, // tri0
                          18, 19, 20, // tri1
                          18, 21, 19  // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot1_squ_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&squ_1_v[327], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_3_txt, G_IM_FMT_CI, 32, 32, 14, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 508, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&squ_1_v[331], 22, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 3, 4, // tri0
                          0, 5, 1, // tri1
                          1, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(3, 2, 8,  // tri0
                      2, 9, 10, // tri1
                      2, 1, 11, // tri2
                      0, 13, 12 // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(7,          // tri count
                          14, 15, 16, // tri0
                          14, 16, 17, // tri1
                          17, 18, 14  // tri2
                          ),
    gsSPNTriangles_5b(19, 20, 21, // tri0
                      21, 20, 18, // tri1
                      21, 22, 19, // tri2
                      17, 21, 18  // tri3
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

static Gfx Lfoot2_squ_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&squ_1_v[255], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&squ_1_v[260], 17, 5),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 4, 5, // tri0
                          0, 7, 6, // tri1
                          3, 9, 8  // tri2
                          ),
    gsSPNTriangles_5b(2, 1, 10, // tri0
                      3, 2, 11, // tri1
                      4, 3, 12, // tri2
                      2, 13, 14 // tri3
                      ),
    gsSPNTrianglesInit_5b(3,          // tri count
                          15, 16, 17, // tri0
                          18, 19, 20, // tri1
                          19, 21, 20  // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot1_squ_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&squ_1_v[277], 6, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_3_txt, G_IM_FMT_CI, 32, 32, 14, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 508, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&squ_1_v[283], 22, 6),
    gsSPNTrianglesInit_5b(7,       // tri count
                          4, 0, 6, // tri0
                          1, 7, 0, // tri1
                          1, 8, 9  // tri2
                          ),
    gsSPNTriangles_5b(2, 5, 10,  // tri0
                      2, 11, 12, // tri1
                      1, 3, 13,  // tri2
                      0, 15, 14  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(7,          // tri count
                          16, 17, 18, // tri0
                          19, 16, 18, // tri1
                          18, 20, 19  // tri2
                          ),
    gsSPNTriangles_5b(21, 22, 23, // tri0
                      20, 22, 21, // tri1
                      23, 24, 21, // tri2
                      20, 21, 19  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_3_txt, G_IM_FMT_CI, 32, 32, 14, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 508, 124),
    gsSPNTrianglesInit_5b(1,          // tri count
                          25, 26, 27, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx base_squ_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_3_txt, G_IM_FMT_CI, 32, 32, 14, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 508, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&squ_1_v[353], 14, 0),
    gsSPNTrianglesInit_5b(12,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(9, 5, 4,  // tri0
                      10, 4, 0, // tri1
                      10, 9, 4, // tri2
                      7, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(8, 7, 13, // tri0
                      2, 10, 0, // tri1
                      2, 1, 6,  // tri2
                      6, 8, 2   // tri3
                      ),
    gsSPNTriangles_5b(7, 12, 13, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

// clang-format off
static cKF_Joint_R_c cKF_je_r_squ_1_tbl[] = {
    /* joint 0 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,1000,0 },
    /* joint 1 */ { base_squ_model, 4, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 2 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,-350,0 },
    /* joint 3 */ { Lfoot1_squ_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 4 */ { Lfoot2_squ_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 5 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 6 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,350,0 },
    /* joint 7 */ { Rfoot1_squ_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 8 */ { Rfoot2_squ_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 9 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 10 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 100,0,-700 },
    /* joint 11 */ { tail1_squ_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 12 */ { tail2_squ_model, 0, cKF_JOINT_FLAG_DISP_OPA, 1099,0,0 },
    /* joint 13 */ { chest_squ_model, 3, cKF_JOINT_FLAG_DISP_OPA, 350,0,0 },
    /* joint 14 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 425,-650,0 },
    /* joint 15 */ { Larm1_squ_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 16 */ { Larm2_squ_model, 0, cKF_JOINT_FLAG_DISP_OPA, 350,0,0 },
    /* joint 17 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 425,650,0 },
    /* joint 18 */ { Rarm1_squ_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 19 */ { Rarm2_squ_model, 1, cKF_JOINT_FLAG_DISP_OPA, 350,0,0 },
    /* joint 20 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 350,0,0 },
    /* joint 21 */ { NULL, 2, cKF_JOINT_FLAG_DISP_OPA, 650,0,0 },
    /* joint 22 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,600 },
    /* joint 23 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 24 */ { head_squ_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 25 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 1600,0,0 },
};
// clang-format on

extern cKF_Skeleton_R_c cKF_bs_r_squ_1 = { 26, 13, cKF_je_r_squ_1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_npc_model_mdl_squ_1_c(void) {
    pc_load_asset("assets/npc/mdl/squ_1_v.bin", squ_1_v, 0x16F0, 0x7CBB80, 0, 2);
}
#endif

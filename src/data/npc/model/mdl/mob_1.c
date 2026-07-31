#include "c_keyframe.h"
#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
static Vtx mob_1_v[0x13B0 / sizeof(Vtx)];
#else
static Vtx mob_1_v[] = {
#include "assets/npc/mdl/mob_1_v.inc"
};
#endif

static Gfx head_mob_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&mob_1_v[32], 10, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x200, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&mob_1_v[42], 15, 10),
    gsSPNTrianglesInit_5b(10,        // tri count
                          0, 10, 11, // tri0
                          1, 12, 13, // tri1
                          7, 0, 14   // tri2
                          ),
    gsSPNTriangles_5b(0, 1, 15,  // tri0
                      3, 16, 17, // tri1
                      5, 18, 19, // tri2
                      4, 3, 20   // tri3
                      ),
    gsSPNTriangles_5b(0, 21, 22, // tri0
                      1, 4, 23,  // tri1
                      5, 7, 24,  // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_2_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&mob_1_v[57], 20, 10),
    gsSPNTrianglesInit_5b(8,         // tri count
                          8, 11, 10, // tri0
                          8, 13, 12, // tri1
                          9, 15, 14  // tri2
                          ),
    gsSPNTriangles_5b(8, 6, 16, // tri0
                      2, 9, 17, // tri1
                      9, 8, 18, // tri2
                      9, 19, 20 // tri3
                      ),
    gsSPNTriangles_5b(8, 21, 22, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x0C0, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(6,          // tri count
                          23, 24, 25, // tri0
                          26, 23, 25, // tri1
                          27, 26, 25  // tri2
                          ),
    gsSPNTriangles_5b(28, 27, 25, // tri0
                      29, 28, 25, // tri1
                      24, 29, 25, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x100, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&mob_1_v[77], 31, 0),
    gsSPNTrianglesInit_5b(12,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          3, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(0, 7, 1,   // tri0
                      8, 9, 10,  // tri1
                      8, 10, 11, // tri2
                      12, 13, 14 // tri3
                      ),
    gsSPNTriangles_5b(15, 16, 17, // tri0
                      15, 17, 18, // tri1
                      12, 14, 19, // tri2
                      20, 21, 22  // tri3
                      ),
    gsSPNTriangles_5b(20, 22, 23, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x140, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(6,          // tri count
                          24, 25, 26, // tri0
                          27, 28, 26, // tri1
                          25, 27, 26  // tri2
                          ),
    gsSPNTriangles_5b(29, 24, 26, // tri0
                      30, 29, 26, // tri1
                      28, 30, 26, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x1C0, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&mob_1_v[108], 31, 0),
    gsSPNTrianglesInit_5b(10,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          3, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,  // tri0
                      10, 2, 6, // tri1
                      9, 11, 7, // tri2
                      8, 4, 3   // tri3
                      ),
    gsSPNTriangles_5b(2, 10, 0, // tri0
                      6, 5, 10, // tri1
                      3, 9, 8,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_1_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(6,          // tri count
                          12, 13, 14, // tri0
                          15, 16, 17, // tri1
                          16, 15, 12  // tri2
                          ),
    gsSPNTriangles_5b(18, 14, 13, // tri0
                      12, 19, 16, // tri1
                      14, 19, 12, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x0C0, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(13,         // tri count
                          20, 21, 22, // tri0
                          23, 22, 24, // tri1
                          23, 25, 26  // tri2
                          ),
    gsSPNTriangles_5b(23, 26, 20, // tri0
                      20, 22, 23, // tri1
                      27, 28, 26, // tri2
                      20, 26, 28  // tri3
                      ),
    gsSPNTriangles_5b(26, 25, 29, // tri0
                      25, 24, 30, // tri1
                      28, 21, 20, // tri2
                      25, 30, 29  // tri3
                      ),
    gsSPNTriangles_5b(24, 25, 23, // tri0
                      29, 27, 26, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx mouth_mob_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&mob_1_v[0], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x080, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&mob_1_v[5], 21, 5),
    gsSPNTrianglesInit_5b(10,      // tri count
                          2, 5, 6, // tri0
                          2, 7, 8, // tri1
                          4, 3, 9  // tri2
                          ),
    gsSPNTriangles_5b(3, 10, 11, // tri0
                      4, 12, 13, // tri1
                      1, 4, 14,  // tri2
                      3, 0, 15   // tri3
                      ),
    gsSPNTriangles_5b(2, 16, 17, // tri0
                      2, 1, 18,  // tri1
                      0, 2, 19,  // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4,          // tri count
                          20, 21, 22, // tri0
                          20, 22, 23, // tri1
                          23, 24, 25  // tri2
                          ),
    gsSPNTriangles_5b(23, 25, 20, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x080, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&mob_1_v[26], 6, 0),
    gsSPNTrianglesInit_5b(3,       // tri count
                          0, 1, 2, // tri0
                          2, 3, 0, // tri1
                          4, 5, 2  // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx hand_mob_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&mob_1_v[175], 25, 0),
    gsSPNTrianglesInit_5b(30,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          3, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 5,  // tri0
                      7, 5, 9,  // tri1
                      0, 10, 1, // tri2
                      11, 8, 4  // tri3
                      ),
    gsSPNTriangles_5b(11, 4, 3,   // tri0
                      12, 13, 14, // tri1
                      9, 13, 12,  // tri2
                      9, 12, 7    // tri3
                      ),
    gsSPNTriangles_5b(0, 2, 10, // tri0
                      6, 5, 8,  // tri1
                      6, 8, 11, // tri2
                      11, 10, 2 // tri3
                      ),
    gsSPNTriangles_5b(11, 2, 6,  // tri0
                      3, 1, 10,  // tri1
                      3, 10, 11, // tri2
                      6, 2, 1    // tri3
                      ),
    gsSPNTriangles_5b(6, 1, 3,    // tri0
                      13, 15, 14, // tri1
                      9, 5, 4,    // tri2
                      9, 4, 16    // tri3
                      ),
    gsSPNTriangles_5b(16, 15, 13, // tri0
                      16, 13, 9,  // tri1
                      15, 12, 14, // tri2
                      16, 4, 8    // tri3
                      ),
    gsSPNTriangles_5b(16, 8, 7,  // tri0
                      7, 12, 15, // tri1
                      7, 15, 16, // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(12,         // tri count
                          17, 18, 19, // tri0
                          19, 18, 20, // tri1
                          19, 20, 21  // tri2
                          ),
    gsSPNTriangles_5b(20, 22, 21, // tri0
                      18, 17, 22, // tri1
                      18, 22, 20, // tri2
                      19, 23, 17  // tri3
                      ),
    gsSPNTriangles_5b(17, 23, 24, // tri0
                      17, 24, 22, // tri1
                      24, 21, 22, // tri2
                      23, 19, 21  // tri3
                      ),
    gsSPNTriangles_5b(23, 21, 24, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rarm2_mob_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*4, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&mob_1_v[200], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x240, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&mob_1_v[205], 16, 5),
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

static Gfx Rarm1_mob_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&mob_1_v[221], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*4, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x240, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&mob_1_v[225], 11, 4),
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

static Gfx Larm2_mob_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&mob_1_v[139], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x240, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&mob_1_v[144], 16, 5),
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

static Gfx Larm1_mob_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&mob_1_v[160], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x240, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&mob_1_v[164], 11, 4),
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

static Gfx chest_mob_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&mob_1_v[236], 9, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 64, 24, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&mob_1_v[245], 22, 9),
    gsSPNTrianglesInit_5b(14,       // tri count
                          0, 9, 3,  // tri0
                          1, 10, 8, // tri1
                          4, 11, 5  // tri2
                          ),
    gsSPNTriangles_5b(6, 12, 2,  // tri0
                      8, 13, 14, // tri1
                      8, 15, 7,  // tri2
                      2, 16, 17  // tri3
                      ),
    gsSPNTriangles_5b(1, 18, 19, // tri0
                      3, 20, 21, // tri1
                      4, 22, 23, // tri2
                      0, 24, 25  // tri3
                      ),
    gsSPNTriangles_5b(0, 5, 26,  // tri0
                      2, 27, 28, // tri1
                      1, 29, 30, // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&mob_1_v[267], 6, 9),
    gsSPNTrianglesInit_5b(4,        // tri count
                          3, 9, 10, // tri0
                          3, 11, 1, // tri1
                          4, 12, 13 // tri2
                          ),
    gsSPNTriangles_5b(4, 2, 14, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPVertex(&mob_1_v[273], 18, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          3, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 8,    // tri0
                      9, 10, 11,  // tri1
                      12, 13, 14, // tri2
                      7, 10, 15   // tri3
                      ),
    gsSPNTriangles_5b(4, 8, 5,   // tri0
                      16, 1, 17, // tri1
                      15, 8, 7,  // tri2
                      9, 15, 10  // tri3
                      ),
    gsSPNTriangles_5b(11, 12, 14, // tri0
                      11, 14, 9,  // tri1
                      13, 17, 14, // tri2
                      1, 16, 2    // tri3
                      ),
    gsSPNTriangles_5b(17, 13, 16, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx base_mob_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 64, 24, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&mob_1_v[291], 24, 0),
    gsSPNTrianglesInit_5b(26,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          0, 6, 1  // tri2
                          ),
    gsSPNTriangles_5b(0, 7, 6,  // tri0
                      5, 4, 8,  // tri1
                      9, 4, 10, // tri2
                      9, 10, 11 // tri3
                      ),
    gsSPNTriangles_5b(6, 12, 1,  // tri0
                      13, 3, 5,  // tri1
                      13, 2, 14, // tri2
                      13, 14, 15 // tri3
                      ),
    gsSPNTriangles_5b(16, 1, 12, // tri0
                      17, 18, 6, // tri1
                      17, 6, 19, // tri2
                      2, 1, 16   // tri3
                      ),
    gsSPNTriangles_5b(2, 16, 14, // tri0
                      6, 18, 12, // tri1
                      3, 20, 4,  // tri2
                      21, 17, 19 // tri3
                      ),
    gsSPNTriangles_5b(21, 19, 22, // tri0
                      15, 23, 3,  // tri1
                      15, 3, 13,  // tri2
                      20, 3, 23   // tri3
                      ),
    gsSPNTriangles_5b(19, 6, 7,  // tri0
                      20, 10, 4, // tri1
                      8, 4, 9,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

// clang-format off
static cKF_Joint_R_c cKF_je_r_mob_1_tbl[] = {
    /* joint 0 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 1 */ { base_mob_model, 4, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 2 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,-700,0 },
    /* joint 3 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 4 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 5 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 6 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,700,0 },
    /* joint 7 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 8 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 9 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 10 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 300,0,-950 },
    /* joint 11 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 12 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 650,0,0 },
    /* joint 13 */ { chest_mob_model, 3, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 14 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 500,-1050,0 },
    /* joint 15 */ { Larm1_mob_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 16 */ { Larm2_mob_model, 0, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 17 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 500,1050,0 },
    /* joint 18 */ { Rarm1_mob_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 19 */ { Rarm2_mob_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 20 */ { hand_mob_model, 0, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 21 */ { NULL, 2, cKF_JOINT_FLAG_DISP_OPA, 1399,0,0 },
    /* joint 22 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 800,0,900 },
    /* joint 23 */ { mouth_mob_model, 0, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 24 */ { head_mob_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 25 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 800,0,0 },
};
// clang-format on

extern cKF_Skeleton_R_c cKF_bs_r_mob_1 = { 26, 9, cKF_je_r_mob_1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_npc_model_mdl_mob_1_c(void) {
    pc_load_asset("assets/npc/mdl/mob_1_v.bin", mob_1_v, 0x13B0, 0x646D60, 0, 2);
}
#endif

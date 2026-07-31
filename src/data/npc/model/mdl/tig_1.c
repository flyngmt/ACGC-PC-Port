#include "c_keyframe.h"
#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
static Vtx tig_1_v[0x1AC0 / sizeof(Vtx)];
#else
static Vtx tig_1_v[] = {
#include "assets/npc/mdl/tig_1_v.inc"
};
#endif

static Gfx head_tig_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_1_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tig_1_v[21], 17, 0),
    gsSPNTrianglesInit_5b(19,      // tri count
                          0, 1, 2, // tri0
                          1, 0, 3, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(0, 7, 8,   // tri0
                      6, 9, 4,   // tri1
                      3, 0, 8,   // tri2
                      10, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(12, 11, 7, // tri0
                      8, 13, 3,  // tri1
                      6, 14, 9,  // tri2
                      15, 4, 9   // tri3
                      ),
    gsSPNTriangles_5b(12, 14, 10, // tri0
                      15, 9, 2,   // tri1
                      2, 1, 16,   // tri2
                      7, 0, 12    // tri3
                      ),
    gsSPNTriangles_5b(12, 9, 14, // tri0
                      2, 12, 0,  // tri1
                      9, 12, 2,  // tri2
                      16, 15, 2  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x040, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&tig_1_v[38], 32, 0),
    gsSPNTrianglesInit_5b(36,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 2, 1  // tri2
                          ),
    gsSPNTriangles_5b(0, 7, 3,  // tri0
                      8, 1, 0,  // tri1
                      2, 9, 0,  // tri2
                      10, 11, 5 // tri3
                      ),
    gsSPNTriangles_5b(12, 13, 7, // tri0
                      9, 2, 6,   // tri1
                      9, 14, 12, // tri2
                      0, 9, 15   // tri3
                      ),
    gsSPNTriangles_5b(6, 16, 17,  // tri0
                      18, 19, 20, // tri1
                      13, 4, 3,   // tri2
                      1, 16, 6    // tri3
                      ),
    gsSPNTriangles_5b(0, 21, 8,   // tri0
                      17, 18, 22, // tri1
                      7, 15, 12,  // tri2
                      18, 17, 8   // tri3
                      ),
    gsSPNTriangles_5b(14, 23, 24, // tri0
                      8, 16, 1,   // tri1
                      7, 13, 3,   // tri2
                      12, 14, 4   // tri3
                      ),
    gsSPNTriangles_5b(8, 17, 16, // tri0
                      3, 21, 0,  // tri1
                      15, 7, 0,  // tri2
                      17, 25, 6  // tri3
                      ),
    gsSPNTriangles_5b(4, 13, 12, // tri0
                      12, 15, 9, // tri1
                      6, 25, 9,  // tri2
                      14, 9, 25  // tri3
                      ),
    gsSPNTriangles_5b(26, 23, 27, // tri0
                      28, 29, 30, // tri1
                      10, 5, 24,  // tri2
                      22, 18, 20  // tri3
                      ),
    gsSPNTriangles_5b(31, 30, 29, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&tig_1_v[70], 27, 0),
    gsSPNTrianglesInit_5b(11,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(3, 2, 7, // tri0
                      8, 4, 6, // tri1
                      3, 7, 9, // tri2
                      10, 8, 6 // tri3
                      ),
    gsSPNTriangles_5b(3, 11, 12, // tri0
                      3, 12, 13, // tri1
                      6, 5, 14,  // tri2
                      14, 15, 6  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x140, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(9,          // tri count
                          16, 17, 18, // tri0
                          19, 20, 21, // tri1
                          18, 22, 16  // tri2
                          ),
    gsSPNTriangles_5b(23, 24, 20, // tri0
                      23, 17, 16, // tri1
                      18, 25, 22, // tri2
                      17, 23, 19  // tri3
                      ),
    gsSPNTriangles_5b(20, 19, 23, // tri0
                      26, 25, 18, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x1C0, G_IM_FMT_CI, 32, 40, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&tig_1_v[97], 32, 0),
    gsSPNTrianglesInit_5b(23,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          5, 6, 3  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 6,    // tri0
                      9, 10, 11,  // tri1
                      12, 13, 14, // tri2
                      15, 0, 2    // tri3
                      ),
    gsSPNTriangles_5b(7, 6, 5,    // tri0
                      16, 17, 18, // tri1
                      5, 3, 19,   // tri2
                      18, 20, 21  // tri3
                      ),
    gsSPNTriangles_5b(0, 3, 22,   // tri0
                      23, 5, 19,  // tri1
                      13, 24, 25, // tri2
                      26, 10, 19  // tri3
                      ),
    gsSPNTriangles_5b(14, 17, 16, // tri0
                      27, 28, 20, // tri1
                      27, 20, 15, // tri2
                      3, 6, 29    // tri3
                      ),
    gsSPNTriangles_5b(11, 13, 25, // tri0
                      19, 10, 30, // tri1
                      26, 4, 17,  // tri2
                      31, 27, 15  // tri3
                      ),
    gsSPVertex(&tig_1_v[129], 30, 0),
    gsSPNTrianglesInit_5b(22,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(9, 10, 8, // tri0
                      5, 11, 0, // tri1
                      0, 2, 12, // tri2
                      13, 14, 7 // tri3
                      ),
    gsSPNTriangles_5b(15, 16, 17, // tri0
                      18, 19, 6,  // tri1
                      18, 6, 3,   // tri2
                      0, 16, 3    // tri3
                      ),
    gsSPNTriangles_5b(0, 3, 5,   // tri0
                      8, 20, 4,  // tri1
                      4, 6, 8,   // tri2
                      12, 17, 16 // tri3
                      ),
    gsSPNTriangles_5b(5, 21, 22,  // tri0
                      23, 13, 19, // tri1
                      18, 15, 24, // tri2
                      25, 20, 26  // tri3
                      ),
    gsSPNTriangles_5b(27, 4, 20,  // tri0
                      28, 11, 29, // tri1
                      29, 11, 22, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x440, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&tig_1_v[159], 18, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(4, 9, 10, // tri0
                      0, 2, 11, // tri1
                      12, 5, 4, // tri2
                      8, 13, 6  // tri3
                      ),
    gsSPNTriangles_5b(14, 15, 3, // tri0
                      11, 16, 0, // tri1
                      10, 12, 4, // tri2
                      3, 17, 14  // tri3
                      ),
    gsSPNTriangles_5b(6, 13, 1, // tri0
                      5, 17, 3, // tri1
                      1, 0, 6,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx mouth_tig_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*13, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tig_1_v[0], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*12, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&tig_1_v[5], 16, 5),
    gsSPNTrianglesInit_5b(8,       // tri count
                          1, 5, 6, // tri0
                          2, 7, 8, // tri1
                          4, 0, 9  // tri2
                          ),
    gsSPNTriangles_5b(3, 10, 11, // tri0
                      4, 12, 3,  // tri1
                      0, 2, 13,  // tri2
                      0, 14, 15  // tri3
                      ),
    gsSPNTriangles_5b(1, 3, 16, // tri0
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

static Gfx Rarm2_tig_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tig_1_v[214], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*11, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x480, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&tig_1_v[219], 17, 5),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 5, 6, // tri0
                          3, 7, 8, // tri1
                          4, 9, 10 // tri2
                          ),
    gsSPNTriangles_5b(0, 1, 11,  // tri0
                      1, 4, 12,  // tri1
                      0, 13, 14, // tri2
                      2, 0, 15   // tri3
                      ),
    gsSPNTriangles_5b(3, 2, 16, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPNTrianglesInit_5b(2,          // tri count
                          17, 18, 19, // tri0
                          20, 21, 18, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rarm1_tig_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tig_1_v[236], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x480, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&tig_1_v[240], 11, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 2, 4, // tri0
                          3, 6, 5, // tri1
                          1, 8, 7  // tri2
                          ),
    gsSPNTriangles_5b(3, 1, 9,   // tri0
                      1, 0, 10,  // tri1
                      0, 11, 12, // tri2
                      2, 13, 14  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Larm2_tig_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tig_1_v[177], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*9, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x480, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&tig_1_v[182], 17, 5),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 5, 6, // tri0
                          3, 7, 8, // tri1
                          4, 9, 10 // tri2
                          ),
    gsSPNTriangles_5b(1, 0, 11,  // tri0
                      4, 1, 12,  // tri1
                      0, 13, 14, // tri2
                      0, 2, 15   // tri3
                      ),
    gsSPNTriangles_5b(2, 3, 16, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPNTrianglesInit_5b(2,          // tri count
                          17, 18, 19, // tri0
                          18, 20, 21, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Larm1_tig_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tig_1_v[199], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x480, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&tig_1_v[203], 11, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          2, 0, 4, // tri0
                          3, 6, 5, // tri1
                          1, 8, 7  // tri2
                          ),
    gsSPNTriangles_5b(1, 3, 9,   // tri0
                      0, 1, 10,  // tri1
                      0, 11, 12, // tri2
                      2, 13, 14  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx chest_tig_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tig_1_v[251], 7, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_3_txt, G_IM_FMT_CI, 32, 32, 14, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&tig_1_v[258], 20, 7),
    gsSPNTrianglesInit_5b(13,       // tri count
                          0, 2, 7,  // tri0
                          6, 8, 9,  // tri1
                          0, 10, 11 // tri2
                          ),
    gsSPNTriangles_5b(1, 12, 5,  // tri0
                      1, 13, 14, // tri1
                      2, 16, 15, // tri2
                      5, 17, 18  // tri3
                      ),
    gsSPNTriangles_5b(5, 19, 20, // tri0
                      2, 21, 22, // tri1
                      6, 0, 23,  // tri2
                      1, 6, 24   // tri3
                      ),
    gsSPNTriangles_5b(3, 5, 25, // tri0
                      4, 26, 2, // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPVertex(&tig_1_v[278], 10, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          0, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(5, 4, 8, // tri0
                      2, 6, 0, // tri1
                      1, 9, 2, // tri2
                      7, 4, 3  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx tail1_tig_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x500, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tig_1_v[312], 8, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          2, 1, 5  // tri2
                          ),
    gsSPNTriangles_5b(4, 6, 3, // tri0
                      5, 7, 2, // tri1
                      2, 4, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx tail2_tig_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tig_1_v[288], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*6, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x500, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&tig_1_v[292], 20, 4),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 4, 5, // tri0
                          1, 6, 7, // tri1
                          3, 8, 9  // tri2
                          ),
    gsSPNTriangles_5b(3, 2, 10, // tri0
                      2, 1, 11, // tri1
                      0, 3, 12, // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPNTrianglesInit_5b(9,          // tri count
                          13, 14, 15, // tri0
                          16, 14, 17, // tri1
                          18, 17, 19  // tri2
                          ),
    gsSPNTriangles_5b(17, 14, 13, // tri0
                      13, 19, 17, // tri1
                      17, 18, 20, // tri2
                      21, 15, 14  // tri3
                      ),
    gsSPNTriangles_5b(15, 22, 13, // tri0
                      19, 23, 18, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot2_tig_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tig_1_v[361], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*4, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x480, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&tig_1_v[366], 17, 5),
    gsSPNTrianglesInit_5b(9,       // tri count
                          3, 5, 6, // tri0
                          2, 3, 7, // tri1
                          0, 2, 8  // tri2
                          ),
    gsSPNTriangles_5b(1, 9, 10,  // tri0
                      4, 1, 11,  // tri1
                      2, 12, 13, // tri2
                      3, 4, 14   // tri3
                      ),
    gsSPNTriangles_5b(1, 15, 16, // tri0
                      3, 17, 18, // tri1
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

static Gfx Rfoot1_tig_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tig_1_v[383], 6, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x480, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&tig_1_v[389], 13, 6),
    gsSPNTrianglesInit_5b(9,       // tri count
                          2, 6, 7, // tri0
                          3, 8, 9, // tri1
                          3, 4, 10 // tri2
                          ),
    gsSPNTriangles_5b(4, 2, 11, // tri0
                      0, 3, 12, // tri1
                      5, 1, 13, // tri2
                      5, 14, 15 // tri3
                      ),
    gsSPNTriangles_5b(2, 5, 16,  // tri0
                      0, 17, 18, // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot2_tig_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tig_1_v[320], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x480, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&tig_1_v[325], 17, 5),
    gsSPNTrianglesInit_5b(9,       // tri count
                          3, 5, 6, // tri0
                          3, 2, 7, // tri1
                          2, 0, 8  // tri2
                          ),
    gsSPNTriangles_5b(1, 9, 10,  // tri0
                      1, 4, 11,  // tri1
                      2, 12, 13, // tri2
                      4, 3, 14   // tri3
                      ),
    gsSPNTriangles_5b(1, 15, 16, // tri0
                      3, 17, 18, // tri1
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

static Gfx Lfoot1_tig_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tig_1_v[342], 6, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x480, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&tig_1_v[348], 13, 6),
    gsSPNTrianglesInit_5b(9,       // tri count
                          1, 6, 7, // tri0
                          2, 8, 9, // tri1
                          0, 2, 10 // tri2
                          ),
    gsSPNTriangles_5b(1, 0, 11, // tri0
                      2, 4, 12, // tri1
                      5, 3, 13, // tri2
                      3, 14, 15 // tri3
                      ),
    gsSPNTriangles_5b(3, 1, 16,  // tri0
                      4, 17, 18, // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx base_tig_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x480, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tig_1_v[402], 26, 0),
    gsSPNTrianglesInit_5b(3,       // tri count
                          0, 1, 2, // tri0
                          3, 1, 0, // tri1
                          2, 1, 4  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_3_txt, G_IM_FMT_CI, 32, 32, 14, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPNTrianglesInit_5b(14,        // tri count
                          5, 6, 7,   // tri0
                          8, 9, 10,  // tri1
                          11, 12, 13 // tri2
                          ),
    gsSPNTriangles_5b(14, 15, 16, // tri0
                      7, 17, 5,   // tri1
                      18, 9, 19,  // tri2
                      18, 19, 15  // tri3
                      ),
    gsSPNTriangles_5b(10, 13, 12, // tri0
                      9, 18, 10,  // tri1
                      6, 5, 11,   // tri2
                      11, 13, 6   // tri3
                      ),
    gsSPNTriangles_5b(19, 16, 15, // tri0
                      12, 8, 10,  // tri1
                      16, 20, 14, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x480, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3,          // tri count
                          21, 22, 23, // tri0
                          23, 22, 24, // tri1
                          25, 22, 21  // tri2
                          ),
    gsSPEndDisplayList(),
};

// clang-format off
static cKF_Joint_R_c cKF_je_r_tig_1_tbl[] = {
    /* joint 0 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,1000,0 },
    /* joint 1 */ { base_tig_model, 4, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 2 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,-250,0 },
    /* joint 3 */ { Lfoot1_tig_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 4 */ { Lfoot2_tig_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 5 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 6 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,250,0 },
    /* joint 7 */ { Rfoot1_tig_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 8 */ { Rfoot2_tig_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 9 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 10 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 75,0,-475 },
    /* joint 11 */ { tail1_tig_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 12 */ { tail2_tig_model, 0, cKF_JOINT_FLAG_DISP_OPA, 650,0,0 },
    /* joint 13 */ { chest_tig_model, 3, cKF_JOINT_FLAG_DISP_OPA, 325,0,0 },
    /* joint 14 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 450,-500,0 },
    /* joint 15 */ { Larm1_tig_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 16 */ { Larm2_tig_model, 0, cKF_JOINT_FLAG_DISP_OPA, 350,0,0 },
    /* joint 17 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 450,500,0 },
    /* joint 18 */ { Rarm1_tig_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 19 */ { Rarm2_tig_model, 1, cKF_JOINT_FLAG_DISP_OPA, 350,0,0 },
    /* joint 20 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 350,0,0 },
    /* joint 21 */ { NULL, 2, cKF_JOINT_FLAG_DISP_OPA, 675,0,0 },
    /* joint 22 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 100,0,700 },
    /* joint 23 */ { mouth_tig_model, 0, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 24 */ { head_tig_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 25 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 1300,0,0 },
};
// clang-format on

extern cKF_Skeleton_R_c cKF_bs_r_tig_1 = { 26, 14, cKF_je_r_tig_1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_npc_model_mdl_tig_1_c(void) {
    pc_load_asset("assets/npc/mdl/tig_1_v.bin", tig_1_v, 0x1AC0, 0x8BC838, 0, 2);
}
#endif

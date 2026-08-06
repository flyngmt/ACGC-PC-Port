#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 hnd_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 hnd_pal[] = {
#include "assets/hnd_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 hnd_white_txt[0x20];
#else
u8 hnd_white_txt[] = {
#include "assets/hnd_white_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 hnd_fin_txt[0x80];
#else
u8 hnd_fin_txt[] = {
#include "assets/hnd_fin_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 hnd_back_txt[0x200];
#else
u8 hnd_back_txt[] = {
#include "assets/hnd_back_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 hnd_neck_txt[0x80];
#else
u8 hnd_neck_txt[] = {
#include "assets/hnd_neck_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 hnd_front_txt[0x200];
#else
u8 hnd_front_txt[] = {
#include "assets/hnd_front_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx hnd_v[0x1320 / sizeof(Vtx)];
#else
Vtx hnd_v[] = {
#include "assets/hnd_v.inc"
};
#endif

Gfx ko_hnd_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&hnd_v[143], 7, 0),
    gsSPMatrix(&anime_6_mdl[10], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, hnd_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, hnd_white_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&hnd_v[150], 12, 7),
    gsSPNTrianglesInit_5b(6, 2, 0, 7, 3, 9, 8, 3, 2, 10),
    gsSPNTriangles_5b(4, 3, 11, 4, 13, 12, 2, 15, 14, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, hnd_fin_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 5, 16, 1, 6, 17, 18, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx koT_hnd_model[] = {
    gsSPMatrix(&anime_6_mdl[10], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&hnd_v[121], 4, 0),
    gsSPMatrix(&anime_6_mdl[9], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, hnd_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, hnd_white_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&hnd_v[125], 18, 4),
    gsSPNTrianglesInit_5b(8, 2, 4, 5, 0, 6, 7, 1, 2, 8),
    gsSPNTriangles_5b(0, 3, 9, 1, 10, 3, 2, 11, 12, 0, 13, 2),
    gsSPNTriangles_5b(1, 15, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(6, 16, 17, 18, 18, 17, 19, 19, 20, 21),
    gsSPNTriangles_5b(16, 19, 17, 20, 19, 16, 19, 21, 18, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kusuri_hnd_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&hnd_v[62], 7, 0),
    gsSPMatrix(&anime_6_mdl[8], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, hnd_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, hnd_white_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&hnd_v[69], 12, 7),
    gsSPNTrianglesInit_5b(6, 1, 7, 8, 1, 9, 4, 1, 11, 10),
    gsSPNTriangles_5b(3, 12, 0, 1, 0, 13, 0, 14, 15, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, hnd_fin_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 5, 16, 2, 6, 17, 18, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kusuriT_hnd_model[] = {
    gsSPMatrix(&anime_6_mdl[8], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&hnd_v[40], 4, 0),
    gsSPMatrix(&anime_6_mdl[7], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, hnd_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, hnd_white_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&hnd_v[44], 18, 4),
    gsSPNTrianglesInit_5b(8, 2, 4, 5, 2, 3, 6, 1, 0, 7),
    gsSPNTriangles_5b(1, 9, 8, 3, 10, 11, 2, 13, 12, 3, 1, 14),
    gsSPNTriangles_5b(2, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(6, 16, 17, 18, 19, 20, 21, 18, 17, 19),
    gsSPNTriangles_5b(19, 17, 16, 16, 20, 19, 18, 19, 21, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx naka_hnd_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&hnd_v[103], 6, 0),
    gsSPMatrix(&anime_6_mdl[6], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, hnd_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, hnd_white_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&hnd_v[109], 12, 6),
    gsSPNTrianglesInit_5b(6, 0, 2, 6, 0, 7, 8, 0, 9, 10),
    gsSPNTriangles_5b(1, 11, 12, 5, 1, 13, 0, 14, 1, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, hnd_fin_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 3, 4, 15, 3, 16, 17, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx nakaT_hnd_model[] = {
    gsSPMatrix(&anime_6_mdl[6], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&hnd_v[81], 4, 0),
    gsSPMatrix(&anime_6_mdl[5], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, hnd_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, hnd_white_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&hnd_v[85], 18, 4),
    gsSPNTrianglesInit_5b(8, 0, 2, 4, 3, 0, 5, 0, 7, 6),
    gsSPNTriangles_5b(2, 8, 9, 1, 3, 10, 1, 11, 2, 3, 13, 12),
    gsSPNTriangles_5b(2, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(6, 16, 17, 18, 19, 20, 21, 17, 16, 20),
    gsSPNTriangles_5b(18, 17, 21, 21, 17, 19, 20, 19, 17, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx hito_hnd_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&hnd_v[22], 6, 0),
    gsSPMatrix(&anime_6_mdl[4], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, hnd_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, hnd_white_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&hnd_v[28], 12, 6),
    gsSPNTrianglesInit_5b(6, 3, 7, 6, 2, 8, 9, 2, 5, 10),
    gsSPNTriangles_5b(3, 2, 11, 2, 13, 12, 1, 3, 14, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, hnd_fin_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 4, 0, 15, 4, 16, 17, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx hitoT_hnd_model[] = {
    gsSPMatrix(&anime_6_mdl[4], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(hnd_v, 4, 0),
    gsSPMatrix(&anime_6_mdl[3], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, hnd_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, hnd_white_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&hnd_v[4], 18, 4),
    gsSPNTrianglesInit_5b(8, 0, 3, 4, 3, 2, 5, 0, 6, 7),
    gsSPNTriangles_5b(2, 8, 9, 0, 10, 11, 1, 13, 12, 0, 14, 1),
    gsSPNTriangles_5b(2, 1, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(6, 16, 17, 18, 18, 17, 19, 20, 18, 21),
    gsSPNTriangles_5b(20, 16, 18, 19, 17, 16, 21, 18, 19, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx oya_hnd_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&hnd_v[188], 9, 0),
    gsSPMatrix(&anime_6_mdl[2], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, hnd_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, hnd_white_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&hnd_v[197], 21, 9),
    gsSPNTrianglesInit_5b(9, 7, 10, 9, 7, 5, 11, 3, 12, 5),
    gsSPNTriangles_5b(1, 13, 2, 2, 15, 14, 3, 16, 17, 2, 18, 3),
    gsSPNTriangles_5b(1, 20, 19, 1, 21, 22, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, hnd_back_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(5, 8, 4, 23, 8, 25, 24, 8, 26, 0),
    gsSPNTriangles_5b(4, 6, 27, 4, 29, 28, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, hnd_white_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&hnd_v[218], 10, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 2, 3, 0, 3, 4, 0),
    gsSPNTriangles_5b(5, 4, 3, 6, 5, 7, 8, 2, 1, 4, 5, 9),
    gsSPNTriangles_5b(9, 5, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx oyaT_hnd_model[] = {
    gsSPMatrix(&anime_6_mdl[2], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&hnd_v[162], 5, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, hnd_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, hnd_white_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&hnd_v[167], 21, 5),
    gsSPNTrianglesInit_5b(10, 0, 6, 5, 0, 8, 7, 0, 1, 9),
    gsSPNTriangles_5b(1, 11, 10, 2, 12, 13, 1, 2, 14, 3, 15, 16),
    gsSPNTriangles_5b(3, 4, 17, 4, 0, 18, 3, 19, 2, 0, 0, 0),
    gsSPNTrianglesInit_5b(5, 20, 21, 22, 21, 20, 23, 22, 21, 24),
    gsSPNTriangles_5b(21, 23, 25, 21, 25, 24, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx body_hnd_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, hnd_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, hnd_white_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&hnd_v[228], 29, 0),
    gsSPNTrianglesInit_5b(19, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 7, 9, 10, 5, 1, 0, 3, 2, 9),
    gsSPNTriangles_5b(9, 2, 10, 11, 12, 13, 7, 14, 4, 0, 6, 5),
    gsSPNTriangles_5b(15, 11, 13, 15, 16, 11, 14, 5, 4, 4, 8, 7),
    gsSPNTriangles_5b(17, 18, 19, 20, 19, 18, 17, 21, 22, 19, 21, 17),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, hnd_neck_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 23, 24, 25, 26, 24, 23, 23, 27, 26),
    gsSPNTriangles_5b(25, 28, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&hnd_v[257], 24, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(1, 0, 9, 10, 11, 12, 13, 14, 15, 16, 14, 13),
    gsSPNTriangles_5b(17, 12, 11, 18, 19, 20, 5, 21, 3, 8, 22, 6),
    gsSPNTriangles_5b(18, 23, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, hnd_front_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&hnd_v[281], 25, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 2, 3, 4, 5, 0, 2),
    gsSPNTriangles_5b(5, 6, 0, 5, 2, 7, 2, 8, 3, 2, 4, 7),
    gsSPNTriangles_5b(1, 0, 9, 10, 5, 7, 2, 1, 8, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, hnd_back_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(16, 11, 12, 13, 14, 12, 11, 15, 12, 14),
    gsSPNTriangles_5b(16, 14, 17, 18, 19, 20, 14, 11, 17, 21, 15, 22),
    gsSPNTriangles_5b(23, 19, 24, 13, 23, 24, 12, 23, 13, 20, 23, 21),
    gsSPNTriangles_5b(20, 19, 23, 21, 12, 15, 21, 23, 12, 14, 22, 15),
    gsSPNTriangles_5b(16, 22, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_hnd_sasu_tbl[] = { 0, 7, 0, 0, 7, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_kn_hnd_sasu_tbl[] = { 12, 13, 13, 10, 11, 12, 13 };

s16 cKF_c_hnd_sasu_tbl[] = { 789,   722,   135,  -900,  0,     0,   92,    -1644, 589,  0,     0,     -1800,
                             0,     0,     -94,  92,    -1644, 475, 92,    -1644, 238,  -1800, -1800, 0,
                             0,     0,     1800, 1,     3,     204, -1714, 563,   92,   -1644, 589,   0,
                             0,     -1800, 0,    855,   1800,  0,   986,   0,     204,  -1714, 566,   92,
                             -1644, 589,   0,    0,     -1800, 116, 883,   -1684, -187, 1044,  -200,  204,
                             -1714, 566,   92,   -1644, 586,   0,   0,     -1800, 0,    884,   1800,  -414,
                             1072,  -435,  204,  -1714, 563,   92,  -1644, 589 };

s16 cKF_ds_hnd_sasu_tbl[] = {
    1,  -330,  -2117, 2,  -401,  -2117,  3,  -471,  -510,  4,  -435,  1568,  5,  -367,  1568,  6,  -330,  2173,
    7,  -222,  3249,  8,  -113,  225,    9,  -207,  -2799, 10, -300,  -1433, 11, -302,  -117,  15, -328,  -167,
    1,  100,   -2984, 2,  1,     -2984,  3,  -99,   -718,  4,  -47,   2210,  5,  48,    2210,  6,  100,   -676,
    7,  3,     -2899, 8,  -93,   275,    9,  22,    3449,  10, 137,   1684,  11, 134,   -143,  14, 110,   -234,
    15, 103,   -204,  1,  1800,  5845,   2,  1995,  5845,  3,  2190,  1407,  4,  2089,  -4329, 5,  1901,  -4329,
    6,  1800,  368,   7,  1926,  3767,   8,  2051,  -266,  9,  1908,  -4300, 10, 1764,  -2110, 11, 1767,  138,
    14, 1791,  227,   15, 1797,  197,    1,  175,   -554,  2,  157,   -554,  3,  139,   -133,  6,  175,   -133,
    7,  157,   -554,  8,  139,   0,      9,  157,   554,   10, 175,   277,   11, 175,   0,     15, 175,   0,
    1,  232,   345,   2,  243,   345,    3,  255,   83,    5,  238,   -256,  6,  232,   83,    7,  243,   345,
    8,  255,   0,     9,  243,   -345,   10, 232,   -172,  11, 232,   0,     15, 232,   0,     1,  -1412, -1344,
    2,  -1457, -1344, 3,  -1502, -324,   4,  -1478, 995,   5,  -1435, 995,   6,  -1412, -324,  7,  -1457, -1344,
    8,  -1502, 0,     9,  -1457, 1344,   10, -1412, 672,   11, -1412, 0,     15, -1412, 0,     1,  130,   8973,
    2,  429,   8973,  3,  728,   2160,   4,  573,   -6646, 5,  285,   -6646, 6,  130,   2160,  7,  429,   8973,
    8,  728,   -808,  9,  375,   -10588, 10, 22,    -5174, 11, 30,    419,   14, 102,   688,   15, 122,   598
};

cKF_Animation_R_c cKF_ba_r_hnd_sasu = {
    cKF_ckcb_r_hnd_sasu_tbl, cKF_ds_hnd_sasu_tbl, cKF_kn_hnd_sasu_tbl, cKF_c_hnd_sasu_tbl, -1, 15
};

u8 cKF_ckcb_r_hnd_side_tbl[] = { 0, 7, 0, 0, 7, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_kn_hnd_side_tbl[] = { 12, 13, 13, 10, 11, 12, 13 };

s16 cKF_c_hnd_side_tbl[] = { 789,   722,   135,  -900,  0,     0,   92,    -1644, 589,  0,     0,     -1800,
                             0,     0,     -94,  92,    -1644, 475, 92,    -1644, 238,  -1800, -1800, 0,
                             0,     0,     1800, 1,     3,     204, -1714, 563,   92,   -1644, 589,   0,
                             0,     -1800, 0,    855,   1800,  0,   986,   0,     204,  -1714, 566,   92,
                             -1644, 589,   0,    0,     -1800, 116, 883,   -1684, -187, 1044,  -200,  204,
                             -1714, 566,   92,   -1644, 586,   0,   0,     -1800, 0,    884,   1800,  -414,
                             1072,  -435,  204,  -1714, 563,   92,  -1644, 589 };

s16 cKF_ds_hnd_side_tbl[] = {
    1,  -330,  -2117, 2,  -401,  -2117,  3,  -471,  -510,  4,  -435,  1568,  5,  -367,  1568,  6,  -330,  2173,
    7,  -222,  3249,  8,  -113,  225,    9,  -207,  -2799, 10, -300,  -1433, 11, -302,  -117,  15, -328,  -167,
    1,  100,   -2984, 2,  1,     -2984,  3,  -99,   -718,  4,  -47,   2210,  5,  48,    2210,  6,  100,   -676,
    7,  3,     -2899, 8,  -93,   275,    9,  22,    3449,  10, 137,   1684,  11, 134,   -143,  14, 110,   -234,
    15, 103,   -204,  1,  1800,  5845,   2,  1995,  5845,  3,  2190,  1407,  4,  2089,  -4329, 5,  1901,  -4329,
    6,  1800,  368,   7,  1926,  3767,   8,  2051,  -266,  9,  1908,  -4300, 10, 1764,  -2110, 11, 1767,  138,
    14, 1791,  227,   15, 1797,  197,    1,  175,   -554,  2,  157,   -554,  3,  139,   -133,  6,  175,   -133,
    7,  157,   -554,  8,  139,   0,      9,  157,   554,   10, 175,   277,   11, 175,   0,     15, 175,   0,
    1,  232,   345,   2,  243,   345,    3,  255,   83,    5,  238,   -256,  6,  232,   83,    7,  243,   345,
    8,  255,   0,     9,  243,   -345,   10, 232,   -172,  11, 232,   0,     15, 232,   0,     1,  -1412, -1344,
    2,  -1457, -1344, 3,  -1502, -324,   4,  -1478, 995,   5,  -1435, 995,   6,  -1412, -324,  7,  -1457, -1344,
    8,  -1502, 0,     9,  -1457, 1344,   10, -1412, 672,   11, -1412, 0,     15, -1412, 0,     1,  130,   8973,
    2,  429,   8973,  3,  728,   2160,   4,  573,   -6646, 5,  285,   -6646, 6,  130,   2160,  7,  429,   8973,
    8,  728,   -808,  9,  375,   -10588, 10, 22,    -5174, 11, 30,    419,   14, 102,   688,   15, 122,   598
};

cKF_Animation_R_c cKF_ba_r_hnd_side = {
    cKF_ckcb_r_hnd_side_tbl, cKF_ds_hnd_side_tbl, cKF_kn_hnd_side_tbl, cKF_c_hnd_side_tbl, -1, 15
};

u8 cKF_ckcb_r_hnd_catch_tbl[] = { 0, 7, 0, 0, 7, 7, 0, 0, 0, 2, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_kn_hnd_catch_tbl[] = { 5, 5, 5, 6, 6, 4, 6, 6, 6, 5, 7, 6, 7 };

s16 cKF_c_hnd_catch_tbl[] = { 789,   722,   135,   -900,  0,     0,     92,    -1644, 589,  0,     0,     -1800, 92,
                              -1644, 475,   92,    -1644, 238,   -1800, -1800, 0,     0,    1800,  204,   -1714, 563,
                              92,    -1644, 589,   0,     0,     -1800, 0,     884,   1800, 0,     1112,  0,     204,
                              -1714, 566,   92,    -1644, 589,   0,     0,     -1800, 116,  883,   -1684, -118,  1117,
                              -134,  204,   -1714, 566,   92,    -1644, 586,   0,     0,    -1800, 0,     884,   1800,
                              -414,  1072,  -435,  204,   -1714, 563,   92,    -1644, 589 };

s16 cKF_ds_hnd_catch_tbl[] = { 1, -1582, 0,      4, -1582, 0,     5, -1582, 638,    6, -1539, 1276,  7, -1497, 1276,
                               1, 273,   0,      4, 273,   0,     5, 273,   508,    6, 307,   1015,  7, 340,   1015,
                               1, 1764,  0,      4, 1764,  0,     5, 1764,  206,    6, 1778,  412,   7, 1791,  412,
                               1, 175,   -2260,  2, 100,   -3615, 4, -231,  -3615,  5, -307,  -1130, 6, -307,  0,
                               7, -307,  0,      1, 232,   533,   2, 249,   853,    4, 328,   853,   5, 345,   267,
                               6, 345,   0,      7, 345,   0,     1, -1412, -169,   2, -1418, -270,  4, -1442, -270,
                               7, -1448, 0,      1, 0,     401,   2, 13,    642,    4, 72,    642,   5, 86,    -13,
                               6, 71,    -427,   7, 57,    -427,  1, 0,     1008,   2, 34,    1613,  4, 181,   1613,
                               5, 215,   570,    6, 219,   133,   7, 224,   133,    1, -94,   -1556, 2, -146,  -2490,
                               4, -374,  -2490,  5, -426,  -1348, 6, -464,  -1140,  7, -502,  -1140, 1, 0,     904,
                               2, 30,    1582,   4, 203,   2938,  6, 377,   1582,   7, 407,   904,   1, 1,     -821,
                               2, -27,   -819,   3, -54,   -2793, 4, -213,  -13995, 5, -987,  64,    6, -209,  13751,
                               7, -70,   4155,   1, 130,   4526,  2, 281,   6174,   3, 542,   7634,  4, 790,   4593,
                               6, 776,   -3155,  7, 637,   -4150, 1, 3,     -927,   2, -28,   -928,  3, -59,   -3397,
                               4, -254,  -14337, 5, -1015, 493,   6, -221,  13853,  7, -91,   3912 };

cKF_Animation_R_c cKF_ba_r_hnd_catch = {
    cKF_ckcb_r_hnd_catch_tbl, cKF_ds_hnd_catch_tbl, cKF_kn_hnd_catch_tbl, cKF_c_hnd_catch_tbl, -1, 7
};

cKF_Joint_R_c cKF_je_r_hnd_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 789, 722, 135 } },
                                     { NULL, 6, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                     { body_hnd_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 3430, 652, 65313 } },
                                     { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 468, 625, 65176 } },
                                     { NULL, 2, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                     { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 915, 0, 0 } },
                                     { oyaT_hnd_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 2069, 64605, 136 } },
                                     { oya_hnd_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 2436, 63852, 136 } },
                                     { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 1577, 668, 0 } },
                                     { NULL, 2, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                     { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 879, 0, 0 } },
                                     { hitoT_hnd_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 999, 65515, 2 } },
                                     { hito_hnd_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1853, 65520, 65313 } },
                                     { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 1663, 136, 0 } },
                                     { NULL, 2, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                     { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 889, 0, 0 } },
                                     { nakaT_hnd_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 906, 516, 65516 } },
                                     { naka_hnd_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1767, 516, 65313 } },
                                     { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 1612, 65144, 0 } },
                                     { NULL, 2, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                     { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 849, 0, 0 } },
                                     { kusuriT_hnd_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 994, 1039, 1 } },
                                     { kusuri_hnd_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1824, 1033, 65313 } },
                                     { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 1462, 64657, 0 } },
                                     { NULL, 2, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                     { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 743, 0, 0 } },
                                     { koT_hnd_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1252, 1524, 58 } },
                                     { ko_hnd_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1968, 1531, 65313 } } };

cKF_Skeleton_R_c cKF_bs_r_hnd = { ARRAY_COUNT(cKF_je_r_hnd_tbl), 11, cKF_je_r_hnd_tbl };

#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
static u8 inv_mwin_nwaku_tex[0x400] ATTRIBUTE_ALIGN(32);
#else
static u8 inv_mwin_nwaku_tex[] ATTRIBUTE_ALIGN(32)= {
#include "assets/ctl_win1/inv_mwin_nwaku_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 ctl_win_aw1_tex[0x800] ATTRIBUTE_ALIGN(32);
#else
u8 ctl_win_aw1_tex[] ATTRIBUTE_ALIGN(32)= {
#include "assets/ctl_win_aw1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 ctl_win_aw2_tex[0x400] ATTRIBUTE_ALIGN(32);
#else
u8 ctl_win_aw2_tex[] ATTRIBUTE_ALIGN(32)= {
#include "assets/ctl_win_aw2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 ctl_win_aw3_tex[0x800] ATTRIBUTE_ALIGN(32);
#else
u8 ctl_win_aw3_tex[] ATTRIBUTE_ALIGN(32)= {
#include "assets/ctl_win_aw3_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 ctl_win_aw4_tex[0x400] ATTRIBUTE_ALIGN(32);
#else
u8 ctl_win_aw4_tex[] ATTRIBUTE_ALIGN(32)= {
#include "assets/ctl_win_aw4_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 ctl_win_aw5_tex[0x400] ATTRIBUTE_ALIGN(32);
#else
u8 ctl_win_aw5_tex[] ATTRIBUTE_ALIGN(32)= {
#include "assets/ctl_win_aw5_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 ctl_win_kage1_tex[0x200] ATTRIBUTE_ALIGN(32);
#else
u8 ctl_win_kage1_tex[] ATTRIBUTE_ALIGN(32)= {
#include "assets/ctl_win_kage1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 ctl_win_aw6_tex[0x400] ATTRIBUTE_ALIGN(32);
#else
u8 ctl_win_aw6_tex[] ATTRIBUTE_ALIGN(32)= {
#include "assets/ctl_win_aw6_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 ctl_win_tagu2_tex[0x200] ATTRIBUTE_ALIGN(32);
#else
static u8 ctl_win_tagu2_tex[] ATTRIBUTE_ALIGN(32)= {
#include "assets/ctl_win1/ctl_win_tagu2_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 ctl_win_waku1_tex[0x800] ATTRIBUTE_ALIGN(32);
#else
static u8 ctl_win_waku1_tex[] ATTRIBUTE_ALIGN(32)= {
#include "assets/ctl_win1/ctl_win_waku1_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 ctl_win_waku2_tex[0x800] ATTRIBUTE_ALIGN(32);
#else
static u8 ctl_win_waku2_tex[] ATTRIBUTE_ALIGN(32)= {
#include "assets/ctl_win1/ctl_win_waku2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 ctl_win_aw8_tex[0x100] ATTRIBUTE_ALIGN(32);
#else
u8 ctl_win_aw8_tex[] ATTRIBUTE_ALIGN(32)= {
#include "assets/ctl_win_aw8_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 ctl_win_aw7_tex[0x400] ATTRIBUTE_ALIGN(32);
#else
u8 ctl_win_aw7_tex[] ATTRIBUTE_ALIGN(32)= {
#include "assets/ctl_win_aw7_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 ctl_win_kage2_tex[0x200] ATTRIBUTE_ALIGN(32);
#else
u8 ctl_win_kage2_tex[] ATTRIBUTE_ALIGN(32)= {
#include "assets/ctl_win_kage2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 ctl_win_kage3_tex[0x200] ATTRIBUTE_ALIGN(32);
#else
u8 ctl_win_kage3_tex[] ATTRIBUTE_ALIGN(32)= {
#include "assets/ctl_win_kage3_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 ctl_win_waku3_tex[0x800] ATTRIBUTE_ALIGN(32);
#else
u8 ctl_win_waku3_tex[] ATTRIBUTE_ALIGN(32)= {
#include "assets/ctl_win_waku3_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 ctl_win_waku4_tex[0x800] ATTRIBUTE_ALIGN(32);
#else
u8 ctl_win_waku4_tex[] ATTRIBUTE_ALIGN(32)= {
#include "assets/ctl_win_waku4_tex.inc"
};
#endif

#ifdef TARGET_PC
u16 ctl_win_nuno1_tex_rgb_ci4_pal[0x20 / sizeof(u16)] ATTRIBUTE_ALIGN(32);
#else
u16 ctl_win_nuno1_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32)= {
#include "assets/ctl_win_nuno1_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 ctl_win_nuno2_tex_rgb_ci4_pal[0x20 / sizeof(u16)] ATTRIBUTE_ALIGN(32);
#else
u16 ctl_win_nuno2_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32)= {
#include "assets/ctl_win_nuno2_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 ctl_win_nuno3_tex_rgb_ci4_pal[0x20 / sizeof(u16)] ATTRIBUTE_ALIGN(32);
#else
u16 ctl_win_nuno3_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32)= {
#include "assets/ctl_win_nuno3_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 ctl_win_nuno4_tex_rgb_ci4_pal[0x20 / sizeof(u16)] ATTRIBUTE_ALIGN(32);
#else
u16 ctl_win_nuno4_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32)= {
#include "assets/ctl_win_nuno4_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 ctl_win_nuno5_tex_rgb_ci4_pal[0x20 / sizeof(u16)] ATTRIBUTE_ALIGN(32);
#else
u16 ctl_win_nuno5_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32)= {
#include "assets/ctl_win_nuno5_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 ctl_win_nuno6_tex_rgb_ci4_pal[0x20 / sizeof(u16)] ATTRIBUTE_ALIGN(32);
#else
u16 ctl_win_nuno6_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32)= {
#include "assets/ctl_win_nuno6_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 ctl_win_nuno7_tex_rgb_ci4_pal[0x20 / sizeof(u16)] ATTRIBUTE_ALIGN(32);
#else
u16 ctl_win_nuno7_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32)= {
#include "assets/ctl_win_nuno7_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 ctl_win_nuno8_tex_rgb_ci4_pal[0x20 / sizeof(u16)] ATTRIBUTE_ALIGN(32);
#else
u16 ctl_win_nuno8_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32)= {
#include "assets/ctl_win_nuno8_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 ctl_win_w8_tex_rgb_ci4_pal[0x20 / sizeof(u16)] ATTRIBUTE_ALIGN(32);
#else
u16 ctl_win_w8_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32)= {
#include "assets/ctl_win_w8_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 ctl_win_w1_tex_rgb_ci4_pal[0x20 / sizeof(u16)] ATTRIBUTE_ALIGN(32);
#else
u16 ctl_win_w1_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32)= {
#include "assets/ctl_win_w1_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 ctl_win_w2_tex_rgb_ci4_pal[0x20 / sizeof(u16)] ATTRIBUTE_ALIGN(32);
#else
u16 ctl_win_w2_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32)= {
#include "assets/ctl_win_w2_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 ctl_win_w3_tex_rgb_ci4_pal[0x20 / sizeof(u16)] ATTRIBUTE_ALIGN(32);
#else
u16 ctl_win_w3_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32)= {
#include "assets/ctl_win_w3_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 ctl_win_w4_tex_rgb_ci4_pal[0x20 / sizeof(u16)] ATTRIBUTE_ALIGN(32);
#else
u16 ctl_win_w4_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32)= {
#include "assets/ctl_win_w4_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 ctl_win_w5_tex_rgb_ci4_pal[0x20 / sizeof(u16)] ATTRIBUTE_ALIGN(32);
#else
u16 ctl_win_w5_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32)= {
#include "assets/ctl_win_w5_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 ctl_win_w6_tex_rgb_ci4_pal[0x20 / sizeof(u16)] ATTRIBUTE_ALIGN(32);
#else
u16 ctl_win_w6_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32)= {
#include "assets/ctl_win_w6_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 ctl_win_w7_tex_rgb_ci4_pal[0x20 / sizeof(u16)] ATTRIBUTE_ALIGN(32);
#else
u16 ctl_win_w7_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32)= {
#include "assets/ctl_win_w7_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 ctl_win_nuno1_tex_rgb_ci4[0x200];
#else
u8 ctl_win_nuno1_tex_rgb_ci4[] = {
#include "assets/ctl_win_nuno1_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 ctl_win_nuno2_tex_rgb_ci4[0x200];
#else
u8 ctl_win_nuno2_tex_rgb_ci4[] = {
#include "assets/ctl_win_nuno2_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 ctl_win_nuno3_tex_rgb_ci4[0x200];
#else
u8 ctl_win_nuno3_tex_rgb_ci4[] = {
#include "assets/ctl_win_nuno3_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 ctl_win_nuno4_tex_rgb_ci4[0x200];
#else
u8 ctl_win_nuno4_tex_rgb_ci4[] = {
#include "assets/ctl_win_nuno4_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 ctl_win_nuno5_tex_rgb_ci4[0x200];
#else
u8 ctl_win_nuno5_tex_rgb_ci4[] = {
#include "assets/ctl_win_nuno5_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 ctl_win_nuno6_tex_rgb_ci4[0x200];
#else
u8 ctl_win_nuno6_tex_rgb_ci4[] = {
#include "assets/ctl_win_nuno6_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 ctl_win_nuno7_tex_rgb_ci4[0x200];
#else
u8 ctl_win_nuno7_tex_rgb_ci4[] = {
#include "assets/ctl_win_nuno7_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 ctl_win_nuno8_tex_rgb_ci4[0x200];
#else
u8 ctl_win_nuno8_tex_rgb_ci4[] = {
#include "assets/ctl_win_nuno8_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 ctl_win_w8_tex_rgb_ci4[0x80];
#else
u8 ctl_win_w8_tex_rgb_ci4[] = {
#include "assets/ctl_win_w8_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 ctl_win_w1_tex_rgb_ci4[0x400];
#else
u8 ctl_win_w1_tex_rgb_ci4[] = {
#include "assets/ctl_win_w1_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 ctl_win_w2_tex_rgb_ci4[0x200];
#else
u8 ctl_win_w2_tex_rgb_ci4[] = {
#include "assets/ctl_win_w2_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 ctl_win_w3_tex_rgb_ci4[0x400];
#else
u8 ctl_win_w3_tex_rgb_ci4[] = {
#include "assets/ctl_win_w3_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 ctl_win_w4_tex_rgb_ci4[0x200];
#else
u8 ctl_win_w4_tex_rgb_ci4[] = {
#include "assets/ctl_win_w4_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 ctl_win_w5_tex_rgb_ci4[0x200];
#else
u8 ctl_win_w5_tex_rgb_ci4[] = {
#include "assets/ctl_win_w5_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 ctl_win_w6_tex_rgb_ci4[0x200];
#else
u8 ctl_win_w6_tex_rgb_ci4[] = {
#include "assets/ctl_win_w6_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 ctl_win_w7_tex_rgb_ci4[0x200];
#else
u8 ctl_win_w7_tex_rgb_ci4[] = {
#include "assets/ctl_win_w7_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
Vtx ctl_win1_v[0xBA0 / sizeof(Vtx)];
#else
Vtx ctl_win1_v[] = {
#include "assets/ctl_win1_v.inc"
};
#endif

Gfx ctl_win1_w13_model[] = {
gsDPPipeSync(),
gsDPLoadTLUT_Dolphin(15, 16, 1, ctl_win_w8_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, ctl_win_w8_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(ctl_win1_v, 4, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
gsSPEndDisplayList(),
};

Gfx ctl_win1_ue1T_model[] = {
gsDPPipeSync(),
gsSPDisplayList(anime_1_txt),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, inv_mwin_nwaku_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&ctl_win1_v[4], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 2, 3, 0, 0),
gsSPEndDisplayList(),
};

Gfx ctl_win1_ue2T_model[] = {
gsDPPipeSync(),
gsSPDisplayList(anime_1_txt + 3 * sizeof(Gfx)),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, ctl_win_aw7_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&ctl_win1_v[8], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsDPPipeSync(),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, ctl_win_aw8_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&ctl_win1_v[12], 8, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
gsSP2Triangles(4, 5, 6, 0, 4, 7, 5, 0),
gsDPPipeSync(),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, ctl_win_aw6_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&ctl_win1_v[20], 8, 0),
gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
gsSP2Triangles(4, 5, 6, 0, 7, 4, 6, 0),
gsDPPipeSync(),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, ctl_win_aw5_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&ctl_win1_v[28], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
gsDPPipeSync(),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, ctl_win_aw4_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&ctl_win1_v[32], 8, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSP2Triangles(4, 5, 6, 0, 5, 7, 6, 0),
gsDPPipeSync(),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, ctl_win_aw3_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&ctl_win1_v[40], 11, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSP2Triangles(4, 5, 6, 0, 5, 7, 6, 0),
gsSP2Triangles(8, 9, 10, 0, 10, 3, 8, 0),
gsDPPipeSync(),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, ctl_win_aw2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&ctl_win1_v[51], 8, 0),
gsSP2Triangles(0, 1, 2, 0, 2, 3, 0, 0),
gsSP2Triangles(4, 5, 6, 0, 5, 7, 6, 0),
gsDPPipeSync(),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, ctl_win_aw1_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&ctl_win1_v[59], 11, 0),
gsSP2Triangles(0, 1, 2, 0, 2, 3, 0, 0),
gsSP2Triangles(4, 5, 6, 0, 5, 7, 6, 0),
gsSP2Triangles(8, 9, 10, 0, 9, 2, 10, 0),
gsSPEndDisplayList(),
};

Gfx ctl_win1_nameT_model[] = {
gsDPPipeSync(),
gsSPDisplayList(anime_1_txt + 6 * sizeof(Gfx)),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, ctl_win_waku4_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&ctl_win1_v[70], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsDPPipeSync(),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, ctl_win_waku3_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&ctl_win1_v[74], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsDPPipeSync(),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, ctl_win_waku2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&ctl_win1_v[78], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
gsDPPipeSync(),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, ctl_win_waku1_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&ctl_win1_v[82], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx ctl_win1_tagu1T_model[] = {
gsDPPipeSync(),
gsDPSetPrimColor(0, 255, 235, 205, 30, 255),
gsDPSetEnvColor(255, 215, 40, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 16, ctl_win_tagu2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&ctl_win1_v[86], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx ctl_win1_tagu2T_model[] = {
gsDPPipeSync(),
gsDPSetPrimColor(0, 255, 20, 205, 195, 255),
gsDPSetEnvColor(60, 225, 255, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 16, ctl_win_tagu2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&ctl_win1_v[90], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx ctl_win1_tagu3T_model[] = {
gsDPPipeSync(),
gsDPSetPrimColor(0, 255, 215, 80, 225, 255),
gsDPSetEnvColor(255, 110, 255, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 16, ctl_win_tagu2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&ctl_win1_v[94], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx ctl_win1_tagu4T_model[] = {
gsDPPipeSync(),
gsDPSetPrimColor(0, 255, 55, 215, 145, 255),
gsDPSetEnvColor(75, 225, 165, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 16, ctl_win_tagu2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&ctl_win1_v[98], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx ctl_win1_tagu5T_model[] = {
gsDPPipeSync(),
gsDPSetPrimColor(0, 255, 225, 125, 80, 255),
gsDPSetEnvColor(255, 155, 110, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 16, ctl_win_tagu2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&ctl_win1_v[102], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx ctl_win1_tagu6T_model[] = {
gsDPPipeSync(),
gsDPSetPrimColor(0, 255, 165, 145, 215, 255),
gsDPSetEnvColor(185, 165, 255, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 16, ctl_win_tagu2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&ctl_win1_v[106], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx ctl_win1_tagu7T_model[] = {
gsDPPipeSync(),
gsDPSetPrimColor(0, 255, 235, 105, 130, 255),
gsDPSetEnvColor(255, 125, 150, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 16, ctl_win_tagu2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&ctl_win1_v[110], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx ctl_win1_tagu8T_model[] = {
gsDPPipeSync(),
gsDPSetPrimColor(0, 255, 125, 225, 60, 255),
gsDPSetEnvColor(155, 255, 90, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 16, ctl_win_tagu2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&ctl_win1_v[114], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx ctl_win1_w1T_model[] = {
gsDPPipeSync(),
gsDPLoadTLUT_Dolphin(15, 16, 1, ctl_win_w1_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, ctl_win_w1_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&ctl_win1_v[118], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx ctl_win1_w2T_model[] = {
gsDPPipeSync(),
gsDPLoadTLUT_Dolphin(15, 16, 1, ctl_win_w2_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, ctl_win_w2_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&ctl_win1_v[122], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx ctl_win1_w3T_model[] = {
gsDPPipeSync(),
gsDPLoadTLUT_Dolphin(15, 16, 1, ctl_win_w3_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, ctl_win_w3_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&ctl_win1_v[126], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
gsSPEndDisplayList(),
};

Gfx ctl_win1_w4T_model[] = {
gsDPPipeSync(),
gsDPLoadTLUT_Dolphin(15, 16, 1, ctl_win_w6_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, ctl_win_w6_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&ctl_win1_v[130], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
gsSPEndDisplayList(),
};

Gfx ctl_win1_w5T_model[] = {
gsDPPipeSync(),
gsDPLoadTLUT_Dolphin(15, 16, 1, ctl_win_w7_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, ctl_win_w7_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&ctl_win1_v[134], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
gsSPEndDisplayList(),
};

Gfx ctl_win1_w6T_model[] = {
gsDPPipeSync(),
gsDPLoadTLUT_Dolphin(15, 16, 1, ctl_win_w6_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, ctl_win_w6_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPVertex(&ctl_win1_v[138], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
gsSPEndDisplayList(),
};

Gfx ctl_win1_w7T_model[] = {
gsDPPipeSync(),
gsDPLoadTLUT_Dolphin(15, 16, 1, ctl_win_w3_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, ctl_win_w3_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&ctl_win1_v[142], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
gsSPEndDisplayList(),
};

Gfx ctl_win1_w8T_model[] = {
gsDPPipeSync(),
gsDPLoadTLUT_Dolphin(15, 16, 1, ctl_win_w2_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, ctl_win_w2_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&ctl_win1_v[146], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
gsSPEndDisplayList(),
};

Gfx ctl_win1_w9T_model[] = {
gsDPPipeSync(),
gsDPLoadTLUT_Dolphin(15, 16, 1, ctl_win_w1_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, ctl_win_w1_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&ctl_win1_v[150], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx ctl_win1_w10T_model[] = {
gsDPPipeSync(),
gsDPLoadTLUT_Dolphin(15, 16, 1, ctl_win_w4_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, ctl_win_w4_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&ctl_win1_v[154], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
gsSPEndDisplayList(),
};

Gfx ctl_win1_w11T_model[] = {
gsDPPipeSync(),
gsDPLoadTLUT_Dolphin(15, 16, 1, ctl_win_w5_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, ctl_win_w5_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&ctl_win1_v[158], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
gsSPEndDisplayList(),
};

Gfx ctl_win1_w12T_model[] = {
gsDPPipeSync(),
gsDPLoadTLUT_Dolphin(15, 16, 1, ctl_win_w4_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, ctl_win_w4_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&ctl_win1_v[162], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
gsSPEndDisplayList(),
};

Gfx ctl_win1_kageT_model[] = {
gsDPPipeSync(),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0),
gsDPSetPrimColor(0, 255, 0, 0, 0, 20),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, ctl_win_kage3_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&ctl_win1_v[166], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsDPPipeSync(),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, ctl_win_kage2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&ctl_win1_v[170], 8, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSP2Triangles(4, 5, 6, 0, 4, 7, 5, 0),
gsDPPipeSync(),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, ctl_win_kage1_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&ctl_win1_v[178], 8, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSP2Triangles(4, 5, 6, 0, 5, 7, 6, 0),
gsSPEndDisplayList(),
};

Gfx ctl_win_mode[] = {
gsDPPipeSync(),
gsSPLoadGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE, G_AC_NONE | G_ZS_PIXEL | G_RM_PASS | G_RM_AA_TEX_EDGE2),
gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL1, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsSPEndDisplayList(),
};

Gfx ctl_tag_mode[] = {
gsDPPipeSync(),
gsSPLoadGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE, G_AC_NONE | G_ZS_PIXEL | G_RM_XLU_SURF | G_RM_XLU_SURF2),
gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0),
gsSPEndDisplayList(),
};

Gfx ctl_win_model[] = {
gsSPDisplayList(ctl_win1_w1T_model),
gsSPDisplayList(ctl_win1_w2T_model),
gsSPDisplayList(ctl_win1_w3T_model),
gsSPDisplayList(ctl_win1_w4T_model),
gsSPDisplayList(ctl_win1_w5T_model),
gsSPDisplayList(ctl_win1_w6T_model),
gsSPDisplayList(ctl_win1_w7T_model),
gsSPDisplayList(ctl_win1_w8T_model),
gsSPDisplayList(ctl_win1_w9T_model),
gsSPDisplayList(ctl_win1_w10T_model),
gsSPDisplayList(ctl_win1_w11T_model),
gsSPDisplayList(ctl_win1_w12T_model),
gsSPDisplayList(ctl_win1_w13_model),
gsDPPipeSync(),
gsDPSetCycleType(G_CYC_1CYCLE),
gsDPSetTextureLUT(G_TT_NONE),
gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0),
gsSPDisplayList(ctl_win1_ue1T_model),
gsDPPipeSync(),
gsSPDisplayList(ctl_win1_ue2T_model),
gsSPDisplayList(ctl_win1_nameT_model),
gsSPEndDisplayList(),
};

Gfx ctl_win8_color_mode[] = {
gsDPSetPrimColor(0, 255, 225, 255, 170, 255),
gsDPSetEnvColor(255, 60, 60, 255),
gsSPEndDisplayList(),
gsDPSetPrimColor(0, 255, 155, 255, 90, 255),
gsDPSetEnvColor(225, 255, 170, 255),
gsSPEndDisplayList(),
gsDPSetPrimColor(0, 255, 215, 255, 195, 255),
gsDPSetEnvColor(155, 255, 90, 255),
gsSPEndDisplayList(),
};

Gfx ctl_win7_color_mode[] = {
gsDPSetPrimColor(0, 255, 255, 190, 220, 255),
gsDPSetEnvColor(255, 60, 60, 255),
gsSPEndDisplayList(),
gsDPSetPrimColor(0, 255, 255, 125, 150, 255),
gsDPSetEnvColor(255, 190, 220, 255),
gsSPEndDisplayList(),
gsDPSetPrimColor(0, 255, 255, 195, 225, 255),
gsDPSetEnvColor(255, 125, 150, 255),
gsSPEndDisplayList(),
};

Gfx ctl_win6_color_mode[] = {
gsDPSetPrimColor(0, 255, 215, 170, 255, 255),
gsDPSetEnvColor(255, 60, 60, 255),
gsSPEndDisplayList(),
gsDPSetPrimColor(0, 255, 185, 165, 255, 255),
gsDPSetEnvColor(215, 170, 255, 255),
gsSPEndDisplayList(),
gsDPSetPrimColor(0, 255, 225, 205, 255, 255),
gsDPSetEnvColor(185, 165, 255, 255),
gsSPEndDisplayList(),
};

Gfx ctl_win5_color_mode[] = {
gsDPSetPrimColor(0, 255, 255, 205, 170, 255),
gsDPSetEnvColor(255, 60, 60, 255),
gsSPEndDisplayList(),
gsDPSetPrimColor(0, 255, 255, 155, 110, 255),
gsDPSetEnvColor(255, 205, 170, 255),
gsSPEndDisplayList(),
gsDPSetPrimColor(0, 255, 255, 215, 185, 255),
gsDPSetEnvColor(255, 155, 110, 255),
gsSPEndDisplayList(),
};

Gfx ctl_win4_color_mode[] = {
gsDPSetPrimColor(0, 255, 170, 255, 255, 255),
gsDPSetEnvColor(255, 60, 50, 255),
gsSPEndDisplayList(),
gsDPSetPrimColor(0, 255, 75, 225, 165, 255),
gsDPSetEnvColor(170, 255, 225, 255),
gsSPEndDisplayList(),
gsDPSetPrimColor(0, 255, 185, 255, 245, 255),
gsDPSetEnvColor(75, 225, 165, 255),
gsSPEndDisplayList(),
};

Gfx ctl_win3_color_mode[] = {
gsDPSetPrimColor(0, 255, 230, 170, 255, 255),
gsDPSetEnvColor(255, 60, 60, 255),
gsSPEndDisplayList(),
gsDPSetPrimColor(0, 255, 255, 110, 255, 255),
gsDPSetEnvColor(230, 170, 255, 255),
gsSPEndDisplayList(),
gsDPSetPrimColor(0, 255, 255, 185, 255, 255),
gsDPSetEnvColor(255, 110, 255, 255),
gsSPEndDisplayList(),
};

Gfx ctl_win2_color_mode[] = {
gsDPSetPrimColor(0, 255, 170, 230, 255, 255),
gsDPSetEnvColor(255, 60, 60, 255),
gsSPEndDisplayList(),
gsDPSetPrimColor(0, 255, 60, 225, 255, 255),
gsDPSetEnvColor(170, 230, 255, 255),
gsSPEndDisplayList(),
gsDPSetPrimColor(0, 255, 195, 245, 245, 255),
gsDPSetEnvColor(60, 225, 255, 255),
gsSPEndDisplayList(),
};

Gfx ctl_win1_color_mode[] = {
gsDPSetPrimColor(0, 255, 255, 255, 170, 255),
gsDPSetEnvColor(255, 60, 60, 255),
gsSPEndDisplayList(),
gsDPSetPrimColor(0, 255, 255, 215, 40, 255),
gsDPSetEnvColor(255, 255, 170, 255),
gsSPEndDisplayList(),
gsDPSetPrimColor(0, 255, 255, 255, 185, 255),
gsDPSetEnvColor(255, 215, 40, 255),
gsSPEndDisplayList(),
};


#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_ctl_win1_c(void) {
    pc_load_asset("assets/ctl_win1/inv_mwin_nwaku_tex.bin", inv_mwin_nwaku_tex, 0x400, 0x7982E0, 0, 0);
    pc_load_asset("assets/ctl_win1/ctl_win_tagu2_tex.bin", ctl_win_tagu2_tex, 0x200, 0x6CFFA0, 0, 0);
    pc_load_asset("assets/ctl_win1/ctl_win_waku1_tex.bin", ctl_win_waku1_tex, 0x800, 0x6D01A0, 0, 0);
    pc_load_asset("assets/ctl_win1/ctl_win_waku2_tex.bin", ctl_win_waku2_tex, 0x800, 0x6D09A0, 0, 0);
}
#endif

#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"


#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_honeycomb_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_honeycomb_pal[]= {
#include "assets/obj_s_honeycomb_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_s_honeycomb_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 obj_s_honeycomb_tex[]= {
#include "assets/obj_s_honeycomb_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_honeycomb_v[0x40 / sizeof(Vtx)];
#else
Vtx obj_s_honeycomb_v[] = { 
#include "assets/obj_s_honeycomb_v.inc"
};
#endif

Gfx obj_s_honeycombT_mat_model[] = { 
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, obj_s_honeycomb_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, obj_s_honeycomb_tex),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 255, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 0, G_TX_RENDERTILE, 15, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
gsSPEndDisplayList()
};

Gfx obj_s_honeycombT_gfx_model[] = { 
gsSPVertex(obj_s_honeycomb_v, 4, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
gsSPEndDisplayList()
};


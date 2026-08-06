#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 inv_mwin_2fukubiki_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 inv_mwin_2fukubiki_pal[] = {
#include "assets/inv_mwin_2fukubiki_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_3fukubiki_pal[0x20 / sizeof(u16)];
#else
u16 inv_mwin_3fukubiki_pal[] = {
#include "assets/inv_mwin_3fukubiki_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_4fukubiki_pal[0x20 / sizeof(u16)];
#else
u16 inv_mwin_4fukubiki_pal[] = {
#include "assets/inv_mwin_4fukubiki_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_5fukubiki_pal[0x20 / sizeof(u16)];
#else
u16 inv_mwin_5fukubiki_pal[] = {
#include "assets/inv_mwin_5fukubiki_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_6fukubiki_pal[0x20 / sizeof(u16)];
#else
u16 inv_mwin_6fukubiki_pal[] = {
#include "assets/inv_mwin_6fukubiki_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_1fukubiki_pal[0x20 / sizeof(u16)];
#else
u16 inv_mwin_1fukubiki_pal[] = {
#include "assets/inv_mwin_1fukubiki_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_1biki3_tex[0x200];
#else
u8 inv_mwin_1biki3_tex[] = {
#include "assets/inv_mwin_1biki3_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_1biki5_tex[0x200];
#else
u8 inv_mwin_1biki5_tex[] = {
#include "assets/inv_mwin_1biki5_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_1biki4_tex[0x200];
#else
u8 inv_mwin_1biki4_tex[] = {
#include "assets/inv_mwin_1biki4_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_1biki2_tex[0x200];
#else
u8 inv_mwin_1biki2_tex[] = {
#include "assets/inv_mwin_1biki2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_1biki1_tex[0x200];
#else
u8 inv_mwin_1biki1_tex[] = {
#include "assets/inv_mwin_1biki1_tex.inc"
};
#endif

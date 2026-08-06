#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 inv_mwin_7fukubiki_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 inv_mwin_7fukubiki_pal[] = {
#include "assets/inv_mwin_7fukubiki_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_8fukubiki_pal[0x20 / sizeof(u16)];
#else
u16 inv_mwin_8fukubiki_pal[] = {
#include "assets/inv_mwin_8fukubiki_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_9fukubiki_pal[0x20 / sizeof(u16)];
#else
u16 inv_mwin_9fukubiki_pal[] = {
#include "assets/inv_mwin_9fukubiki_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_10fukubiki_pal[0x20 / sizeof(u16)];
#else
u16 inv_mwin_10fukubiki_pal[] = {
#include "assets/inv_mwin_10fukubiki_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_11fukubiki_pal[0x20 / sizeof(u16)];
#else
u16 inv_mwin_11fukubiki_pal[] = {
#include "assets/inv_mwin_11fukubiki_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_12fukubiki_pal[0x20 / sizeof(u16)];
#else
u16 inv_mwin_12fukubiki_pal[] = {
#include "assets/inv_mwin_12fukubiki_pal.inc"
};
#endif

#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 inv_mwin_kaseki2_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 inv_mwin_kaseki2_pal[] = {
#include "assets/inv_mwin_kaseki2_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_kaseki_pal[0x20 / sizeof(u16)];
#else
u16 inv_mwin_kaseki_pal[] = {
#include "assets/inv_mwin_kaseki_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_kaseki2_tex[0x200];
#else
u8 inv_mwin_kaseki2_tex[] = {
#include "assets/inv_mwin_kaseki2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_kaseki_tex[0x200];
#else
u8 inv_mwin_kaseki_tex[] = {
#include "assets/inv_mwin_kaseki_tex.inc"
};
#endif

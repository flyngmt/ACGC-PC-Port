#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 inv_mwin_binsen1_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 inv_mwin_binsen1_pal[] = {
#include "assets/inv_mwin_binsen1_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_binsen1_tex[0x200];
#else
u8 inv_mwin_binsen1_tex[] = {
#include "assets/inv_mwin_binsen1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_binsen2_tex[0x200];
#else
u8 inv_mwin_binsen2_tex[] = {
#include "assets/inv_mwin_binsen2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_binsen3_tex[0x200];
#else
u8 inv_mwin_binsen3_tex[] = {
#include "assets/inv_mwin_binsen3_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_binsen4_tex[0x200];
#else
u8 inv_mwin_binsen4_tex[] = {
#include "assets/inv_mwin_binsen4_tex.inc"
};
#endif

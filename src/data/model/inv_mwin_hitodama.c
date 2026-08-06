#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 inv_mwin_hitodama_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 inv_mwin_hitodama_pal[] = {
#include "assets/inv_mwin_hitodama_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_hitodama1_tex[0x200];
#else
u8 inv_mwin_hitodama1_tex[] = {
#include "assets/inv_mwin_hitodama1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_hitodama2_tex[0x200];
#else
u8 inv_mwin_hitodama2_tex[] = {
#include "assets/inv_mwin_hitodama2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_hitodama3_tex[0x200];
#else
u8 inv_mwin_hitodama3_tex[] = {
#include "assets/inv_mwin_hitodama3_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_hitodama4_tex[0x200];
#else
u8 inv_mwin_hitodama4_tex[] = {
#include "assets/inv_mwin_hitodama4_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_hitodama5_tex[0x200];
#else
u8 inv_mwin_hitodama5_tex[] = {
#include "assets/inv_mwin_hitodama5_tex.inc"
};
#endif

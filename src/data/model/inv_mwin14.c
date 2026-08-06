#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 inv_mwin_utiwa_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 inv_mwin_utiwa_pal[] = {
#include "assets/inv_mwin_utiwa_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_kazaguruma_pal[0x20 / sizeof(u16)];
#else
u16 inv_mwin_kazaguruma_pal[] = {
#include "assets/inv_mwin_kazaguruma_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_fuusen_pal[0x20 / sizeof(u16)];
#else
u16 inv_mwin_fuusen_pal[] = {
#include "assets/inv_mwin_fuusen_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_utiwa_tex[0x200];
#else
u8 inv_mwin_utiwa_tex[] = {
#include "assets/inv_mwin_utiwa_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_kazaguruma_tex[0x200];
#else
u8 inv_mwin_kazaguruma_tex[] = {
#include "assets/inv_mwin_kazaguruma_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_fuusen_tex[0x200];
#else
u8 inv_mwin_fuusen_tex[] = {
#include "assets/inv_mwin_fuusen_tex.inc"
};
#endif

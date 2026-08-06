#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 inv_mwin_mtegami2_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 inv_mwin_mtegami2_pal[] = {
#include "assets/inv_mwin_mtegami2_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_mtegami_pal[0x20 / sizeof(u16)];
#else
u16 inv_mwin_mtegami_pal[] = {
#include "assets/inv_mwin_mtegami_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_otegami_pal[0x20 / sizeof(u16)];
#else
u16 inv_mwin_otegami_pal[] = {
#include "assets/inv_mwin_otegami_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_mtegami2_tex[0x200];
#else
u8 inv_mwin_mtegami2_tex[] = {
#include "assets/inv_mwin_mtegami2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_pmtegami2_tex[0x200];
#else
u8 inv_mwin_pmtegami2_tex[] = {
#include "assets/inv_mwin_pmtegami2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_mtegami_tex[0x200];
#else
u8 inv_mwin_mtegami_tex[] = {
#include "assets/inv_mwin_mtegami_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_pmtegami_tex[0x200];
#else
u8 inv_mwin_pmtegami_tex[] = {
#include "assets/inv_mwin_pmtegami_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_otegami_tex[0x200];
#else
u8 inv_mwin_otegami_tex[] = {
#include "assets/inv_mwin_otegami_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_potegami_tex[0x200];
#else
u8 inv_mwin_potegami_tex[] = {
#include "assets/inv_mwin_potegami_tex.inc"
};
#endif

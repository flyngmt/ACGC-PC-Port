#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 inv_mwin_gmushi_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 inv_mwin_gmushi_pal[] = {
#include "assets/inv_mwin_gmushi_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_gturi_pal[0x20 / sizeof(u16)];
#else
u16 inv_mwin_gturi_pal[] = {
#include "assets/inv_mwin_gturi_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_gscoop_pal[0x20 / sizeof(u16)];
#else
u16 inv_mwin_gscoop_pal[] = {
#include "assets/inv_mwin_gscoop_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_gono_pal[0x20 / sizeof(u16)];
#else
u16 inv_mwin_gono_pal[] = {
#include "assets/inv_mwin_gono_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_gmushi_tex[0x200];
#else
u8 inv_mwin_gmushi_tex[] = {
#include "assets/inv_mwin_gmushi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_gturi_tex[0x200];
#else
u8 inv_mwin_gturi_tex[] = {
#include "assets/inv_mwin_gturi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_gscoop_tex[0x200];
#else
u8 inv_mwin_gscoop_tex[] = {
#include "assets/inv_mwin_gscoop_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_gono_tex[0x200];
#else
u8 inv_mwin_gono_tex[] = {
#include "assets/inv_mwin_gono_tex.inc"
};
#endif

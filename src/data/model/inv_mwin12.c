#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 inv_mwin_ono_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 inv_mwin_ono_pal[] = {
#include "assets/inv_mwin_ono_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_scoop_pal[0x20 / sizeof(u16)];
#else
u16 inv_mwin_scoop_pal[] = {
#include "assets/inv_mwin_scoop_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_turi_tex_pal[0x20 / sizeof(u16)];
#else
u16 inv_mwin_turi_tex_pal[] = {
#include "assets/inv_mwin_turi_tex_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_mushi_pal[0x20 / sizeof(u16)];
#else
u16 inv_mwin_mushi_pal[] = {
#include "assets/inv_mwin_mushi_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_ono_tex[0x200];
#else
u8 inv_mwin_ono_tex[] = {
#include "assets/inv_mwin_ono_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_scoop_tex[0x200];
#else
u8 inv_mwin_scoop_tex[] = {
#include "assets/inv_mwin_scoop_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_turi_tex[0x200];
#else
u8 inv_mwin_turi_tex[] = {
#include "assets/inv_mwin_turi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_mushi_tex[0x200];
#else
u8 inv_mwin_mushi_tex[] = {
#include "assets/inv_mwin_mushi_tex.inc"
};
#endif

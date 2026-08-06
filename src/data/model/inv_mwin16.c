#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 inv_mwin_39ishidai_pal[0x40 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 inv_mwin_39ishidai_pal[] = {
#include "assets/inv_mwin_39ishidai_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_33zarigani_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_33zarigani_pal[] = {
#include "assets/inv_mwin_33zarigani_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_34kaeru_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_34kaeru_pal[] = {
#include "assets/inv_mwin_34kaeru_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_35medaka_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_35medaka_pal[] = {
#include "assets/inv_mwin_35medaka_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_36kurage_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_36kurage_pal[] = {
#include "assets/inv_mwin_36kurage_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_37suzuki_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_37suzuki_pal[] = {
#include "assets/inv_mwin_37suzuki_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_38tai_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_38tai_pal[] = {
#include "assets/inv_mwin_38tai_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_40piraruku_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_40piraruku_pal[] = {
#include "assets/inv_mwin_40piraruku_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_39ishidai_tex[0x200];
#else
u8 inv_mwin_39ishidai_tex[] = {
#include "assets/inv_mwin_39ishidai_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_33zarigani_tex[0x200];
#else
u8 inv_mwin_33zarigani_tex[] = {
#include "assets/inv_mwin_33zarigani_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_34kaeru_tex[0x200];
#else
u8 inv_mwin_34kaeru_tex[] = {
#include "assets/inv_mwin_34kaeru_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_35medaka_tex[0x200];
#else
u8 inv_mwin_35medaka_tex[] = {
#include "assets/inv_mwin_35medaka_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_36kurage_tex[0x200];
#else
u8 inv_mwin_36kurage_tex[] = {
#include "assets/inv_mwin_36kurage_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_37suzuki_tex[0x200];
#else
u8 inv_mwin_37suzuki_tex[] = {
#include "assets/inv_mwin_37suzuki_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_38tai_tex[0x200];
#else
u8 inv_mwin_38tai_tex[] = {
#include "assets/inv_mwin_38tai_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_40piraruku_tex[0x200];
#else
u8 inv_mwin_40piraruku_tex[] = {
#include "assets/inv_mwin_40piraruku_tex.inc"
};
#endif

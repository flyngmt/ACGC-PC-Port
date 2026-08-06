#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 inv_mwin_hiougi_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 inv_mwin_hiougi_pal[] = {
#include "assets/inv_mwin_hiougi_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_hirako_pal[0x20 / sizeof(u16)];
#else
u16 inv_mwin_hirako_pal[] = {
#include "assets/inv_mwin_hirako_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_hone_pal[0x20 / sizeof(u16)];
#else
u16 inv_mwin_hone_pal[] = {
#include "assets/inv_mwin_hone_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_hora_pal[0x20 / sizeof(u16)];
#else
u16 inv_mwin_hora_pal[] = {
#include "assets/inv_mwin_hora_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_hoshida_pal[0x20 / sizeof(u16)];
#else
u16 inv_mwin_hoshida_pal[] = {
#include "assets/inv_mwin_hoshida_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_sango_pal[0x20 / sizeof(u16)];
#else
u16 inv_mwin_sango_pal[] = {
#include "assets/inv_mwin_sango_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_syako_pal[0x20 / sizeof(u16)];
#else
u16 inv_mwin_syako_pal[] = {
#include "assets/inv_mwin_syako_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_hiougi_tex[0x200];
#else
u8 inv_mwin_hiougi_tex[] = {
#include "assets/inv_mwin_hiougi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_hirako_tex[0x200];
#else
u8 inv_mwin_hirako_tex[] = {
#include "assets/inv_mwin_hirako_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_hone_tex[0x200];
#else
u8 inv_mwin_hone_tex[] = {
#include "assets/inv_mwin_hone_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_hora_tex[0x200];
#else
u8 inv_mwin_hora_tex[] = {
#include "assets/inv_mwin_hora_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_hoshida_tex[0x200];
#else
u8 inv_mwin_hoshida_tex[] = {
#include "assets/inv_mwin_hoshida_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_sango_tex[0x200];
#else
u8 inv_mwin_sango_tex[] = {
#include "assets/inv_mwin_sango_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_syako_tex[0x200];
#else
u8 inv_mwin_syako_tex[] = {
#include "assets/inv_mwin_syako_tex.inc"
};
#endif

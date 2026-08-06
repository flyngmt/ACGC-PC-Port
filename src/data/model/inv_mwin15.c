#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 inv_mwin_39ari_pal[0x40 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 inv_mwin_39ari_pal[] = {
#include "assets/inv_mwin_39ari_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_33maimai_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_33maimai_pal[] = {
#include "assets/inv_mwin_33maimai_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_34kera_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_34kera_pal[] = {
#include "assets/inv_mwin_34kera_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_35amenbo_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_35amenbo_pal[] = {
#include "assets/inv_mwin_35amenbo_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_36mino_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_36mino_pal[] = {
#include "assets/inv_mwin_36mino_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_37dango_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_37dango_pal[] = {
#include "assets/inv_mwin_37dango_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_38kumo_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_38kumo_pal[] = {
#include "assets/inv_mwin_38kumo_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_40ka_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_40ka_pal[] = {
#include "assets/inv_mwin_40ka_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_39ari_tex[0x200];
#else
u8 inv_mwin_39ari_tex[] = {
#include "assets/inv_mwin_39ari_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_33maimai_tex[0x200];
#else
u8 inv_mwin_33maimai_tex[] = {
#include "assets/inv_mwin_33maimai_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_34kera_tex[0x200];
#else
u8 inv_mwin_34kera_tex[] = {
#include "assets/inv_mwin_34kera_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_35amenbo_tex[0x200];
#else
u8 inv_mwin_35amenbo_tex[] = {
#include "assets/inv_mwin_35amenbo_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_36mino_tex[0x200];
#else
u8 inv_mwin_36mino_tex[] = {
#include "assets/inv_mwin_36mino_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_37dango_tex[0x200];
#else
u8 inv_mwin_37dango_tex[] = {
#include "assets/inv_mwin_37dango_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_38kumo_tex[0x200];
#else
u8 inv_mwin_38kumo_tex[] = {
#include "assets/inv_mwin_38kumo_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_40ka_tex[0x200];
#else
u8 inv_mwin_40ka_tex[] = {
#include "assets/inv_mwin_40ka_tex.inc"
};
#endif

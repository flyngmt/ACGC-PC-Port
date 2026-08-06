#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 inv_mwin_leaf_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 inv_mwin_leaf_pal[] = {
#include "assets/inv_mwin_leaf_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_naegi_pal[0x20 / sizeof(u16)];
#else
u16 inv_mwin_naegi_pal[] = {
#include "assets/inv_mwin_naegi_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_seed_pal[0x20 / sizeof(u16)];
#else
u16 inv_mwin_seed_pal[] = {
#include "assets/inv_mwin_seed_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_unbrella_pal[0x20 / sizeof(u16)];
#else
u16 inv_mwin_unbrella_pal[] = {
#include "assets/inv_mwin_unbrella_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_jyuutan_pal[0x20 / sizeof(u16)];
#else
u16 inv_mwin_jyuutan_pal[] = {
#include "assets/inv_mwin_jyuutan_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_kabe2_pal[0x20 / sizeof(u16)];
#else
u16 inv_mwin_kabe2_pal[] = {
#include "assets/inv_mwin_kabe2_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_leaf_tex[0x200];
#else
u8 inv_mwin_leaf_tex[] = {
#include "assets/inv_mwin_leaf_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_naegi_tex[0x200];
#else
u8 inv_mwin_naegi_tex[] = {
#include "assets/inv_mwin_naegi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_seed_tex[0x200];
#else
u8 inv_mwin_seed_tex[] = {
#include "assets/inv_mwin_seed_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_unbrella_tex[0x200];
#else
u8 inv_mwin_unbrella_tex[] = {
#include "assets/inv_mwin_unbrella_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_jyuutan_tex[0x200];
#else
u8 inv_mwin_jyuutan_tex[] = {
#include "assets/inv_mwin_jyuutan_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_kabe_tex[0x200];
#else
u8 inv_mwin_kabe_tex[] = {
#include "assets/inv_mwin_kabe_tex.inc"
};
#endif

#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 inv_mwin_pbox1_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 inv_mwin_pbox1_tex_rgb_ci4_pal[] = {
#include "assets/inv_mwin_pbox1_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_pbox2_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 inv_mwin_pbox2_tex_rgb_ci4_pal[] = {
#include "assets/inv_mwin_pbox2_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_pbox3_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 inv_mwin_pbox3_tex_rgb_ci4_pal[] = {
#include "assets/inv_mwin_pbox3_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_pbox4_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 inv_mwin_pbox4_tex_rgb_ci4_pal[] = {
#include "assets/inv_mwin_pbox4_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_pbox5_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 inv_mwin_pbox5_tex_rgb_ci4_pal[] = {
#include "assets/inv_mwin_pbox5_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_pbox1_tex_rgb_ci4[0x200];
#else
u8 inv_mwin_pbox1_tex_rgb_ci4[] = {
#include "assets/inv_mwin_pbox1_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_pbox2_tex_rgb_ci4[0x200];
#else
u8 inv_mwin_pbox2_tex_rgb_ci4[] = {
#include "assets/inv_mwin_pbox2_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_pbox3_tex_rgb_ci4[0x200];
#else
u8 inv_mwin_pbox3_tex_rgb_ci4[] = {
#include "assets/inv_mwin_pbox3_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_pbox4_tex_rgb_ci4[0x200];
#else
u8 inv_mwin_pbox4_tex_rgb_ci4[] = {
#include "assets/inv_mwin_pbox4_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_pbox5_tex_rgb_ci4[0x200];
#else
u8 inv_mwin_pbox5_tex_rgb_ci4[] = {
#include "assets/inv_mwin_pbox5_tex_rgb_ci4.inc"
};
#endif

#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 sav_win1_nuno_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 sav_win1_nuno_tex_rgb_ci4_pal[]= {
#include "assets/sav_win1_nuno_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 sav_win2_nuno_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 sav_win2_nuno_tex_rgb_ci4_pal[]= {
#include "assets/sav_win2_nuno_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 sav_win3_nuno_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 sav_win3_nuno_tex_rgb_ci4_pal[]= {
#include "assets/sav_win3_nuno_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 sav_win4_nuno_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 sav_win4_nuno_tex_rgb_ci4_pal[]= {
#include "assets/sav_win4_nuno_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 sav_win5_nuno_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 sav_win5_nuno_tex_rgb_ci4_pal[]= {
#include "assets/sav_win5_nuno_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 sav_win6_nuno_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 sav_win6_nuno_tex_rgb_ci4_pal[]= {
#include "assets/sav_win6_nuno_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 sav_win7_nuno_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 sav_win7_nuno_tex_rgb_ci4_pal[]= {
#include "assets/sav_win7_nuno_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 sav_win8_nuno_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 sav_win8_nuno_tex_rgb_ci4_pal[]= {
#include "assets/sav_win8_nuno_tex_rgb_ci4_pal.inc"
};
#endif


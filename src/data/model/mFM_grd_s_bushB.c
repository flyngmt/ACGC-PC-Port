#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 mFM_grd_s_bushB_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) u8 mFM_grd_s_bushB_tex[] = {
#include "assets/mFM_grd_s_bushB_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 mFM_grd_s_bushB_2_tex[0x400];
#else
u8 mFM_grd_s_bushB_2_tex[] = {
#include "assets/mFM_grd_s_bushB_2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 mFM_grd_s_bushB_3_tex[0x400];
#else
u8 mFM_grd_s_bushB_3_tex[] = {
#include "assets/mFM_grd_s_bushB_3_tex.inc"
};
#endif

#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_cedar_light_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_cedar_light_pal[] = {
#include "assets/obj_cedar_light_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_cedar_leaf_tex_txt[0x800];
#else
u8 obj_w_cedar_leaf_tex_txt[] = {
#include "assets/obj_w_cedar_leaf_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_cedar_cutS_tex_txt[0x200];
#else
u8 obj_w_cedar_cutS_tex_txt[] = {
#include "assets/obj_w_cedar_cutS_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_cedar_cutL_tex_txt[0x600];
#else
u8 obj_w_cedar_cutL_tex_txt[] = {
#include "assets/obj_w_cedar_cutL_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_x_cedar_light_tex_txt[0x200];
#else
u8 obj_x_cedar_light_tex_txt[] = {
#include "assets/obj_x_cedar_light_tex_txt.inc"
};
#endif

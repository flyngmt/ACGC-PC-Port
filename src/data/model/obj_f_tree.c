#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_f_tree_leaf_tex_txt[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_f_tree_leaf_tex_txt[] = {
#include "assets/obj_f_tree_leaf_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_f_tree_cutS_tex_txt[0x200];
#else
u8 obj_f_tree_cutS_tex_txt[] = {
#include "assets/obj_f_tree_cutS_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_f_tree_cutL_tex_txt[0x600];
#else
u8 obj_f_tree_cutL_tex_txt[] = {
#include "assets/obj_f_tree_cutL_tex_txt.inc"
};
#endif

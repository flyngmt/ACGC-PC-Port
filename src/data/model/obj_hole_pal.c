#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"


#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_b_hole_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_b_hole_pal[]= {
#include "assets/obj_b_hole_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_g_hole_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_g_hole_pal[]= {
#include "assets/obj_g_hole_pal.inc"
};
#endif


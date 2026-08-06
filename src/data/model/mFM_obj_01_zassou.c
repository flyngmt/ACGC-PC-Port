#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 mFM_obj_01_zassou_pal[0x120 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 mFM_obj_01_zassou_pal[] = {
#include "assets/mFM_obj_01_zassou_pal.inc"
};
#endif

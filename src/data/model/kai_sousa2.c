#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 testbutton[0x80];
#else
ATTRIBUTE_ALIGN(32) u8 testbutton[] = {
#include "assets/testbutton.inc"
};
#endif

#ifdef TARGET_PC
Vtx kai_sousa2_v[0xA00 / sizeof(Vtx)];
#else
Vtx kai_sousa2_v[] = {
#include "assets/kai_sousa2_v.inc"
};
#endif

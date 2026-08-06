#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 inv_mwin_video_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 inv_mwin_video_pal[] = {
#include "assets/inv_mwin_video_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_camera2_pal[0x20 / sizeof(u16)];
#else
u16 inv_mwin_camera2_pal[] = {
#include "assets/inv_mwin_camera2_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_GB_pal[0x20 / sizeof(u16)];
#else
u16 inv_mwin_GB_pal[] = {
#include "assets/inv_mwin_GB_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_hankati_pal[0x20 / sizeof(u16)];
#else
u16 inv_mwin_hankati_pal[] = {
#include "assets/inv_mwin_hankati_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_ehon_pal[0x20 / sizeof(u16)];
#else
u16 inv_mwin_ehon_pal[] = {
#include "assets/inv_mwin_ehon_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_manga_pal[0x20 / sizeof(u16)];
#else
u16 inv_mwin_manga_pal[] = {
#include "assets/inv_mwin_manga_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_glasses_pal[0x20 / sizeof(u16)];
#else
u16 inv_mwin_glasses_pal[] = {
#include "assets/inv_mwin_glasses_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_pokepi_pal[0x20 / sizeof(u16)];
#else
u16 inv_mwin_pokepi_pal[] = {
#include "assets/inv_mwin_pokepi_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_tetyou_pal[0x20 / sizeof(u16)];
#else
u16 inv_mwin_tetyou_pal[] = {
#include "assets/inv_mwin_tetyou_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_tokei_pal[0x20 / sizeof(u16)];
#else
u16 inv_mwin_tokei_pal[] = {
#include "assets/inv_mwin_tokei_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_video_tex[0x200];
#else
u8 inv_mwin_video_tex[] = {
#include "assets/inv_mwin_video_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_camera_tex[0x200];
#else
u8 inv_mwin_camera_tex[] = {
#include "assets/inv_mwin_camera_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_GB_tex[0x200];
#else
u8 inv_mwin_GB_tex[] = {
#include "assets/inv_mwin_GB_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_hankati_tex[0x200];
#else
u8 inv_mwin_hankati_tex[] = {
#include "assets/inv_mwin_hankati_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_ehon_tex[0x200];
#else
u8 inv_mwin_ehon_tex[] = {
#include "assets/inv_mwin_ehon_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_manga_tex[0x200];
#else
u8 inv_mwin_manga_tex[] = {
#include "assets/inv_mwin_manga_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_glasses_tex[0x200];
#else
u8 inv_mwin_glasses_tex[] = {
#include "assets/inv_mwin_glasses_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_pokepi_tex[0x200];
#else
u8 inv_mwin_pokepi_tex[] = {
#include "assets/inv_mwin_pokepi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_tetyou_tex[0x200];
#else
u8 inv_mwin_tetyou_tex[] = {
#include "assets/inv_mwin_tetyou_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_tokei_tex[0x200];
#else
u8 inv_mwin_tokei_tex[] = {
#include "assets/inv_mwin_tokei_tex.inc"
};
#endif

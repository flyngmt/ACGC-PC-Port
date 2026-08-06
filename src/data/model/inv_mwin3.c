#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 inv_mwin_08oonamazu_pal[0x40 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 inv_mwin_08oonamazu_pal[] = {
#include "assets/inv_mwin_08oonamazu_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_01funa_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_01funa_pal[] = {
#include "assets/inv_mwin_01funa_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_02masu_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_02masu_pal[] = {
#include "assets/inv_mwin_02masu_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_03koi_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_03koi_pal[] = {
#include "assets/inv_mwin_03koi_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_04nishiki_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_04nishiki_pal[] = {
#include "assets/inv_mwin_04nishiki_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_05nigoi_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_05nigoi_pal[] = {
#include "assets/inv_mwin_05nigoi_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_06ugui_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_06ugui_pal[] = {
#include "assets/inv_mwin_06ugui_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_07namazu_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_07namazu_pal[] = {
#include "assets/inv_mwin_07namazu_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_09oikawa_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_09oikawa_pal[] = {
#include "assets/inv_mwin_09oikawa_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_10tanago_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_10tanago_pal[] = {
#include "assets/inv_mwin_10tanago_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_11dojyou_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_11dojyou_pal[] = {
#include "assets/inv_mwin_11dojyou_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_12gill_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_12gill_pal[] = {
#include "assets/inv_mwin_12gill_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_13bass_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_13bass_pal[] = {
#include "assets/inv_mwin_13bass_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_14bassm_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_14bassm_pal[] = {
#include "assets/inv_mwin_14bassm_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_15bassl_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_15bassl_pal[] = {
#include "assets/inv_mwin_15bassl_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_16raigyo_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_16raigyo_pal[] = {
#include "assets/inv_mwin_16raigyo_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_17unagi_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_17unagi_pal[] = {
#include "assets/inv_mwin_17unagi_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_18donko_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_18donko_pal[] = {
#include "assets/inv_mwin_18donko_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_19wakasagi_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_19wakasagi_pal[] = {
#include "assets/inv_mwin_19wakasagi_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_20ayu_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_20ayu_pal[] = {
#include "assets/inv_mwin_20ayu_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_21yamame_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_21yamame_pal[] = {
#include "assets/inv_mwin_21yamame_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_22niji_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_22niji_pal[] = {
#include "assets/inv_mwin_22niji_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_23iwana_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_23iwana_pal[] = {
#include "assets/inv_mwin_23iwana_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_24itou_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_24itou_pal[] = {
#include "assets/inv_mwin_24itou_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_25sake_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_25sake_pal[] = {
#include "assets/inv_mwin_25sake_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_26kingyo_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_26kingyo_pal[] = {
#include "assets/inv_mwin_26kingyo_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_27demekin_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_27demekin_pal[] = {
#include "assets/inv_mwin_27demekin_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_28gupi_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_28gupi_pal[] = {
#include "assets/inv_mwin_28gupi_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_29angel_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_29angel_pal[] = {
#include "assets/inv_mwin_29angel_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_30pirania_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_30pirania_pal[] = {
#include "assets/inv_mwin_30pirania_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_31aroana_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_31aroana_pal[] = {
#include "assets/inv_mwin_31aroana_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_32kaseki_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_32kaseki_pal[] = {
#include "assets/inv_mwin_32kaseki_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_08oonamazu_tex[0x200];
#else
u8 inv_mwin_08oonamazu_tex[] = {
#include "assets/inv_mwin_08oonamazu_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_01funa_tex[0x200];
#else
u8 inv_mwin_01funa_tex[] = {
#include "assets/inv_mwin_01funa_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_02masu_tex[0x200];
#else
u8 inv_mwin_02masu_tex[] = {
#include "assets/inv_mwin_02masu_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_03koi_tex[0x200];
#else
u8 inv_mwin_03koi_tex[] = {
#include "assets/inv_mwin_03koi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_04nishiki_tex[0x200];
#else
u8 inv_mwin_04nishiki_tex[] = {
#include "assets/inv_mwin_04nishiki_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_05nigoi_tex[0x200];
#else
u8 inv_mwin_05nigoi_tex[] = {
#include "assets/inv_mwin_05nigoi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_06ugui_tex[0x200];
#else
u8 inv_mwin_06ugui_tex[] = {
#include "assets/inv_mwin_06ugui_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_07namazu_tex[0x200];
#else
u8 inv_mwin_07namazu_tex[] = {
#include "assets/inv_mwin_07namazu_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_09oikawa_tex[0x200];
#else
u8 inv_mwin_09oikawa_tex[] = {
#include "assets/inv_mwin_09oikawa_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_10tanago_tex[0x200];
#else
u8 inv_mwin_10tanago_tex[] = {
#include "assets/inv_mwin_10tanago_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_11dojyou_tex[0x200];
#else
u8 inv_mwin_11dojyou_tex[] = {
#include "assets/inv_mwin_11dojyou_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_12gill_tex[0x200];
#else
u8 inv_mwin_12gill_tex[] = {
#include "assets/inv_mwin_12gill_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_13bass_tex[0x200];
#else
u8 inv_mwin_13bass_tex[] = {
#include "assets/inv_mwin_13bass_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_14bassm_tex[0x200];
#else
u8 inv_mwin_14bassm_tex[] = {
#include "assets/inv_mwin_14bassm_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_15bassl_tex[0x200];
#else
u8 inv_mwin_15bassl_tex[] = {
#include "assets/inv_mwin_15bassl_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_16raigyo_tex[0x200];
#else
u8 inv_mwin_16raigyo_tex[] = {
#include "assets/inv_mwin_16raigyo_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_17unagi_tex[0x200];
#else
u8 inv_mwin_17unagi_tex[] = {
#include "assets/inv_mwin_17unagi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_18donko_tex[0x200];
#else
u8 inv_mwin_18donko_tex[] = {
#include "assets/inv_mwin_18donko_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_19wakasagi_tex[0x200];
#else
u8 inv_mwin_19wakasagi_tex[] = {
#include "assets/inv_mwin_19wakasagi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_20ayu_tex[0x200];
#else
u8 inv_mwin_20ayu_tex[] = {
#include "assets/inv_mwin_20ayu_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_21yamame_tex[0x200];
#else
u8 inv_mwin_21yamame_tex[] = {
#include "assets/inv_mwin_21yamame_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_22niji_tex[0x200];
#else
u8 inv_mwin_22niji_tex[] = {
#include "assets/inv_mwin_22niji_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_23iwana_tex[0x200];
#else
u8 inv_mwin_23iwana_tex[] = {
#include "assets/inv_mwin_23iwana_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_24itou_tex[0x200];
#else
u8 inv_mwin_24itou_tex[] = {
#include "assets/inv_mwin_24itou_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_25sake_tex[0x200];
#else
u8 inv_mwin_25sake_tex[] = {
#include "assets/inv_mwin_25sake_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_26kingyo_tex[0x200];
#else
u8 inv_mwin_26kingyo_tex[] = {
#include "assets/inv_mwin_26kingyo_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_27demekin_tex[0x200];
#else
u8 inv_mwin_27demekin_tex[] = {
#include "assets/inv_mwin_27demekin_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_28gupi_tex[0x200];
#else
u8 inv_mwin_28gupi_tex[] = {
#include "assets/inv_mwin_28gupi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_29angel_tex[0x200];
#else
u8 inv_mwin_29angel_tex[] = {
#include "assets/inv_mwin_29angel_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_30pirania_tex[0x200];
#else
u8 inv_mwin_30pirania_tex[] = {
#include "assets/inv_mwin_30pirania_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_31aroana_tex[0x200];
#else
u8 inv_mwin_31aroana_tex[] = {
#include "assets/inv_mwin_31aroana_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_32kaseki_tex[0x200];
#else
u8 inv_mwin_32kaseki_tex[] = {
#include "assets/inv_mwin_32kaseki_tex.inc"
};
#endif

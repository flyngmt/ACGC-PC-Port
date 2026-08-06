#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 inv_mwin_01monshiro_pal[0x40 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 inv_mwin_01monshiro_pal[] = {
#include "assets/inv_mwin_01monshiro_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_02monki_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_02monki_pal[] = {
#include "assets/inv_mwin_02monki_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_03kiageha_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_03kiageha_pal[] = {
#include "assets/inv_mwin_03kiageha_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_04ohmurasaki_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_04ohmurasaki_pal[] = {
#include "assets/inv_mwin_04ohmurasaki_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_05abura_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_05abura_pal[] = {
#include "assets/inv_mwin_05abura_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_06minmin_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_06minmin_pal[] = {
#include "assets/inv_mwin_06minmin_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_07tukutuku_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_07tukutuku_pal[] = {
#include "assets/inv_mwin_07tukutuku_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_08higurashi_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_08higurashi_pal[] = {
#include "assets/inv_mwin_08higurashi_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_09akiakane_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_09akiakane_pal[] = {
#include "assets/inv_mwin_09akiakane_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_10shiokara_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_10shiokara_pal[] = {
#include "assets/inv_mwin_10shiokara_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_11ginyanma_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_11ginyanma_pal[] = {
#include "assets/inv_mwin_11ginyanma_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_12oniyanma_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_12oniyanma_pal[] = {
#include "assets/inv_mwin_12oniyanma_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_13koorogi_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_13koorogi_pal[] = {
#include "assets/inv_mwin_13koorogi_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_14kirigirisu_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_14kirigirisu_pal[] = {
#include "assets/inv_mwin_14kirigirisu_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_15matumushi_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_15matumushi_pal[] = {
#include "assets/inv_mwin_15matumushi_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_16suzumushi_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_16suzumushi_pal[] = {
#include "assets/inv_mwin_16suzumushi_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_17tentou_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_17tentou_pal[] = {
#include "assets/inv_mwin_17tentou_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_18nanahoshi_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_18nanahoshi_pal[] = {
#include "assets/inv_mwin_18nanahoshi_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_19kamakiri_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_19kamakiri_pal[] = {
#include "assets/inv_mwin_19kamakiri_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_20syouryou_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_20syouryou_pal[] = {
#include "assets/inv_mwin_20syouryou_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_21tonosama_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_21tonosama_pal[] = {
#include "assets/inv_mwin_21tonosama_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_22danna_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_22danna_pal[] = {
#include "assets/inv_mwin_22danna_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_23hati_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_23hati_pal[] = {
#include "assets/inv_mwin_23hati_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_24genji_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_24genji_pal[] = {
#include "assets/inv_mwin_24genji_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_25kanabun_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_25kanabun_pal[] = {
#include "assets/inv_mwin_25kanabun_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_26gomadara_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_26gomadara_pal[] = {
#include "assets/inv_mwin_26gomadara_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_27tamamushi_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_27tamamushi_pal[] = {
#include "assets/inv_mwin_27tamamushi_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_28kabuto_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_28kabuto_pal[] = {
#include "assets/inv_mwin_28kabuto_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_29hirata_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_29hirata_pal[] = {
#include "assets/inv_mwin_29hirata_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_30nokogiri_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_30nokogiri_pal[] = {
#include "assets/inv_mwin_30nokogiri_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_31miyama_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_31miyama_pal[] = {
#include "assets/inv_mwin_31miyama_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_mwin_32okuwa_pal[0x40 / sizeof(u16)];
#else
u16 inv_mwin_32okuwa_pal[] = {
#include "assets/inv_mwin_32okuwa_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_01monshiro_tex[0x200];
#else
u8 inv_mwin_01monshiro_tex[] = {
#include "assets/inv_mwin_01monshiro_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_02monki_tex[0x200];
#else
u8 inv_mwin_02monki_tex[] = {
#include "assets/inv_mwin_02monki_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_03kiageha_tex[0x200];
#else
u8 inv_mwin_03kiageha_tex[] = {
#include "assets/inv_mwin_03kiageha_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_04ohmurasaki_tex[0x200];
#else
u8 inv_mwin_04ohmurasaki_tex[] = {
#include "assets/inv_mwin_04ohmurasaki_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_05abura_tex[0x200];
#else
u8 inv_mwin_05abura_tex[] = {
#include "assets/inv_mwin_05abura_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_06minmin_tex[0x200];
#else
u8 inv_mwin_06minmin_tex[] = {
#include "assets/inv_mwin_06minmin_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_07tukutuku_tex[0x200];
#else
u8 inv_mwin_07tukutuku_tex[] = {
#include "assets/inv_mwin_07tukutuku_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_08higurashi_tex[0x200];
#else
u8 inv_mwin_08higurashi_tex[] = {
#include "assets/inv_mwin_08higurashi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_09akiakane_tex[0x200];
#else
u8 inv_mwin_09akiakane_tex[] = {
#include "assets/inv_mwin_09akiakane_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_10shiokara_tex[0x200];
#else
u8 inv_mwin_10shiokara_tex[] = {
#include "assets/inv_mwin_10shiokara_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_11ginyanma_tex[0x200];
#else
u8 inv_mwin_11ginyanma_tex[] = {
#include "assets/inv_mwin_11ginyanma_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_12oniyanma_tex[0x200];
#else
u8 inv_mwin_12oniyanma_tex[] = {
#include "assets/inv_mwin_12oniyanma_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_13koorogi_tex[0x200];
#else
u8 inv_mwin_13koorogi_tex[] = {
#include "assets/inv_mwin_13koorogi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_14kirigirisu_tex[0x200];
#else
u8 inv_mwin_14kirigirisu_tex[] = {
#include "assets/inv_mwin_14kirigirisu_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_15matumushi_tex[0x200];
#else
u8 inv_mwin_15matumushi_tex[] = {
#include "assets/inv_mwin_15matumushi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_16suzumushi_tex[0x200];
#else
u8 inv_mwin_16suzumushi_tex[] = {
#include "assets/inv_mwin_16suzumushi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_17tentou_tex[0x200];
#else
u8 inv_mwin_17tentou_tex[] = {
#include "assets/inv_mwin_17tentou_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_18nanahoshi_tex[0x200];
#else
u8 inv_mwin_18nanahoshi_tex[] = {
#include "assets/inv_mwin_18nanahoshi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_19kamakiri_tex[0x200];
#else
u8 inv_mwin_19kamakiri_tex[] = {
#include "assets/inv_mwin_19kamakiri_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_20syouryou_tex[0x200];
#else
u8 inv_mwin_20syouryou_tex[] = {
#include "assets/inv_mwin_20syouryou_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_21tonosama_tex[0x200];
#else
u8 inv_mwin_21tonosama_tex[] = {
#include "assets/inv_mwin_21tonosama_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_22danna_tex[0x200];
#else
u8 inv_mwin_22danna_tex[] = {
#include "assets/inv_mwin_22danna_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_23hati_tex[0x200];
#else
u8 inv_mwin_23hati_tex[] = {
#include "assets/inv_mwin_23hati_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_24genji_tex[0x200];
#else
u8 inv_mwin_24genji_tex[] = {
#include "assets/inv_mwin_24genji_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_25kanabun_tex[0x200];
#else
u8 inv_mwin_25kanabun_tex[] = {
#include "assets/inv_mwin_25kanabun_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_26gomadara_tex[0x200];
#else
u8 inv_mwin_26gomadara_tex[] = {
#include "assets/inv_mwin_26gomadara_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_27tamamushi_tex[0x200];
#else
u8 inv_mwin_27tamamushi_tex[] = {
#include "assets/inv_mwin_27tamamushi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_28kabuto_tex[0x200];
#else
u8 inv_mwin_28kabuto_tex[] = {
#include "assets/inv_mwin_28kabuto_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_29hirata_tex[0x200];
#else
u8 inv_mwin_29hirata_tex[] = {
#include "assets/inv_mwin_29hirata_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_30nokogiri_tex[0x200];
#else
u8 inv_mwin_30nokogiri_tex[] = {
#include "assets/inv_mwin_30nokogiri_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_31miyama_tex[0x200];
#else
u8 inv_mwin_31miyama_tex[] = {
#include "assets/inv_mwin_31miyama_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_mwin_32okuwa_tex[0x200];
#else
u8 inv_mwin_32okuwa_tex[] = {
#include "assets/inv_mwin_32okuwa_tex.inc"
};
#endif

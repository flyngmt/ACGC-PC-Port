#include <dolphin/types.h>

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned short kgr_5_pal[0x20 / sizeof(unsigned short)];
#else
ATTRIBUTE_ALIGN(32) extern unsigned short kgr_5_pal[] = {
#include "assets/npc/tex/kgr_5_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char kgr_5_eye1_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char kgr_5_eye1_TA_tex_txt[] = {
#include "assets/npc/tex/kgr_5_eye1_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char kgr_5_eye2_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char kgr_5_eye2_TA_tex_txt[] = {
#include "assets/npc/tex/kgr_5_eye2_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char kgr_5_eye3_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char kgr_5_eye3_TA_tex_txt[] = {
#include "assets/npc/tex/kgr_5_eye3_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char kgr_5_eye4_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char kgr_5_eye4_TA_tex_txt[] = {
#include "assets/npc/tex/kgr_5_eye4_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char kgr_5_eye5_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char kgr_5_eye5_TA_tex_txt[] = {
#include "assets/npc/tex/kgr_5_eye5_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char kgr_5_eye6_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char kgr_5_eye6_TA_tex_txt[] = {
#include "assets/npc/tex/kgr_5_eye6_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char kgr_5_eye7_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char kgr_5_eye7_TA_tex_txt[] = {
#include "assets/npc/tex/kgr_5_eye7_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char kgr_5_eye8_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char kgr_5_eye8_TA_tex_txt[] = {
#include "assets/npc/tex/kgr_5_eye8_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char kgr_5_tmem_txt[0x440];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char kgr_5_tmem_txt[] = {
#include "assets/npc/tex/kgr_5_tmem_txt.inc"
};
#endif


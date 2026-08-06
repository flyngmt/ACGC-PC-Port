#include <dolphin/types.h>

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned short pig_9_pal[0x20 / sizeof(unsigned short)];
#else
ATTRIBUTE_ALIGN(32) extern unsigned short pig_9_pal[] = {
#include "assets/npc/tex/pig_9_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char pig_9_eye1_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char pig_9_eye1_TA_tex_txt[] = {
#include "assets/npc/tex/pig_9_eye1_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char pig_9_eye2_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char pig_9_eye2_TA_tex_txt[] = {
#include "assets/npc/tex/pig_9_eye2_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char pig_9_eye3_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char pig_9_eye3_TA_tex_txt[] = {
#include "assets/npc/tex/pig_9_eye3_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char pig_9_eye4_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char pig_9_eye4_TA_tex_txt[] = {
#include "assets/npc/tex/pig_9_eye4_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char pig_9_eye5_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char pig_9_eye5_TA_tex_txt[] = {
#include "assets/npc/tex/pig_9_eye5_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char pig_9_eye6_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char pig_9_eye6_TA_tex_txt[] = {
#include "assets/npc/tex/pig_9_eye6_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char pig_9_eye7_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char pig_9_eye7_TA_tex_txt[] = {
#include "assets/npc/tex/pig_9_eye7_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char pig_9_eye8_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char pig_9_eye8_TA_tex_txt[] = {
#include "assets/npc/tex/pig_9_eye8_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char pig_9_mouth1_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char pig_9_mouth1_TA_tex_txt[] = {
#include "assets/npc/tex/pig_9_mouth1_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char pig_9_mouth2_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char pig_9_mouth2_TA_tex_txt[] = {
#include "assets/npc/tex/pig_9_mouth2_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char pig_9_mouth3_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char pig_9_mouth3_TA_tex_txt[] = {
#include "assets/npc/tex/pig_9_mouth3_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char pig_9_mouth4_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char pig_9_mouth4_TA_tex_txt[] = {
#include "assets/npc/tex/pig_9_mouth4_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char pig_9_mouth5_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char pig_9_mouth5_TA_tex_txt[] = {
#include "assets/npc/tex/pig_9_mouth5_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char pig_9_mouth6_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char pig_9_mouth6_TA_tex_txt[] = {
#include "assets/npc/tex/pig_9_mouth6_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char pig_9_tmem_txt[0x380];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char pig_9_tmem_txt[] = {
#include "assets/npc/tex/pig_9_tmem_txt.inc"
};
#endif


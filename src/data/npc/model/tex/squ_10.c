#include <dolphin/types.h>

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned short squ_10_pal[0x20 / sizeof(unsigned short)];
#else
ATTRIBUTE_ALIGN(32) extern unsigned short squ_10_pal[] = {
#include "assets/npc/tex/squ_10_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char squ_10_eye1_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char squ_10_eye1_TA_tex_txt[] = {
#include "assets/npc/tex/squ_10_eye1_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char squ_10_eye2_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char squ_10_eye2_TA_tex_txt[] = {
#include "assets/npc/tex/squ_10_eye2_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char squ_10_eye3_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char squ_10_eye3_TA_tex_txt[] = {
#include "assets/npc/tex/squ_10_eye3_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char squ_10_eye4_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char squ_10_eye4_TA_tex_txt[] = {
#include "assets/npc/tex/squ_10_eye4_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char squ_10_eye5_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char squ_10_eye5_TA_tex_txt[] = {
#include "assets/npc/tex/squ_10_eye5_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char squ_10_eye6_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char squ_10_eye6_TA_tex_txt[] = {
#include "assets/npc/tex/squ_10_eye6_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char squ_10_eye7_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char squ_10_eye7_TA_tex_txt[] = {
#include "assets/npc/tex/squ_10_eye7_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char squ_10_eye8_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char squ_10_eye8_TA_tex_txt[] = {
#include "assets/npc/tex/squ_10_eye8_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char squ_10_mouth1_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char squ_10_mouth1_TA_tex_txt[] = {
#include "assets/npc/tex/squ_10_mouth1_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char squ_10_mouth2_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char squ_10_mouth2_TA_tex_txt[] = {
#include "assets/npc/tex/squ_10_mouth2_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char squ_10_mouth3_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char squ_10_mouth3_TA_tex_txt[] = {
#include "assets/npc/tex/squ_10_mouth3_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char squ_10_mouth4_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char squ_10_mouth4_TA_tex_txt[] = {
#include "assets/npc/tex/squ_10_mouth4_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char squ_10_mouth5_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char squ_10_mouth5_TA_tex_txt[] = {
#include "assets/npc/tex/squ_10_mouth5_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char squ_10_mouth6_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char squ_10_mouth6_TA_tex_txt[] = {
#include "assets/npc/tex/squ_10_mouth6_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char squ_10_tmem_txt[0x400];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char squ_10_tmem_txt[] = {
#include "assets/npc/tex/squ_10_tmem_txt.inc"
};
#endif


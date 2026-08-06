#include <dolphin/types.h>

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned short cat_14_pal[0x20 / sizeof(unsigned short)];
#else
ATTRIBUTE_ALIGN(32) extern unsigned short cat_14_pal[] = {
#include "assets/npc/tex/cat_14_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char cat_14_eye1_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char cat_14_eye1_TA_tex_txt[] = {
#include "assets/npc/tex/cat_14_eye1_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char cat_14_eye2_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char cat_14_eye2_TA_tex_txt[] = {
#include "assets/npc/tex/cat_14_eye2_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char cat_14_eye3_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char cat_14_eye3_TA_tex_txt[] = {
#include "assets/npc/tex/cat_14_eye3_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char cat_14_eye4_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char cat_14_eye4_TA_tex_txt[] = {
#include "assets/npc/tex/cat_14_eye4_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char cat_14_eye5_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char cat_14_eye5_TA_tex_txt[] = {
#include "assets/npc/tex/cat_14_eye5_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char cat_14_eye6_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char cat_14_eye6_TA_tex_txt[] = {
#include "assets/npc/tex/cat_14_eye6_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char cat_14_eye7_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char cat_14_eye7_TA_tex_txt[] = {
#include "assets/npc/tex/cat_14_eye7_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char cat_14_eye8_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char cat_14_eye8_TA_tex_txt[] = {
#include "assets/npc/tex/cat_14_eye8_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char cat_14_mouth1_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char cat_14_mouth1_TA_tex_txt[] = {
#include "assets/npc/tex/cat_14_mouth1_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char cat_14_mouth2_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char cat_14_mouth2_TA_tex_txt[] = {
#include "assets/npc/tex/cat_14_mouth2_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char cat_14_mouth3_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char cat_14_mouth3_TA_tex_txt[] = {
#include "assets/npc/tex/cat_14_mouth3_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char cat_14_mouth4_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char cat_14_mouth4_TA_tex_txt[] = {
#include "assets/npc/tex/cat_14_mouth4_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char cat_14_mouth5_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char cat_14_mouth5_TA_tex_txt[] = {
#include "assets/npc/tex/cat_14_mouth5_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char cat_14_mouth6_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char cat_14_mouth6_TA_tex_txt[] = {
#include "assets/npc/tex/cat_14_mouth6_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char cat_14_tmem_txt[0x400];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char cat_14_tmem_txt[] = {
#include "assets/npc/tex/cat_14_tmem_txt.inc"
};
#endif


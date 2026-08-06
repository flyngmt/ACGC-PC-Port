#include <dolphin/types.h>

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned short cow_2_pal[0x20 / sizeof(unsigned short)];
#else
ATTRIBUTE_ALIGN(32) extern unsigned short cow_2_pal[] = {
#include "assets/npc/tex/cow_2_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char cow_2_eye1_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char cow_2_eye1_TA_tex_txt[] = {
#include "assets/npc/tex/cow_2_eye1_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char cow_2_eye2_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char cow_2_eye2_TA_tex_txt[] = {
#include "assets/npc/tex/cow_2_eye2_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char cow_2_eye3_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char cow_2_eye3_TA_tex_txt[] = {
#include "assets/npc/tex/cow_2_eye3_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char cow_2_eye4_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char cow_2_eye4_TA_tex_txt[] = {
#include "assets/npc/tex/cow_2_eye4_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char cow_2_eye5_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char cow_2_eye5_TA_tex_txt[] = {
#include "assets/npc/tex/cow_2_eye5_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char cow_2_eye6_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char cow_2_eye6_TA_tex_txt[] = {
#include "assets/npc/tex/cow_2_eye6_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char cow_2_eye7_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char cow_2_eye7_TA_tex_txt[] = {
#include "assets/npc/tex/cow_2_eye7_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char cow_2_eye8_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char cow_2_eye8_TA_tex_txt[] = {
#include "assets/npc/tex/cow_2_eye8_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char cow_2_mouth1_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char cow_2_mouth1_TA_tex_txt[] = {
#include "assets/npc/tex/cow_2_mouth1_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char cow_2_mouth2_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char cow_2_mouth2_TA_tex_txt[] = {
#include "assets/npc/tex/cow_2_mouth2_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char cow_2_mouth3_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char cow_2_mouth3_TA_tex_txt[] = {
#include "assets/npc/tex/cow_2_mouth3_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char cow_2_mouth4_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char cow_2_mouth4_TA_tex_txt[] = {
#include "assets/npc/tex/cow_2_mouth4_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char cow_2_mouth5_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char cow_2_mouth5_TA_tex_txt[] = {
#include "assets/npc/tex/cow_2_mouth5_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char cow_2_mouth6_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char cow_2_mouth6_TA_tex_txt[] = {
#include "assets/npc/tex/cow_2_mouth6_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char cow_2_tmem_txt[0x400];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char cow_2_tmem_txt[] = {
#include "assets/npc/tex/cow_2_tmem_txt.inc"
};
#endif


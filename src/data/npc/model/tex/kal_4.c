#include <dolphin/types.h>

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned short kal_4_pal[0x20 / sizeof(unsigned short)];
#else
ATTRIBUTE_ALIGN(32) extern unsigned short kal_4_pal[] = {
#include "assets/npc/tex/kal_4_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char kal_4_eye1_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char kal_4_eye1_TA_tex_txt[] = {
#include "assets/npc/tex/kal_4_eye1_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char kal_4_eye2_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char kal_4_eye2_TA_tex_txt[] = {
#include "assets/npc/tex/kal_4_eye2_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char kal_4_eye3_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char kal_4_eye3_TA_tex_txt[] = {
#include "assets/npc/tex/kal_4_eye3_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char kal_4_eye4_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char kal_4_eye4_TA_tex_txt[] = {
#include "assets/npc/tex/kal_4_eye4_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char kal_4_eye5_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char kal_4_eye5_TA_tex_txt[] = {
#include "assets/npc/tex/kal_4_eye5_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char kal_4_eye6_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char kal_4_eye6_TA_tex_txt[] = {
#include "assets/npc/tex/kal_4_eye6_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char kal_4_eye7_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char kal_4_eye7_TA_tex_txt[] = {
#include "assets/npc/tex/kal_4_eye7_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char kal_4_eye8_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char kal_4_eye8_TA_tex_txt[] = {
#include "assets/npc/tex/kal_4_eye8_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char kal_4_mouth1_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char kal_4_mouth1_TA_tex_txt[] = {
#include "assets/npc/tex/kal_4_mouth1_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char kal_4_mouth2_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char kal_4_mouth2_TA_tex_txt[] = {
#include "assets/npc/tex/kal_4_mouth2_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char kal_4_mouth3_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char kal_4_mouth3_TA_tex_txt[] = {
#include "assets/npc/tex/kal_4_mouth3_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char kal_4_mouth4_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char kal_4_mouth4_TA_tex_txt[] = {
#include "assets/npc/tex/kal_4_mouth4_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char kal_4_mouth5_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char kal_4_mouth5_TA_tex_txt[] = {
#include "assets/npc/tex/kal_4_mouth5_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char kal_4_mouth6_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char kal_4_mouth6_TA_tex_txt[] = {
#include "assets/npc/tex/kal_4_mouth6_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char kal_4_tmem_txt[0x480];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char kal_4_tmem_txt[] = {
#include "assets/npc/tex/kal_4_tmem_txt.inc"
};
#endif


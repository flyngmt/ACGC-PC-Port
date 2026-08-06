#include <dolphin/types.h>

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned short mus_6_pal[0x20 / sizeof(unsigned short)];
#else
ATTRIBUTE_ALIGN(32) extern unsigned short mus_6_pal[] = {
#include "assets/npc/tex/mus_6_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char mus_6_eye1_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char mus_6_eye1_TA_tex_txt[] = {
#include "assets/npc/tex/mus_6_eye1_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char mus_6_eye2_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char mus_6_eye2_TA_tex_txt[] = {
#include "assets/npc/tex/mus_6_eye2_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char mus_6_eye3_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char mus_6_eye3_TA_tex_txt[] = {
#include "assets/npc/tex/mus_6_eye3_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char mus_6_eye4_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char mus_6_eye4_TA_tex_txt[] = {
#include "assets/npc/tex/mus_6_eye4_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char mus_6_eye5_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char mus_6_eye5_TA_tex_txt[] = {
#include "assets/npc/tex/mus_6_eye5_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char mus_6_eye6_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char mus_6_eye6_TA_tex_txt[] = {
#include "assets/npc/tex/mus_6_eye6_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char mus_6_eye7_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char mus_6_eye7_TA_tex_txt[] = {
#include "assets/npc/tex/mus_6_eye7_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char mus_6_eye8_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char mus_6_eye8_TA_tex_txt[] = {
#include "assets/npc/tex/mus_6_eye8_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char mus_6_mouth1_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char mus_6_mouth1_TA_tex_txt[] = {
#include "assets/npc/tex/mus_6_mouth1_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char mus_6_mouth2_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char mus_6_mouth2_TA_tex_txt[] = {
#include "assets/npc/tex/mus_6_mouth2_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char mus_6_mouth3_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char mus_6_mouth3_TA_tex_txt[] = {
#include "assets/npc/tex/mus_6_mouth3_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char mus_6_mouth4_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char mus_6_mouth4_TA_tex_txt[] = {
#include "assets/npc/tex/mus_6_mouth4_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char mus_6_mouth5_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char mus_6_mouth5_TA_tex_txt[] = {
#include "assets/npc/tex/mus_6_mouth5_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char mus_6_mouth6_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char mus_6_mouth6_TA_tex_txt[] = {
#include "assets/npc/tex/mus_6_mouth6_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char mus_6_tmem_txt[0x400];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char mus_6_tmem_txt[] = {
#include "assets/npc/tex/mus_6_tmem_txt.inc"
};
#endif


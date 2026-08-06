#include <dolphin/types.h>

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned short cml_1_pal[0x20 / sizeof(unsigned short)];
#else
ATTRIBUTE_ALIGN(32) extern unsigned short cml_1_pal[] = {
#include "assets/npc/tex/cml_1_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char cml_1_eye1_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char cml_1_eye1_TA_tex_txt[] = {
#include "assets/npc/tex/cml_1_eye1_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char cml_1_eye2_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char cml_1_eye2_TA_tex_txt[] = {
#include "assets/npc/tex/cml_1_eye2_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char cml_1_eye3_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char cml_1_eye3_TA_tex_txt[] = {
#include "assets/npc/tex/cml_1_eye3_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char cml_1_eye4_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char cml_1_eye4_TA_tex_txt[] = {
#include "assets/npc/tex/cml_1_eye4_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char cml_1_eye5_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char cml_1_eye5_TA_tex_txt[] = {
#include "assets/npc/tex/cml_1_eye5_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char cml_1_eye6_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char cml_1_eye6_TA_tex_txt[] = {
#include "assets/npc/tex/cml_1_eye6_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char cml_1_eye7_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char cml_1_eye7_TA_tex_txt[] = {
#include "assets/npc/tex/cml_1_eye7_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char cml_1_eye8_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char cml_1_eye8_TA_tex_txt[] = {
#include "assets/npc/tex/cml_1_eye8_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char cml_1_tmem_txt[0x780];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char cml_1_tmem_txt[] = {
#include "assets/npc/tex/cml_1_tmem_txt.inc"
};
#endif


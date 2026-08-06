#include <dolphin/types.h>

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned short hip_3_pal[0x20 / sizeof(unsigned short)];
#else
ATTRIBUTE_ALIGN(32) extern unsigned short hip_3_pal[] = {
#include "assets/npc/tex/hip_3_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char hip_3_eye1_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char hip_3_eye1_TA_tex_txt[] = {
#include "assets/npc/tex/hip_3_eye1_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char hip_3_eye2_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char hip_3_eye2_TA_tex_txt[] = {
#include "assets/npc/tex/hip_3_eye2_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char hip_3_eye3_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char hip_3_eye3_TA_tex_txt[] = {
#include "assets/npc/tex/hip_3_eye3_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char hip_3_eye4_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char hip_3_eye4_TA_tex_txt[] = {
#include "assets/npc/tex/hip_3_eye4_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char hip_3_eye5_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char hip_3_eye5_TA_tex_txt[] = {
#include "assets/npc/tex/hip_3_eye5_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char hip_3_eye6_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char hip_3_eye6_TA_tex_txt[] = {
#include "assets/npc/tex/hip_3_eye6_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char hip_3_eye7_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char hip_3_eye7_TA_tex_txt[] = {
#include "assets/npc/tex/hip_3_eye7_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char hip_3_eye8_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char hip_3_eye8_TA_tex_txt[] = {
#include "assets/npc/tex/hip_3_eye8_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char hip_3_tmem_txt[0x500];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char hip_3_tmem_txt[] = {
#include "assets/npc/tex/hip_3_tmem_txt.inc"
};
#endif


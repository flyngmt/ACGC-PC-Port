#include <dolphin/types.h>

#ifdef TARGET_PC
unsigned short ost_3_pal[0x20 / sizeof(unsigned short)] ATTRIBUTE_ALIGN(32);
#else
extern unsigned short ost_3_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/ost_3_pal.inc"
};
#endif

#ifdef TARGET_PC
unsigned char ost_3_eye1_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char ost_3_eye1_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/ost_3_eye1_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char ost_3_eye2_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char ost_3_eye2_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/ost_3_eye2_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char ost_3_eye3_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char ost_3_eye3_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/ost_3_eye3_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char ost_3_eye4_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char ost_3_eye4_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/ost_3_eye4_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char ost_3_eye5_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char ost_3_eye5_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/ost_3_eye5_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char ost_3_eye6_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char ost_3_eye6_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/ost_3_eye6_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char ost_3_eye7_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char ost_3_eye7_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/ost_3_eye7_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char ost_3_eye8_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char ost_3_eye8_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/ost_3_eye8_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char ost_3_tmem_txt[0x540] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char ost_3_tmem_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/ost_3_tmem_txt.inc"
};
#endif


#include <dolphin/types.h>

#ifdef TARGET_PC
unsigned short bea_1_pal[0x20 / sizeof(unsigned short)] ATTRIBUTE_ALIGN(32);
#else
extern unsigned short bea_1_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/bea_1_pal.inc"
};
#endif

#ifdef TARGET_PC
unsigned char bea_1_eye1_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char bea_1_eye1_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/bea_1_eye1_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char bea_1_eye2_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char bea_1_eye2_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/bea_1_eye2_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char bea_1_eye3_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char bea_1_eye3_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/bea_1_eye3_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char bea_1_eye4_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char bea_1_eye4_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/bea_1_eye4_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char bea_1_eye5_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char bea_1_eye5_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/bea_1_eye5_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char bea_1_eye6_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char bea_1_eye6_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/bea_1_eye6_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char bea_1_eye7_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char bea_1_eye7_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/bea_1_eye7_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char bea_1_eye8_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char bea_1_eye8_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/bea_1_eye8_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char bea_1_mouth1_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char bea_1_mouth1_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/bea_1_mouth1_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char bea_1_mouth2_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char bea_1_mouth2_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/bea_1_mouth2_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char bea_1_mouth3_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char bea_1_mouth3_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/bea_1_mouth3_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char bea_1_mouth4_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char bea_1_mouth4_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/bea_1_mouth4_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char bea_1_mouth5_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char bea_1_mouth5_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/bea_1_mouth5_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char bea_1_mouth6_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char bea_1_mouth6_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/bea_1_mouth6_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char bea_1_tmem_txt[0x400] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char bea_1_tmem_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/bea_1_tmem_txt.inc"
};
#endif


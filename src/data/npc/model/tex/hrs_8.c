#include <dolphin/types.h>

#ifdef TARGET_PC
unsigned short hrs_8_pal[0x20 / sizeof(unsigned short)] ATTRIBUTE_ALIGN(32);
#else
extern unsigned short hrs_8_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/hrs_8_pal.inc"
};
#endif

#ifdef TARGET_PC
unsigned char hrs_8_eye1_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char hrs_8_eye1_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/hrs_8_eye1_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char hrs_8_eye2_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char hrs_8_eye2_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/hrs_8_eye2_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char hrs_8_eye3_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char hrs_8_eye3_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/hrs_8_eye3_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char hrs_8_eye4_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char hrs_8_eye4_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/hrs_8_eye4_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char hrs_8_eye5_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char hrs_8_eye5_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/hrs_8_eye5_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char hrs_8_eye6_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char hrs_8_eye6_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/hrs_8_eye6_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char hrs_8_eye7_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char hrs_8_eye7_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/hrs_8_eye7_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char hrs_8_eye8_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char hrs_8_eye8_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/hrs_8_eye8_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char hrs_8_tmem_txt[0x580] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char hrs_8_tmem_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/hrs_8_tmem_txt.inc"
};
#endif


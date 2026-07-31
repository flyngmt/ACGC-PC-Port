#include <dolphin/types.h>

#ifdef TARGET_PC
unsigned short fob_1_pal[0x20 / sizeof(unsigned short)] ATTRIBUTE_ALIGN(32);
#else
extern unsigned short fob_1_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/fob_1_pal.inc"
};
#endif

#ifdef TARGET_PC
unsigned char fob_1_eye1_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char fob_1_eye1_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/fob_1_eye1_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char fob_1_eye2_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char fob_1_eye2_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/fob_1_eye2_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char fob_1_eye3_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char fob_1_eye3_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/fob_1_eye3_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char fob_1_eye4_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char fob_1_eye4_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/fob_1_eye4_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char fob_1_eye5_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char fob_1_eye5_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/fob_1_eye5_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char fob_1_eye6_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char fob_1_eye6_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/fob_1_eye6_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char fob_1_eye7_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char fob_1_eye7_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/fob_1_eye7_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char fob_1_eye8_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char fob_1_eye8_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/fob_1_eye8_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char fob_1_tmem_txt[0x740] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char fob_1_tmem_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/fob_1_tmem_txt.inc"
};
#endif


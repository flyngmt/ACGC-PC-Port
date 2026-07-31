#include <dolphin/types.h>

#ifdef TARGET_PC
unsigned short brd_5_pal[0x20 / sizeof(unsigned short)] ATTRIBUTE_ALIGN(32);
#else
extern unsigned short brd_5_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/brd_5_pal.inc"
};
#endif

#ifdef TARGET_PC
unsigned char brd_5_eye1_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char brd_5_eye1_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/brd_5_eye1_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char brd_5_eye2_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char brd_5_eye2_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/brd_5_eye2_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char brd_5_eye3_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char brd_5_eye3_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/brd_5_eye3_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char brd_5_eye4_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char brd_5_eye4_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/brd_5_eye4_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char brd_5_eye5_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char brd_5_eye5_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/brd_5_eye5_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char brd_5_eye6_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char brd_5_eye6_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/brd_5_eye6_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char brd_5_eye7_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char brd_5_eye7_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/brd_5_eye7_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char brd_5_eye8_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char brd_5_eye8_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/brd_5_eye8_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char brd_5_tmem_txt[0x500] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char brd_5_tmem_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/brd_5_tmem_txt.inc"
};
#endif


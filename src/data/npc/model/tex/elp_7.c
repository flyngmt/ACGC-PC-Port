#include <dolphin/types.h>

#ifdef TARGET_PC
unsigned short elp_7_pal[0x20 / sizeof(unsigned short)] ATTRIBUTE_ALIGN(32);
#else
extern unsigned short elp_7_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/elp_7_pal.inc"
};
#endif

#ifdef TARGET_PC
unsigned char elp_7_eye1_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char elp_7_eye1_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/elp_7_eye1_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char elp_7_eye2_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char elp_7_eye2_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/elp_7_eye2_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char elp_7_eye3_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char elp_7_eye3_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/elp_7_eye3_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char elp_7_eye4_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char elp_7_eye4_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/elp_7_eye4_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char elp_7_eye5_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char elp_7_eye5_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/elp_7_eye5_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char elp_7_eye6_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char elp_7_eye6_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/elp_7_eye6_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char elp_7_eye7_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char elp_7_eye7_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/elp_7_eye7_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char elp_7_eye8_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char elp_7_eye8_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/elp_7_eye8_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char elp_7_mouth1_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char elp_7_mouth1_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/elp_7_mouth1_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char elp_7_mouth2_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char elp_7_mouth2_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/elp_7_mouth2_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char elp_7_mouth3_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char elp_7_mouth3_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/elp_7_mouth3_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char elp_7_mouth4_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char elp_7_mouth4_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/elp_7_mouth4_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char elp_7_mouth5_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char elp_7_mouth5_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/elp_7_mouth5_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char elp_7_mouth6_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char elp_7_mouth6_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/elp_7_mouth6_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char elp_7_tmem_txt[0x400] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char elp_7_tmem_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/elp_7_tmem_txt.inc"
};
#endif


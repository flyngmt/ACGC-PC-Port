#include <dolphin/types.h>

#ifdef TARGET_PC
unsigned short cat_10_pal[0x20 / sizeof(unsigned short)] ATTRIBUTE_ALIGN(32);
#else
extern unsigned short cat_10_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/cat_10_pal.inc"
};
#endif

#ifdef TARGET_PC
unsigned char cat_10_eye1_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char cat_10_eye1_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/cat_10_eye1_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char cat_10_eye2_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char cat_10_eye2_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/cat_10_eye2_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char cat_10_eye3_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char cat_10_eye3_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/cat_10_eye3_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char cat_10_eye4_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char cat_10_eye4_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/cat_10_eye4_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char cat_10_eye5_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char cat_10_eye5_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/cat_10_eye5_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char cat_10_eye6_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char cat_10_eye6_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/cat_10_eye6_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char cat_10_eye7_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char cat_10_eye7_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/cat_10_eye7_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char cat_10_eye8_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char cat_10_eye8_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/cat_10_eye8_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char cat_10_mouth1_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char cat_10_mouth1_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/cat_10_mouth1_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char cat_10_mouth2_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char cat_10_mouth2_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/cat_10_mouth2_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char cat_10_mouth3_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char cat_10_mouth3_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/cat_10_mouth3_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char cat_10_mouth4_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char cat_10_mouth4_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/cat_10_mouth4_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char cat_10_mouth5_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char cat_10_mouth5_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/cat_10_mouth5_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char cat_10_mouth6_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char cat_10_mouth6_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/cat_10_mouth6_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char cat_10_tmem_txt[0x400] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char cat_10_tmem_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/cat_10_tmem_txt.inc"
};
#endif


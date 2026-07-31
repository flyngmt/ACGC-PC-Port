#include <dolphin/types.h>

#ifdef TARGET_PC
unsigned short cat_14_pal[0x20 / sizeof(unsigned short)] ATTRIBUTE_ALIGN(32);
#else
extern unsigned short cat_14_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/cat_14_pal.inc"
};
#endif

#ifdef TARGET_PC
unsigned char cat_14_eye1_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char cat_14_eye1_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/cat_14_eye1_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char cat_14_eye2_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char cat_14_eye2_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/cat_14_eye2_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char cat_14_eye3_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char cat_14_eye3_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/cat_14_eye3_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char cat_14_eye4_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char cat_14_eye4_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/cat_14_eye4_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char cat_14_eye5_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char cat_14_eye5_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/cat_14_eye5_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char cat_14_eye6_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char cat_14_eye6_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/cat_14_eye6_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char cat_14_eye7_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char cat_14_eye7_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/cat_14_eye7_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char cat_14_eye8_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char cat_14_eye8_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/cat_14_eye8_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char cat_14_mouth1_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char cat_14_mouth1_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/cat_14_mouth1_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char cat_14_mouth2_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char cat_14_mouth2_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/cat_14_mouth2_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char cat_14_mouth3_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char cat_14_mouth3_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/cat_14_mouth3_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char cat_14_mouth4_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char cat_14_mouth4_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/cat_14_mouth4_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char cat_14_mouth5_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char cat_14_mouth5_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/cat_14_mouth5_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char cat_14_mouth6_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char cat_14_mouth6_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/cat_14_mouth6_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char cat_14_tmem_txt[0x400] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char cat_14_tmem_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/cat_14_tmem_txt.inc"
};
#endif


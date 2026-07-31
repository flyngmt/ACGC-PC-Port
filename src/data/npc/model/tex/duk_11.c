#include <dolphin/types.h>

#ifdef TARGET_PC
unsigned short duk_11_pal[0x20 / sizeof(unsigned short)] ATTRIBUTE_ALIGN(32);
#else
extern unsigned short duk_11_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/duk_11_pal.inc"
};
#endif

#ifdef TARGET_PC
unsigned char duk_11_eye1_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char duk_11_eye1_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/duk_11_eye1_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char duk_11_eye2_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char duk_11_eye2_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/duk_11_eye2_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char duk_11_eye3_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char duk_11_eye3_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/duk_11_eye3_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char duk_11_eye4_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char duk_11_eye4_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/duk_11_eye4_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char duk_11_eye5_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char duk_11_eye5_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/duk_11_eye5_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char duk_11_eye6_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char duk_11_eye6_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/duk_11_eye6_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char duk_11_eye7_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char duk_11_eye7_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/duk_11_eye7_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char duk_11_eye8_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char duk_11_eye8_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/duk_11_eye8_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char duk_11_mouth1_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char duk_11_mouth1_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/duk_11_mouth1_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char duk_11_mouth2_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char duk_11_mouth2_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/duk_11_mouth2_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char duk_11_mouth3_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char duk_11_mouth3_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/duk_11_mouth3_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char duk_11_mouth4_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char duk_11_mouth4_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/duk_11_mouth4_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char duk_11_mouth5_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char duk_11_mouth5_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/duk_11_mouth5_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char duk_11_mouth6_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char duk_11_mouth6_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/duk_11_mouth6_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char duk_11_tmem_txt[0x400] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char duk_11_tmem_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/duk_11_tmem_txt.inc"
};
#endif


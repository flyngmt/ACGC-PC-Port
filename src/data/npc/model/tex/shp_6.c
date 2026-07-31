#include <dolphin/types.h>

#ifdef TARGET_PC
unsigned short shp_6_pal[0x20 / sizeof(unsigned short)] ATTRIBUTE_ALIGN(32);
#else
extern unsigned short shp_6_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/shp_6_pal.inc"
};
#endif

#ifdef TARGET_PC
unsigned char shp_6_eye1_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char shp_6_eye1_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/shp_6_eye1_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char shp_6_eye2_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char shp_6_eye2_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/shp_6_eye2_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char shp_6_eye3_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char shp_6_eye3_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/shp_6_eye3_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char shp_6_eye4_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char shp_6_eye4_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/shp_6_eye4_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char shp_6_eye5_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char shp_6_eye5_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/shp_6_eye5_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char shp_6_eye6_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char shp_6_eye6_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/shp_6_eye6_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char shp_6_eye7_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char shp_6_eye7_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/shp_6_eye7_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char shp_6_eye8_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char shp_6_eye8_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/shp_6_eye8_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char shp_6_mouth1_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char shp_6_mouth1_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/shp_6_mouth1_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char shp_6_mouth2_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char shp_6_mouth2_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/shp_6_mouth2_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char shp_6_mouth3_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char shp_6_mouth3_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/shp_6_mouth3_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char shp_6_mouth4_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char shp_6_mouth4_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/shp_6_mouth4_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char shp_6_mouth5_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char shp_6_mouth5_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/shp_6_mouth5_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char shp_6_mouth6_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char shp_6_mouth6_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/shp_6_mouth6_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char shp_6_tmem_txt[0x400] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char shp_6_tmem_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/shp_6_tmem_txt.inc"
};
#endif


#include <dolphin/types.h>

#ifdef TARGET_PC
unsigned short wol_2_pal[0x20 / sizeof(unsigned short)] ATTRIBUTE_ALIGN(32);
#else
extern unsigned short wol_2_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/wol_2_pal.inc"
};
#endif

#ifdef TARGET_PC
unsigned char wol_2_eye1_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char wol_2_eye1_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/wol_2_eye1_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char wol_2_eye2_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char wol_2_eye2_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/wol_2_eye2_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char wol_2_eye3_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char wol_2_eye3_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/wol_2_eye3_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char wol_2_eye4_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char wol_2_eye4_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/wol_2_eye4_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char wol_2_eye5_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char wol_2_eye5_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/wol_2_eye5_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char wol_2_eye6_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char wol_2_eye6_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/wol_2_eye6_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char wol_2_eye7_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char wol_2_eye7_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/wol_2_eye7_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char wol_2_eye8_TA_tex_txt[0x100] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char wol_2_eye8_TA_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/wol_2_eye8_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
unsigned char wol_2_tmem_txt[0x400] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char wol_2_tmem_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/wol_2_tmem_txt.inc"
};
#endif


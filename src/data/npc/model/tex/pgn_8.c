#include <dolphin/types.h>

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned short pgn_8_pal[0x20 / sizeof(unsigned short)];
#else
ATTRIBUTE_ALIGN(32) extern unsigned short pgn_8_pal[] = {
#include "assets/npc/tex/pgn_8_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char pgn_8_eye1_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char pgn_8_eye1_TA_tex_txt[] = {
#include "assets/npc/tex/pgn_8_eye1_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char pgn_8_eye2_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char pgn_8_eye2_TA_tex_txt[] = {
#include "assets/npc/tex/pgn_8_eye2_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char pgn_8_eye3_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char pgn_8_eye3_TA_tex_txt[] = {
#include "assets/npc/tex/pgn_8_eye3_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char pgn_8_eye4_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char pgn_8_eye4_TA_tex_txt[] = {
#include "assets/npc/tex/pgn_8_eye4_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char pgn_8_eye5_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char pgn_8_eye5_TA_tex_txt[] = {
#include "assets/npc/tex/pgn_8_eye5_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char pgn_8_eye6_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char pgn_8_eye6_TA_tex_txt[] = {
#include "assets/npc/tex/pgn_8_eye6_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char pgn_8_eye7_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char pgn_8_eye7_TA_tex_txt[] = {
#include "assets/npc/tex/pgn_8_eye7_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char pgn_8_eye8_TA_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char pgn_8_eye8_TA_tex_txt[] = {
#include "assets/npc/tex/pgn_8_eye8_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char pgn_8_tmem_txt[0x580];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char pgn_8_tmem_txt[] = {
#include "assets/npc/tex/pgn_8_tmem_txt.inc"
};
#endif


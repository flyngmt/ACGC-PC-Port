#include <dolphin/types.h>

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned short hem_1_pal[0x20 / sizeof(unsigned short)];
#else
ATTRIBUTE_ALIGN(32) extern unsigned short hem_1_pal[] = {
#include "assets/npc/tex/hem_1_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char hem_1_tmem_txt[0x740];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char hem_1_tmem_txt[] = {
#include "assets/npc/tex/hem_1_tmem_txt.inc"
};
#endif


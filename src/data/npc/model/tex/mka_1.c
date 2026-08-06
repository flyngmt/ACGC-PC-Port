#include <dolphin/types.h>

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned short mka_1_pal[0x20 / sizeof(unsigned short)];
#else
ATTRIBUTE_ALIGN(32) extern unsigned short mka_1_pal[] = {
#include "assets/npc/tex/mka_1_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) unsigned char mka_1_tmem_txt[0x480];
#else
ATTRIBUTE_ALIGN(32) extern unsigned char mka_1_tmem_txt[] = {
#include "assets/npc/tex/mka_1_tmem_txt.inc"
};
#endif


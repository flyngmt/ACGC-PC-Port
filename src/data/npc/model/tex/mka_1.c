#include <dolphin/types.h>

#ifdef TARGET_PC
unsigned short mka_1_pal[0x20 / sizeof(unsigned short)] ATTRIBUTE_ALIGN(32);
#else
extern unsigned short mka_1_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/mka_1_pal.inc"
};
#endif

#ifdef TARGET_PC
unsigned char mka_1_tmem_txt[0x480] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char mka_1_tmem_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/mka_1_tmem_txt.inc"
};
#endif


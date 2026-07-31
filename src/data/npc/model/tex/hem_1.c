#include <dolphin/types.h>

#ifdef TARGET_PC
unsigned short hem_1_pal[0x20 / sizeof(unsigned short)] ATTRIBUTE_ALIGN(32);
#else
extern unsigned short hem_1_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/hem_1_pal.inc"
};
#endif

#ifdef TARGET_PC
unsigned char hem_1_tmem_txt[0x740] ATTRIBUTE_ALIGN(32);
#else
extern unsigned char hem_1_tmem_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/npc/tex/hem_1_tmem_txt.inc"
};
#endif


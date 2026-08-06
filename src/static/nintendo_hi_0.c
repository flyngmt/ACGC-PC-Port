#include "nintendo_hi_0.h" // IWYU pragma: keep

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 nintendo_hi_0[NINTENDO_HI_0_SIZE];
#else
#include "assets/nintendo_hi_0.inc"
#endif

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_static_nintendo_hi_0_c(void) {
    pc_load_asset("assets/nintendo_hi_0.bin", nintendo_hi_0, 0x9900, 0xC0140, 1, 0);
}
#endif

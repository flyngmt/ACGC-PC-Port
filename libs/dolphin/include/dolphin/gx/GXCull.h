#ifndef _DOLPHIN_GXCULL
#define _DOLPHIN_GXCULL

#include <dolphin/types.h>

#ifdef __cplusplus
extern "C" {
#endif

void GXSetScissor(u32 left, u32 top, u32 wd, u32 ht);
void GXSetCullMode(GXCullMode mode);
void GXSetCoPlanar(GXBool enable);

#ifdef __cplusplus
}
#endif

#endif // _DOLPHIN_GXCULL

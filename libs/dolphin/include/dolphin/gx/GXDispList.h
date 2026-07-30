#ifndef _DOLPHIN_GXDISPLIST
#define _DOLPHIN_GXDISPLIST

#include <dolphin/types.h>

#ifdef __cplusplus
extern "C" {
#endif

void GXBeginDisplayList(void* list, u32 size);
u32 GXEndDisplayList(void);
void GXCallDisplayList(void* list, u32 nbytes);

#ifdef __cplusplus
}
#endif

#endif // _DOLPHIN_GXDISPLIST

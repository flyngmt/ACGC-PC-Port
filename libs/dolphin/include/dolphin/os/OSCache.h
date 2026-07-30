#ifndef OS_CACHE_H
#define OS_CACHE_H
#include "types.h"
#ifdef __cplusplus
extern "C" {
#endif

void DCEnable(void);
void DCInvalidateRange(void*, u32);
void DCFlushRange(void*, u32);
void DCStoreRange(void*, u32);
void DCFlushRangeNoSync(void*, u32);
void DCStoreRangeNoSync(void*, u32);
void DCZeroRange(void*, u32);
void DCTouchRange(void*, u32 len);
void ICInvalidateRange(void*, u32);
void ICFlashInvalidate(void);
void ICEnable(void);
void LCDisable(void);

//void L2GlobalInvalidate(void);

//void DMAErrorHandler(u8, struct OSContext*, u32, u32, ...);

//void __OSCacheInit(void);

#ifdef __cplusplus
}
#endif
#endif

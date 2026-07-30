#ifndef _DOLPHIN_GXPERF
#define _DOLPHIN_GXPERF

#include <dolphin/types.h>

#ifdef __cplusplus
extern "C" {
#endif

void GXReadXfRasMetric(u32* xf_wait_in, u32* xf_wait_out, u32* ras_busy, u32* clocks);

#ifdef __cplusplus
}
#endif

#endif // _DOLPHIN_GXPERF

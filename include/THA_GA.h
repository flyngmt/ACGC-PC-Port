#ifndef THA_GA_H
#define THA_GA_H

#include "TwoHeadArena.h"
#include "PR/mbi.h"
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  size_t size;
  Gfx* buf_p;
  Gfx* head_p;
  Gfx* tail_p;
} TwoHeadArenaGfx_t;

typedef TwoHeadArenaGfx_t TwoHeadArenaGfx;

typedef union {
  TwoHeadArena tha;
  TwoHeadArenaGfx thaGfx;
} THA_GA_t;

typedef THA_GA_t THA_GA;

extern void THA_GA_ct(THA_GA* tha_ga, Gfx* p, size_t n);
extern void THA_GA_dt(THA_GA* tha_ga); /* @unused */
extern int THA_GA_isCrash(THA_GA* tha_ga);
extern void THA_GA_init(THA_GA* tha_ga); /* @unused*/
extern int THA_GA_getFreeBytes(THA_GA* tha_ga);
extern void* THA_GA_getTailPtr(THA_GA* tha_ga); /* @unused */
extern void* THA_GA_nextPtrN(THA_GA* tha_ga, size_t n); /* @unused */
extern void* THA_GA_nextPtr1(THA_GA* tha_ga); /* @unused */
extern Gfx* THA_GA_NEXT_DISP(THA_GA* tha_ga); /* @unused */
extern void* THA_GA_getHeadPtr(THA_GA* tha_ga); /* @unused */
extern void THA_GA_setHeadPtr(THA_GA* tha_ga, void *p); /* @unused */
extern N64Mtx* THA_GA_alloc(THA_GA* tha_ga, size_t n); /* @unused */
extern N64Mtx* THA_GA_allocMtxN(THA_GA* tha_ga, size_t n); /* @unused */
extern N64Mtx* THA_GA_allocMtx1(THA_GA* tha_ga); /* @unused */
extern Vtx* THA_GA_allocVtxN(THA_GA* tha_ga, size_t n); /* @unused */
extern Vtx* THA_GA_allocVtx1(THA_GA* tha_ga); /* @unused */

#ifdef __cplusplus
};
#endif

#endif

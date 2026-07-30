#include "TwoHeadArena.h"

#include "libultra/libultra.h"
#include "types.h"

/* @fabricated */
/*
extern void* THA_getHeadPtr(TwoHeadArena* this) {
  return this->head_p;
}
*/

/* @fabricated */
/*
extern void THA_setHeadPtr(TwoHeadArena* this, void* p) {
  this->head_p = (char*)p;
}
*/

/* @fabricated */
/*
extern void* THA_getTailPtr(TwoHeadArena* this) {
  return this->tail_p;
}
*/

/* @fabricated */
/*
extern void* THA_nextPtrN(TwoHeadArena* this, size_t n) {
  char* next_p = this->head_p;
  this->head_p += n;
  return (void*)next_p;
}
*/

/* @fabricated */
/*
extern void* THA_nextPtr1(TwoHeadArena* this) {
  return THA_nextPtrN(this, 1);
}
*/

/* @fabricated */
/*
extern void* THA_alloc(TwoHeadArena* this, size_t siz) {
  u32 mask;
  if (siz == 8) {
    mask = ~(8 - 1);
  } else if (siz == 2 || siz == 6 || siz == 10 || siz == 14) {
    mask = ~(2 - 1);
  } else if (siz > 15) {
    mask = ~(16 - 1);
  } else {
    mask = ~0;
  }

  this->tail_p = (char*)((((u32)this->tail_p & mask) - siz) & mask);
  return this->tail_p;
}
*/

extern void* THA_alloc16(TwoHeadArena* this, size_t siz) {
  const uintptr_t mask = ~(uintptr_t)(16 - 1);
  this->tail_p = (char*)((((uintptr_t)this->tail_p & mask) - siz) & mask);
  return this->tail_p;
}

extern void* THA_allocAlign(TwoHeadArena* this, size_t siz, int mask) {
  uintptr_t native_mask = (uintptr_t)(s64)mask;
  this->tail_p = (char*)((((uintptr_t)this->tail_p & native_mask) - siz) & native_mask);
  return this->tail_p;
}

extern int THA_getFreeBytesAlign(TwoHeadArena* this, int mask) {
  uintptr_t native_mask = (uintptr_t)(s64)mask;
  uintptr_t aligned_head = ((uintptr_t)this->head_p + (u32)~mask) & native_mask;
  return (int)((uintptr_t)this->tail_p - aligned_head);
}

extern int THA_getFreeBytes16(TwoHeadArena* this) {
  return THA_getFreeBytesAlign(this, -16);
}

extern int THA_getFreeBytes(TwoHeadArena* this) {
  return THA_getFreeBytesAlign(this, -1);
}

extern int THA_isCrash(TwoHeadArena* this) {
  return THA_getFreeBytes(this) < 0;
}

extern void THA_init(TwoHeadArena* this) {
  this->head_p = this->buf_p;
  this->tail_p = this->buf_p + this->size;
}

extern void THA_ct(TwoHeadArena* this, char* p, size_t n) {
  this->buf_p = p;
  this->size = n;
  THA_init(this);
}

extern void THA_dt(TwoHeadArena* this) {
  bzero(this, sizeof(TwoHeadArena));
}

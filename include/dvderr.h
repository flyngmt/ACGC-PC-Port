#ifndef DVDERR_H
#define DVDERR_H

#include "types.h"
#include "PR/mbi.h"

#ifdef __cplusplus
extern "C" {
#endif

enum dvderr_state {
  DVDERR_NONE = -1,

  DVDERR_COVER_OPEN = 0,
  DVDERR_NO_DISK,
  DVDERR_WRONG_DISK,
  DVDERR_RETRY,
  DVDERR_FATAL,

  DVDERR_NUM
};

typedef void (*DVDERR_DRAW_PROC)();

/* sizeof(dvderr_work) == 0x3F8 */
typedef struct dvderr_work_s {
  /* 0x000 */ Gfx gfx[100];               // display list buffer
  /* 0x320 */ Gfx* gfx_p;                 // current display list buffer write pointer
  /* 0x328 */ N64Mtx ortho;                  // orthographic matrix
  /* 0x368 */ N64Mtx projection;             // projection matrix
  /* 0x3A8 */ N64Mtx modelview;              // modelview matrix
  /* 0x3E8 */ f32 scale;                  // scale for modelview matrix

  /* 0x3EC */ DVDERR_DRAW_PROC draw_proc; // current draw routine
  /* 0x3F0 */ int now_error;              // current dvd error
  /* 0x3F4 */ int next_error;             // next dvd error
} dvderr_work;

extern int dvderr_draw();
extern void dvderr_init();

#ifdef __cplusplus
};
#endif

#endif

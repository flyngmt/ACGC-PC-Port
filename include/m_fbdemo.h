#ifndef FBDEMO_H
#define FBDEMO_H

#include "types.h"
#include "PR/mbi.h"
#include "m_lib.h"

typedef struct {
    /* 0x00 */ int cols;
    /* 0x04 */ int rows;
    /* 0x08 */ int frame;
    /* 0x0C */ xy_t* vtxData;
    /* 0x10 */ Vtx* vtxFrame1;
    /* 0x14 */ Vtx* vtxFrame2;
    /* 0x18 */ N64Mtx projection;
    /* 0x58 */ N64Mtx modelView1;
    /* 0x98 */ N64Mtx modelView2;
    /* 0xD8 */ Gfx* gfx; // "gfxtbl"
    /* 0xDC */ u16* zBuffer;
} fbdemo_c; // size = 0xE0


extern void fbdemo_init_gfx(fbdemo_c*);
extern void fbdemo_init_data(fbdemo_c*);
extern void fbdemo_cleanup(fbdemo_c*);
extern fbdemo_c* fbdemo_init(fbdemo_c*, int, int); 
extern void fbdemo_update(fbdemo_c*);
extern void fbdemo_draw(fbdemo_c*, Gfx**);
extern void fbdemo_move(fbdemo_c*);

#endif


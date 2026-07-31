#ifndef FBDEMO_WIPE_H
#define FBDEMO_WIPE_H
#include "types.h"
#include "PR/mbi.h"
#include "libu64/u64types.h"

typedef struct {
    /* 0x000 */ Color_RGBA8_u32 color;
    /* 0x004 */ Color_RGBA8_u32 unkColor;
    /* 0x008 */ u8 direction;
    /* 0x009 */ u8 frame;
    /* 0x00A */ u8 finished;
    /* 0x00C */ u16 texX;
    /* 0x00E */ u16 texY;
    /* 0x010 */ u16 normal;
    /* 0x018 */ N64Mtx projection;
    /* 0x058 */ N64Mtx lookAt;
    /* 0x098 */ N64Mtx modelView[2][3];
} fbdemo_wipe1; // size = 0x218


extern fbdemo_wipe1* fbdemo_wipe1_init(fbdemo_wipe1*);
extern void fbdemo_wipe1_move(fbdemo_wipe1*, int);
extern void fbdemo_wipe1_draw(fbdemo_wipe1*, Gfx**);
extern void fbdemo_wipe1_startup(fbdemo_wipe1*);
extern void fbdemo_wipe1_settype(fbdemo_wipe1*, int);
extern void fbdemo_wipe1_setcolor_rgba8888(fbdemo_wipe1*, u32);
extern u8 fbdemo_wipe1_is_finish(fbdemo_wipe1*);
#endif
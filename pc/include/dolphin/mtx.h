#ifndef ACGC_PC_DOLPHIN_MTX_H
#define ACGC_PC_DOLPHIN_MTX_H

/*
 * libultra already owns the name Mtx for its fixed-point N64 matrix. Rename
 * Aurora's floating-point Dolphin type while its header is parsed, then
 * expose the aliases used by this game's matching SDK headers.
 */
#define Mtx AuroraMtx
#include <extern/aurora/include/dolphin/mtx.h>
#undef Mtx

typedef AuroraMtx Mtx34;
typedef AuroraMtx GC_Mtx;
typedef f32 (*MtxP)[4];

#endif

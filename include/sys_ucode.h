#ifndef SYS_UCODE_H
#define SYS_UCODE_H

#include "types.h"
#include "PR/mbi.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ucode_info_s {
    int type;
    void* ucode_p;
} ucode_info;

#define UCODE_TYPE_NONE 0
#define UCODE_TYPE_POLY_TEXT 1
#define UCODE_TYPE_POLY_DATA 2
#define UCODE_TYPE_SPRITE_TEXT 3
#define UCODE_TYPE_SPRITE_DATA 4

#define SP_UCODE_DATA_SIZE 0x800

extern s64 gspF3DZEX2_NoN_PosLight_fifoDataStart[];
extern s64 gspF3DZEX2_NoN_PosLight_fifoTextStart[];

extern u64 gspS2DEX2_fifoDataStart[];
extern u64 gspS2DEX2_fifoTextStart[];

extern s64* ucode_GetPolyTextStart();
extern s64* ucode_GetPolyDataStart();
extern u64* ucode_GetSpriteTextStart();
extern u64* ucode_GetSpriteDataStart();

#ifdef __cplusplus
};
#endif

#endif

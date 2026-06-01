#include "jaudio_NES/audioconst.h"

fxconfig NA_HALL_DELAY = { 1, 0x20, 0x4500, 0x14, 0x1100, 0x7fff, 0, 0, 0xff, 0, 0 };

// clang-format off
na_spec_config NA_SPEC_CONFIG[1] = {
    { 
        0xbb80,
        1,
        24,
        5,
        0,
        0,
        1,
        0,
        0,
        &NA_HALL_DELAY,
        0x400,
        0x200,
        0x07fff,
        0,
        0x680,
        0x4500,
        0,
        0x7800,
        0x2300,
        0,
    },
};
// clang-format on

#if defined(TARGET_PC) && UINTPTR_MAX > 0xFFFFFFFFu
/* 64-bit: audio structs with pointer fields are larger, need bigger heaps */
ALGlobalsConst AGC = {
    0x18, 0x30, 0xE0000, 0x70000, 0x50000,
};
#else
ALGlobalsConst AGC = {
    0x18, 0x30, 0x70000, 0x38000, 0x28000,
};
#endif

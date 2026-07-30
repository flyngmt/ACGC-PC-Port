#ifndef _DOLPHIN_OS_OSFASTCAST_H
#define _DOLPHIN_OS_OSFASTCAST_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif // ifdef __cplusplus

/////// FAST CAST DEFINES ////////
// GQR formats.
#define OS_GQR_U8 (0x0004)  // GQR 1
#define OS_GQR_U16 (0x0005) // GQR 2
#define OS_GQR_S8 (0x0006)  // GQR 3
#define OS_GQR_S16 (0x0007) // GQR 4

// GQRs for fast casting.
#define OS_FASTCAST_U8 (2)
#define OS_FASTCAST_U16 (3)
#define OS_FASTCAST_S8 (4)
#define OS_FASTCAST_S16 (5)

//////////////////////////////////

/////// FAST CAST INLINES ////////
// Initialise fast casting.
static inline void OSInitFastCast() {
#ifdef __MWERKS__ // clang-format off
	asm {
		li r3, OS_GQR_U8
		oris r3, r3, OS_GQR_U8
		mtspr 0x392, r3
		li r3, OS_GQR_U16
		oris r3, r3, OS_GQR_U16
		mtspr 0x393, r3
		li r3, OS_GQR_S8
		oris r3, r3, OS_GQR_S8
		mtspr 0x394, r3
		li r3, OS_GQR_S16
		oris r3, r3, OS_GQR_S16
		mtspr 0x395, r3
	}
#endif // clang-format on
}

// Float to int.
static inline s16 __OSf32tos16(
#ifndef TARGET_PC
    register
#endif
    f32 inF) {
#ifdef TARGET_PC
    if (inF > 32767.0f) return 32767;
    if (inF < -32768.0f) return -32768;
    return (s16)inF;
#else
    register s16 out;
    u32 tmp;
    register u32* tmpPtr = &tmp;
#ifdef __MWERKS__ // clang-format off
	asm {
		psq_st inF, 0(tmpPtr), 0x1, OS_FASTCAST_S16
		lha out, 0(tmpPtr)
	}
#endif // clang-format on
    return out;
#endif
}

static inline void OSf32tos16(f32* f, s16* out) {
    *out = __OSf32tos16(*f);
}

static inline u8 __OSf32tou8(
#ifndef TARGET_PC
    register
#endif
    f32 inF) {
#ifdef TARGET_PC
    if (inF > 255.0f) return 255;
    if (inF < 0.0f) return 0;
    return (u8)inF;
#else
    register u8 out;
    u32 tmp;
    register u32* tmpPtr = &tmp;
#ifdef __MWERKS__ // clang-format off
	asm {
		psq_st inF, 0(tmpPtr), 0x1, OS_FASTCAST_U8
		lbz out, 0(tmpPtr)
	}
#endif // clang-format on
    return out;
#endif
}

static inline void OSf32tou8(f32* f, u8* out) {
    *out = __OSf32tou8(*f);
}

static inline s8 __OSf32tos8(
#ifndef TARGET_PC
    register
#endif
    f32 inF) {
#ifdef TARGET_PC
    if (inF > 127.0f) return 127;
    if (inF < -128.0f) return -128;
    return (s8)inF;
#else
    register s8 out;
    u32 tmp;
    register u32* tmpPtr = &tmp;
#ifdef __MWERKS__ // clang-format off
	asm {
		psq_st inF, 0(tmpPtr), 0x1, OS_FASTCAST_S8
		lbz out, 0(tmpPtr)
		extsb out, out
	}
#endif // clang-format on
    return out;
#endif
}

static inline void OSf32tos8(f32* f, s8* out) {
    *out = __OSf32tos8(*f);
}

static inline float __OSs16tof32(
#ifndef TARGET_PC
    register
#endif
    s16* s) {
#ifdef TARGET_PC
    return (float)(*s);
#else
    register float f;
#ifdef __MWERKS__ // clang-format off
    asm {
        psq_l f, 0(s), 1, 5
    }
#endif // clang-format on
    return f;
#endif
}

static inline void OSs16tof32(
#ifndef TARGET_PC
    register
#endif
    s16* s,
#ifndef TARGET_PC
    volatile register
#endif
    f32* f) {
    *f = __OSs16tof32(s);
}

//////////////////////////////////

#ifdef __cplusplus
};
#endif // ifdef __cplusplus

#endif

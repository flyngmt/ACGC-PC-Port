#ifndef _common_h_
#define _common_h_

#if DO_INLINE_ATTRIBS
#ifdef _MSC_VER
#define FIXNES_NOINLINE __declspec(noinline)
#define FIXNES_ALWAYSINLINE __forceinline
#else
#define FIXNES_NOINLINE __attribute__((noinline))
#define FIXNES_ALWAYSINLINE __attribute__((always_inline))
#endif
#else
#define FIXNES_NOINLINE
#define FIXNES_ALWAYSINLINE
#endif

#endif

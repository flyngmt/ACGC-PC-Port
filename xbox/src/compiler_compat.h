#ifndef AC_XBOX360_COMPILER_COMPAT_H
#define AC_XBOX360_COMPILER_COMPAT_H
#if !(defined(TARGET_XBOX) || defined(TARGET_XBOX360)) || !defined(__powerpc__)
#error This compatibility header requires the Xbox 360 PowerPC smoke target
#endif
/* Metrowerks intrinsics in shared MSL headers. These are real scalar PPC
 * instructions, not Gekko paired-single operations or SDK calls.
 * Numerical equivalence on Xenon remains to be tested.
 */
#define __fabs(x) __builtin_fabs(x)
#define __abs(x) __builtin_abs(x)
#define __alloca(n) __builtin_alloca(n)
static __inline__ double ac_ppc_frsqrte(double x) {
    double result;
    __asm__("frsqrte %0,%1" : "=f"(result) : "f"(x));
    return result;
}
#define __frsqrte(x) ac_ppc_frsqrte(x)
#endif

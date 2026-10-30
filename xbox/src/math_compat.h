#ifndef AC_XBOX360_MATH_COMPAT_H
#define AC_XBOX360_MATH_COMPAT_H
#include <float.h>
/* Standard C libm ABI, supplied by the pinned newlib library. Do not include
 * SDK libc structures in the legacy game namespace. This intentionally uses
 * standard sqrt domain/NaN behavior, not the CodeWarrior approximation. */
#ifdef __cplusplus
extern "C" {
#endif
double fabs(double);
float fabsf(float);
double sqrt(double);
float sqrtf(float);
double sin(double);
double cos(double);
double tan(double);
double asin(double);
double acos(double);
double atan(double);
double atan2(double, double);
double exp(double);
double log(double);
double log10(double);
double pow(double, double);
double floor(double);
double ceil(double);
double fmod(double, double);
double ldexp(double, int);
double scalbn(double, int);
double copysign(double, double);
float sinf(float);
float cosf(float);
float tanf(float);
float asinf(float);
float acosf(float);
float atanf(float);
float atan2f(float, float);
float expf(float);
float logf(float);
float powf(float, float);
float floorf(float);
float ceilf(float);
float fmodf(float, float);
float copysignf(float, float);
#ifdef __cplusplus
}
#endif
#define NAN (__builtin_nanf(""))
#define INFINITY (__builtin_inff())
#define HUGE_VAL (__builtin_huge_val())
#define HUGE_VALF (__builtin_huge_valf())
/* Retain MSL's classification numbers for game comparisons. */
#define FP_NAN 1
#define FP_QNAN 1
#define FP_SNAN 0
#define FP_INFINITE 2
#define FP_ZERO 3
#define FP_NORMAL 4
#define FP_SUBNORMAL 5
#define fpclassify(x) __builtin_fpclassify(1, 2, 4, 5, 3, (x))
#define isfinite(x) __builtin_isfinite(x)
#define isnan(x) __builtin_isnan(x)
#define isinf(x) __builtin_isinf(x)
#define signbit(x) __builtin_signbit(x)
static __inline__ int __fpclassifyf(float x) { return fpclassify(x); }
static __inline__ int __fpclassifyd(double x) { return fpclassify(x); }
#endif

#ifndef _FLOAT_H_
#define _FLOAT_H_

#ifdef TARGET_PC
#include <float.h>
#else

#define FLT_EPSILON 1.1920928955078125e-07f

#endif /* TARGET_PC */
#endif

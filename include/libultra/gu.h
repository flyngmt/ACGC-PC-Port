#ifndef GU_H
#define GU_H
#include "types.h"
#include "PR/mbi.h"
#include "libultra/ultratypes.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAX
#define MAX(a,b) (((a)>(b))?(a):(b))
#endif
#ifndef MIN
#define MIN(a,b) (((a)<(b))?(a):(b))
#endif

#define	FTOFIX32(x)	(long)((x) * (float)0x00010000)
#define	FIX32TOF(x)	((float)(x) * (1.0f / (float)0x00010000))
#define	FTOFRAC8(x)	((int) MIN(((x) * (128.0f)), 127.0f) & 0xff)

void guMtxIdentF(float mf[4][4]);

static inline void guTranslateF(float m[4][4], float x, float y, float z){
    guMtxIdentF(m);
    m[3][0] = x;
    m[3][1] = y;
    m[3][2] = z;
}

static inline void guScaleF(float mf[4][4], float x, float y, float z) {
    guMtxIdentF(mf);
    mf[0][0] = x;
    mf[1][1] = y;
    mf[2][2] = z;
    mf[3][3] = 1.0;
}

void guMtxF2L(float mf[4][4], Mtx *m);

void guTranslate(Mtx *m, float x, float y, float z);
void guScale(Mtx *m, float x, float y, float z);

void guMtxIdent(Mtx *m);
void guNormalize(float* x, float* y, float* z); 
void guOrtho(Mtx *m, float l, float r, float b, float t, float n, float f, float scale);

void guRotate(Mtx* m, float a, float x, float y, float z);

 void guLookAt(Mtx *m, 
			float xEye, float yEye, float zEye,
			float xAt,  float yAt,  float zAt,
			float xUp,  float yUp,  float zUp);
			
void guPerspective(Mtx *m, u16 *perspNorm, float fovy, 
			  float aspect, float near, float far, float scale);
			  
			  
void guLookAtHilite (Mtx *m, LookAt *l, Hilite *h, 
		float xEye, float yEye, float zEye,
		float xAt,  float yAt,  float zAt,
		float xUp,  float yUp,  float zUp,
		float xl1,  float yl1,  float zl1,   /* light 1 direction */
		float xl2,  float yl2,  float zl2,   /* light 2 direction */
		int twidth, int theight);	     /* highlight txtr size*/

extern signed short sins (unsigned short angle);
extern signed short coss (unsigned short angle);

#ifdef __cplusplus
}
#endif

#endif

#include "libultra/gu.h"
#include "MSL_C/math.h"

void guRotateF(float mf[4][4], float a, float x, float y, float z)
{
	float xxsine;
	float zxsine;
    float yxsine;
    float	cosine;
    float	sine;
    static float	dtor = 3.1415926f / 180.0f;
    float tmp;
	float	ab, bc, ca, t;
	guNormalize(&x, &y, &z);
    
    tmp = a * dtor;
    
	sine = sin(tmp);
	cosine = cos(tmp);
	t = (1-cosine);
	ab = x*y*t;
	bc = y*z*t;
	ca = z*x*t;

	guMtxIdentF(mf);

    xxsine = x * sine;
    yxsine = y * sine;
    zxsine = z * sine;

	t = x*x;
	mf[0][0] = t+cosine*(1-t);
	mf[2][1] = bc-xxsine;
	mf[1][2] = bc+xxsine;

	t = y*y;
	mf[1][1] = t+cosine*(1-t);
	mf[2][0] = ca+yxsine;
	mf[0][2] = ca-yxsine;

	t = z*z;
	mf[2][2] = t+cosine*(1-t);
	mf[1][0] = ab-zxsine;
	mf[0][1] = ab+zxsine;
}

void guRotate(N64Mtx *m, float a, float x, float y, float z) {
    float mf[4][4];
    guRotateF(mf, a, x, y, z);
    guMtxF2L(mf, m);
}

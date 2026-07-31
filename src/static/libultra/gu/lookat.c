#include "libultra/gu.h"
#include "MSL_C/w_math.h"

void guLookAtF(float mf[4][4], float xEye, float yEye, float zEye,
	       float xAt,  float yAt,  float zAt,
	       float xUp,  float yUp,  float zUp)
{
	float	len, xLook, yLook, zLook, xRight, yRight, zRight;

	guMtxIdentF(mf);

	xLook = xAt - xEye;
	yLook = yAt - yEye;
	zLook = zAt - zEye;

	/* Negate because positive Z is behind us: */
	len =  sqrtf (xLook*xLook + yLook*yLook + zLook*zLook);
    len = -1.0f/ len;
	xLook *= len;
	yLook *= len;
	zLook *= len;

	/* Right = Up x Look */

	xRight = yUp * zLook - zUp * yLook;
	yRight = zUp * xLook - xUp * zLook;
	zRight = xUp * yLook - yUp * xLook;
    len = sqrtf (xRight*xRight + yRight*yRight + zRight*zRight);
	len = 1.0f / len;
	xRight *= len;
	yRight *= len;
	zRight *= len;

	/* Up = Look x Right */

	xUp = yLook * zRight - zLook * yRight;
	yUp = zLook * xRight - xLook * zRight;
	zUp = xLook * yRight - yLook * xRight;
    len = sqrtf (xUp*xUp + yUp*yUp + zUp*zUp);
	len = 1.0f / len;
	xUp *= len;
	yUp *= len;
	zUp *= len;

	mf[0][0] = xRight;
	mf[1][0] = yRight;
	mf[2][0] = zRight;
	mf[3][0] = -(xEye * xRight + yEye * yRight + zEye * zRight);

	mf[0][1] = xUp;
	mf[1][1] = yUp;
	mf[2][1] = zUp;
	mf[3][1] = -(xEye * xUp + yEye * yUp + zEye * zUp);

	mf[0][2] = xLook;
	mf[1][2] = yLook;
	mf[2][2] = zLook;
	mf[3][2] = -(xEye * xLook + yEye * yLook + zEye * zLook);

	mf[0][3] = 0;
	mf[1][3] = 0;
	mf[2][3] = 0;
	mf[3][3] = 1;
}


void guLookAt (N64Mtx *m, float xEye, float yEye, float zEye,
	       float xAt,  float yAt,  float zAt,
	       float xUp,  float yUp,  float zUp)
{
	float mf[4][4];

	guLookAtF(mf, xEye, yEye, zEye, xAt, yAt, zAt, xUp, yUp, zUp);

	guMtxF2L(mf, m);
}

#include "libultra/gu.h"
#include "MSL_C/math.h"

void guPerspectiveF(float mf[4][4], u16 *perspNorm, float fovy, float aspect, float near, float far, float scale)
{
	float	cot;
	int	i, j;

	guMtxIdentF(mf);

	fovy *= 3.1415926 / 180.0;
	cot = (float)cos(fovy/2) / (float)sin(fovy/2);

	mf[0][0] = cot / aspect;
	mf[1][1] = cot;
	mf[2][2] = (near + far) / (near - far);
	mf[2][3] = -1;
	mf[3][2] = (2 * near * far) / (near - far);
	mf[3][3] = 0;
    
	for (i=0; i<4; i++)
	    for (j=0; j<4; j++)
		mf[i][j] *= scale;


	if (perspNorm != (u16 *) NULL) {
	    if (near+far<=2.0) {
		*perspNorm = (u16) 0xFFFF;
	    } else  {
		*perspNorm = (u16) ((2.0*65536.0)/(near+far));
		if (*perspNorm<=0) 
		    *perspNorm = (u16) 0x0001;
	    }
	}
}

void guPerspective(N64Mtx *m, u16 *perspNorm, float fovy, float aspect, float near, float far, float scale)
{
	float mf[4][4];

	guPerspectiveF(mf, perspNorm, fovy, aspect, near, far, scale);

	guMtxF2L(mf, m);
}

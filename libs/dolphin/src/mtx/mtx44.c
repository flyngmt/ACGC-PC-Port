#include <dolphin.h>
#include <dolphin/mtx.h>
#include <macros.h>

extern f32 tanf(f32);

// NOTE: this is not present in SMS but needed for .sdata2 to match
// stolen from prime
void C_MTXFrustum(Mtx44 m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f)
{
	f32 tmp;

	tmp     = 1.0f / (r - l);
	m[0][0] = (2 * n) * tmp;
	m[0][1] = 0.0f;
	m[0][2] = (r + l) * tmp;
	m[0][3] = 0.0f;

	tmp     = 1.0f / (t - b);
	m[1][0] = 0.0f;
	m[1][1] = (2 * n) * tmp;
	m[1][2] = (t + b) * tmp;
	m[1][3] = 0.0f;

	m[2][0] = 0.0f;
	m[2][1] = 0.0f;

	tmp     = 1.0f / (f - n);
	m[2][2] = -(n)*tmp;
	m[2][3] = -(f * n) * tmp;
	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = -1.0f;
	m[3][3] = 0.0f;
}

void C_MTXPerspective(GC_Mtx m, f32 fovY, f32 aspect, f32 n, f32 f)
{
	f32 angle;
	f32 cot;
	f32 tmp;

	angle   = (0.5f * fovY);
	angle   = angle * 0.017453293f;
	cot     = 1 / tanf(angle);
	m[0][0] = (cot / aspect);
	m[0][1] = 0;
	m[0][2] = 0;
	m[0][3] = 0;
	m[1][0] = 0;
	m[1][1] = (cot);
	m[1][2] = 0;
	m[1][3] = 0;
	m[2][0] = 0;
	m[2][1] = 0;
	tmp     = 1 / (f - n);
	m[2][2] = (-n * tmp);
	m[2][3] = (tmp * -(f * n));
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = -1;
	m[3][3] = 0;
}

void C_MTXOrtho(GC_Mtx m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f)
{
	f32 tmp;

	tmp     = 1 / (r - l);
	m[0][0] = 2 * tmp;
	m[0][1] = 0;
	m[0][2] = 0;
	m[0][3] = (tmp * -(r + l));
	tmp     = 1 / (t - b);
	m[1][0] = 0;
	m[1][1] = 2 * tmp;
	m[1][2] = 0;
	m[1][3] = (tmp * -(t + b));
	m[2][0] = 0;
	m[2][1] = 0;
	tmp     = 1 / (f - n);
	m[2][2] = (-1 * tmp);
	m[2][3] = (-f * tmp);
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
}

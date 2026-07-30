#include <dolphin.h>
#include <dolphin/mtx.h>

#define qr0 0

asm void PSVECAdd(register Vec* a, register Vec* b, register Vec* c)
{
#ifdef __MWERKS__ // clang-format off
	psq_l  f2, Vec.x(a), 0, qr0
	psq_l  f4, Vec.x(b), 0, qr0
	ps_add f6, f2, f4
	psq_st f6, Vec.x(c), 0, qr0
	psq_l  f3, Vec.z(a), 1, qr0
	psq_l  f5, Vec.z(b), 1, qr0
	ps_add f7, f3, f5
	psq_st f7, Vec.z(c), 1, qr0
#endif // clang-format on
}

asm void PSVECSubtract(register Vec* a, register Vec* b, register Vec* c)
{
#ifdef __MWERKS__ // clang-format off
	psq_l  f2, Vec.x(a), 0, qr0
	psq_l  f4, Vec.x(b), 0, qr0
	ps_sub f6, f2, f4
	psq_st f6, Vec.x(c), 0, qr0
	psq_l  f3, Vec.z(a), 1, qr0
	psq_l  f5, Vec.z(b), 1, qr0
	ps_sub f7, f3, f5
	psq_st f7, Vec.z(c), 1, qr0
#endif // clang-format on
}

asm void PSVECScale(register Vec* src, register Vec* dst, register f32 mult)
{
#ifdef __MWERKS__ // clang-format off
	psq_l f0, Vec.x(src), 0, qr0
	psq_l f2, Vec.z(src), 1, qr0
	ps_muls0 f0, f0, f1
	psq_st f0, Vec.x(dst), 0, qr0
	ps_muls0 f0, f2, f1
	psq_st f0, Vec.z(dst), 1, qr0
#endif // clang-format on
}

void PSVECNormalize(const register Vec* vec1, register Vec* dst)
{
	register float c_half  = 0.5f;
	register float c_three = 3.0f;
	register float v1_xy;
	register float v1_z;
	register float xx_zz;
	register float xx_yy;
	register float sqsum;
	register float rsqrt;
	register float nwork0;
	register float nwork1;

#ifdef __MWERKS__ // clang-format off
	asm
	{
		psq_l    v1_xy, Vec.x(vec1), 0, qr0
		ps_mul   xx_yy, v1_xy, v1_xy
		psq_l    v1_z, Vec.z(vec1), 1, qr0
		ps_madd  xx_zz, v1_z, v1_z, xx_yy
		ps_sum0  sqsum, xx_zz, v1_z, xx_yy
		frsqrte  rsqrt, sqsum
		fmuls    nwork0, rsqrt, rsqrt
		fmuls    nwork1, rsqrt, c_half
		fnmsubs  nwork0, nwork0, sqsum, c_three
		fmuls    rsqrt, nwork0, nwork1
		ps_muls0 v1_xy, v1_xy, rsqrt
		psq_st   v1_xy, Vec.x(dst), 0, qr0
		ps_muls0 v1_z, v1_z, rsqrt
		psq_st   v1_z, Vec.z(dst), 1, qr0
	}
#endif // clang-format on
}

asm float PSVECMag(register Vec* v)
{
#ifdef __MWERKS__ // clang-format off
	psq_l   f0, Vec.x(v), 0, qr0
	ps_mul  f0, f0, f0
	lfs     f1, Vec.z(v)
	ps_madd f1, f1, f1, f0
	lfs     f4, 0.5f
	ps_sum0 f1, f1, f0, f0
	frsqrte f0, f1
	lfs     f3, 3.0f
	fmuls   f2, f0, f0
	fmuls   f0, f0, f4
	fnmsubs f2, f2, f1, f3
	fmuls   f0, f2, f0
	fsel    f0, f0, f0, f1
	fmuls   f1, f1, f0
#endif // clang-format on
}

asm f32 PSVECDotProduct(register Vec* vec1, register Vec* vec2)
{
#ifdef __MWERKS__ // clang-format off
	psq_l f2, Vec.y(vec1), 0, qr0
	psq_l f3, Vec.y(vec2), 0, qr0
	ps_mul f2, f2, f3
	psq_l f5, Vec.x(vec1), 0, qr0
	psq_l f4, Vec.x(vec2), 0, qr0
	ps_madd f3, f5, f4, f2
	ps_sum0 f1, f3, f2, f2
#endif // clang-format on
}

asm void PSVECCrossProduct(register Vec* vec1, register Vec* vec2,
                           register Vec* dst)
{
#ifdef __MWERKS__ // clang-format off
	psq_l f1, Vec.x(vec2), 0, qr0
	lfs f2, Vec.z(vec1)
	psq_l f0, Vec.x(vec1), 0, qr0
	ps_merge10 f6, f1, f1
	lfs f3, Vec.z(vec2)
	ps_mul f4, f1, f2
	ps_muls0 f7, f1, f0
	ps_msub f5, f0, f3, f4
	ps_msub f8, f0, f6, f7
	ps_merge11 f9, f5, f5
	ps_merge01 f10, f5, f8
	psq_st f9, Vec.x(dst), 1, qr0
	ps_neg f10, f10
	psq_st f10, Vec.y(dst), 0, qr0
#endif // clang-format on
}

asm f32 PSVECSquareDistance(register Vec* vec1, register Vec* vec2)
{
#ifdef __MWERKS__ // clang-format off
	psq_l f0, Vec.y(vec1), 0, qr0
	psq_l f1, Vec.y(vec2), 0, qr0
	ps_sub f2, f0, f1
	psq_l f0, Vec.x(vec1), 0, qr0
	psq_l f1, Vec.x(vec2), 0, qr0
	ps_mul f2, f2, f2
	ps_sub f0, f0, f1
	ps_madd f1, f0, f0, f2
	ps_sum0 f1, f1, f2, f2
#endif // clang-format on
}

asm f32 PSVECDistance(register Vec* vec1, register Vec* vec2)
{
#ifdef __MWERKS__ // clang-format off
	psq_l   f0, Vec.y(vec1), 0, qr0
	psq_l   f1, Vec.y(vec2), 0, qr0
	ps_sub  f2, f0, f1
	psq_l   f0, Vec.x(vec1), 0, qr0
	psq_l   f1, Vec.x(vec2), 0, qr0
	ps_mul  f2, f2, f2
	ps_sub  f0, f0, f1
	lfs     f3, 0.5f
	ps_madd f0, f0, f0, f2
	ps_sum0 f0, f0, f2, f2
	lfs     f4, 3.0f
	frsqrte f1, f0
	fmuls   f2, f1, f1
	fmuls   f1, f1, f3
	fnmsubs f2, f2, f0, f4
	fmuls   f1, f2, f1
	fsel    f1, f1, f1, f0
	fmuls   f1, f0, f1
#endif // clang-format on
}

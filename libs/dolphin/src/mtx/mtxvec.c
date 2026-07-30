#include <dolphin.h>
#include <dolphin/mtx.h>

#define qr0 0

asm void PSMTXMultVec(const register Mtx44 m, const register Vec* src, register Vec* dst)
{
#ifdef __MWERKS__ // clang-format off
	nofralloc
	psq_l f0, Vec.x(src), 0, qr0
	psq_l f2, 0(m), 0, qr0
	psq_l f1, Vec.z(src), 1, qr0
	ps_mul f4, f2, f0
	psq_l f3, 8(m), 0, qr0
	ps_madd f5, f3, f1, f4
	psq_l f8, 16(m), 0, qr0
	ps_sum0 f6, f5, f6, f5
	psq_l f9, 24(m), 0, qr0
	ps_mul f10, f8, f0
	psq_st f6, Vec.x(dst), 1, qr0
	ps_madd f11, f9, f1, f10
	psq_l f2, 32(m), 0, qr0
	ps_sum0 f12, f11, f12, f11
	psq_l f3, 40(m), 0, qr0
	ps_mul f4, f2, f0
	psq_st f12, Vec.y(dst), 1, qr0
	ps_madd f5, f3, f1, f4
	ps_sum0 f6, f5, f6, f5
	psq_st f6, Vec.z(dst), 1, qr0
	blr
#endif // clang-format on
}

asm void PSMTXMultVecArray(const register GC_Mtx m, const register Vec* srcBase,
                           register Vec* dstBase, register u32 count)
{
#ifdef __MWERKS__ // clang-format off
	psq_l      f13, 0x0(m), 0, qr0
	psq_l      f12, 0x10(m), 0, qr0
	subi       count, count, 0x1
	psq_l      f11, 0x8(m), 0, qr0
	ps_merge00 f0, f13, f12
	subi       dstBase, dstBase, 0x4
	psq_l      f10, 0x18(m), 0, qr0
	ps_merge11 f1, f13, f12

	mtctr count
	psq_l      f4, 0x20(m), 0, qr0
	ps_merge00 f2, f11, f10
	psq_l      f5, 0x28(m), 0, qr0
	ps_merge11 f3, f11, f10
	psq_l      f6, Vec.x(srcBase), 0, qr0
	psq_lu     f7, Vec.z(srcBase), 1, qr0
	ps_madds0  f8, f0, f6, f3
	ps_mul     f9, f4, f6
	ps_madds1  f8, f1, f6, f8
	ps_madd    f10, f5, f7, f9

loop:
	psq_lu    f6, Vec.y(srcBase), 0, qr0
	ps_madds0 f12, f2, f7, f8
	psq_lu    f7, Vec.z(srcBase), 1, qr0
	ps_sum0   f13, f10, f9, f10
	ps_madds0 f8, f0, f6, f3
	ps_mul    f9, f4, f6
	psq_stu   f12, 0x4(dstBase), 0, qr0
	ps_madds1 f8, f1, f6, f8
	psq_stu   f13, 0x8(dstBase), 1, qr0
	ps_madd   f10, f5, f7, f9
	bdnz loop

	ps_madds0 f12, f2, f7, f8
	ps_sum0   f13, f10, f9, f10
	psq_stu   f12, 0x4(dstBase), 0, qr0
	psq_stu   f13, 0x8(dstBase), 1, qr0
#endif // clang-format on
}

asm void PSMTXMultVecSR(const register Mtx44 m, const register Vec* src, register Vec* dst)
{
#ifdef __MWERKS__ // clang-format off
	psq_l   f0, 0x0(m), 0, qr0
	psq_l   f6, Vec.x(src), 0, qr0
	psq_l   f2, 0x10(m), 0, qr0
	ps_mul  f8, f0, f6
	psq_l   f4, 0x20(m), 0, qr0
	ps_mul  f10, f2, f6
	psq_l   f7, Vec.z(src), 1, qr0
	ps_mul  f12, f4, f6
	psq_l   f3, 0x18(m), 0, qr0
	ps_sum0 f8, f8, f8, f8
	psq_l   f5, 0x28(m), 0, qr0
	ps_sum0 f10, f10, f10, f10
	psq_l   f1, 0x8(m), 0, qr0
	ps_sum0 f12, f12, f12, f12
	ps_madd f9, f1, f7, f8
	psq_st  f9, Vec.x(dst), 1, qr0
	ps_madd f11, f3, f7, f10
	psq_st  f11, Vec.y(dst), 1, qr0
	ps_madd f13, f5, f7, f12
	psq_st  f13, Vec.z(dst), 1, qr0
#endif // clang-format on
}

#include <dolphin.h>
#include <dolphin/mtx.h>
#include <macros.h>

#define qr0 0

// unsorted externs
extern f32 sinf(f32);
extern f32 cosf(f32);
extern f32 tanf(f32);

// .sbss
static float Unit01[2] = { 0.0f, 1.0f };

// MEME: if this function is not here, 0.0f and 1.0f have wrong order in .sdata2
void C_MTXIdentity(GC_Mtx mtx)
{
	mtx[0][0] = 1.0f;
	mtx[0][1] = 0.0f;
	mtx[0][2] = 0.0f;
	mtx[1][0] = 0.0f;
	mtx[1][1] = 1.0f;
	mtx[1][2] = 0.0f;
	mtx[2][0] = 0.0f;
	mtx[2][1] = 0.0f;
	mtx[2][2] = 1.0f;
}

void PSMTXIdentity(register GC_Mtx m)
{
	register f32 c_zero = 0.0f;
	register f32 c_one  = 1.0f;
	register f32 c_01;
	register f32 c_10;

#ifdef __MWERKS__ // clang-format off
	asm {
		psq_st c_zero, 8(m), 0, qr0
		ps_merge01 c_01, c_zero, c_one
		psq_st c_zero, 24(m), 0, qr0
		ps_merge10 c_10, c_one, c_zero
		psq_st c_zero, 32(m), 0, qr0
		psq_st c_01, 16(m), 0, qr0
		psq_st c_10, 0(m), 0, qr0
		psq_st c_10, 40(m), 0, qr0
	}
#endif // clang-format on
}

asm void PSMTXCopy(const register GC_Mtx src, register GC_Mtx dst)
{
#ifdef __MWERKS__ // clang-format off
	psq_l f0, 0(src), 0, qr0
	psq_st f0, 0(dst), 0, qr0
	psq_l f1, 8(src), 0, qr0
	psq_st f1, 8(dst), 0, qr0
	psq_l f2, 16(src), 0, qr0
	psq_st f2, 16(dst), 0, qr0
	psq_l f3, 24(src), 0, qr0
	psq_st f3, 24(dst), 0, qr0
	psq_l f4, 32(src), 0, qr0
	psq_st f4, 32(dst), 0, qr0
	psq_l f5, 40(src), 0, qr0
	psq_st f5, 40(dst), 0, qr0
#endif // clang-format on
}

asm void PSMTXConcat(const register GC_Mtx mA, const register GC_Mtx mB, register GC_Mtx mAB)
{
#ifdef __MWERKS__ // clang-format off
	nofralloc
	stwu r1, -64(r1)
	psq_l f0, 0(mA), 0, qr0
	stfd f14, 8(r1)
	psq_l f6, 0(mB), 0, qr0
	lis r6, Unit01@ha
	psq_l f7, 8(mB), 0, qr0
	stfd f15, 16(r1)
	addi r6, r6, Unit01@l
	stfd f31, 40(r1)
	psq_l f8, 16(mB), 0, qr0
	ps_muls0 f12, f6, f0
	psq_l f2, 16(mA), 0, qr0
	ps_muls0 f13, f7, f0
	psq_l f31, 0(r6), 0, qr0
	ps_muls0 f14, f6, f2
	psq_l f9, 24(mB), 0, qr0
	ps_muls0 f15, f7, f2
	psq_l f1, 8(mA), 0, qr0
	ps_madds1 f12, f8, f0, f12
	psq_l f3, 24(mA), 0, qr0
	ps_madds1 f14, f8, f2, f14
	psq_l f10, 32(mB), 0, qr0
	ps_madds1 f13, f9, f0, f13
	psq_l f11, 40(mB), 0, qr0
	ps_madds1 f15, f9, f2, f15
	psq_l f4, 32(mA), 0, qr0
	psq_l f5, 40(mA), 0, qr0
	ps_madds0 f12, f10, f1, f12
	ps_madds0 f13, f11, f1, f13
	ps_madds0 f14, f10, f3, f14
	ps_madds0 f15, f11, f3, f15
	psq_st f12, 0(mAB), 0, qr0
	ps_muls0 f2, f6, f4
	ps_madds1 f13, f31, f1, f13
	ps_muls0 f0, f7, f4
	psq_st f14, 16(mAB), 0, qr0
	ps_madds1 f15, f31, f3, f15
	psq_st f13, 8(mAB), 0, qr0
	ps_madds1 f2, f8, f4, f2
	ps_madds1 f0, f9, f4, f0
	ps_madds0 f2, f10, f5, f2
	lfd f14, 8(r1)
	psq_st f15, 24(mAB), 0, qr0
	ps_madds0 f0, f11, f5, f0
	psq_st f2, 32(mAB), 0, qr0
	ps_madds1 f0, f31, f5, f0
	lfd f15, 16(r1)
	psq_st f0, 40(mAB), 0, qr0
	lfd f31, 40(r1)
	addi r1, r1, 64
	blr
#endif // clang-format on
}

asm u32 PSMTXInverse(const register GC_Mtx src, register GC_Mtx inv)
{
#ifdef __MWERKS__ // clang-format off
	psq_l f0, 0(src), 1, qr0
	psq_l f1, 4(src), 0, qr0
	psq_l f2, 16(src), 1, qr0
	ps_merge10 f6, f1, f0
	psq_l f3, 20(src), 0, qr0
	psq_l f4, 32(src), 1, qr0
	ps_merge10 f7, f3, f2
	psq_l f5, 36(src), 0, qr0
	ps_mul f11, f3, f6
	ps_mul f13, f5, f7
	ps_merge10 f8, f5, f4
	ps_msub f11, f1, f7, f11
	ps_mul f12, f1, f8
	ps_msub f13, f3, f8, f13
	ps_mul f10, f3, f4
	ps_msub f12, f5, f6, f12
	ps_mul f9, f0, f5
	ps_mul f8, f1, f2
	ps_sub f6, f6, f6
	ps_msub f10, f2, f5, f10
	ps_mul f7, f0, f13
	ps_msub f9, f1, f4, f9
	ps_madd f7, f2, f12, f7
	ps_msub f8, f0, f3, f8
	ps_madd f7, f4, f11, f7
	ps_cmpo0 cr0, f7, f6
	bne skip_return
	li r3, 0
	blr
skip_return:
	fres f0, f7
	ps_add f6, f0, f0
	ps_mul f5, f0, f0
	ps_nmsub f0, f7, f5, f6
	lfs f1, 12(src)
	ps_muls0 f13, f13, f0
	lfs f2, 28(src)
	ps_muls0 f12, f12, f0
	lfs f3, 44(src)
	ps_muls0 f11, f11, f0
	ps_merge00 f5, f13, f12
	ps_muls0 f10, f10, f0
	ps_merge11 f4, f13, f12
	ps_muls0 f9, f9, f0
	psq_st f5, 0(inv), 0, qr0
	ps_mul f6, f13, f1
	psq_st f4, 16(inv), 0, qr0
	ps_muls0 f8, f8, f0
	ps_madd f6, f12, f2, f6
	psq_st f10, 32(inv), 1, qr0
	ps_nmadd f6, f11, f3, f6
	psq_st f9, 36(inv), 1, qr0
	ps_mul f7, f10, f1
	ps_merge00 f5, f11, f6
	psq_st f8, 40(inv), 1, qr0
	ps_merge11 f4, f11, f6
	psq_st f5, 8(inv), 0, qr0
	ps_madd f7, f9, f2, f7
	psq_st f4, 24(inv), 0, qr0
	ps_nmadd f7, f8, f3, f7
	li r3, 1
	psq_st f7, 44(inv), 1, qr0
#endif // clang-format on
}

void PSMTXRotRad(GC_Mtx m, char axis, f32 rad)
{
	f32 s = sinf(rad);
	f32 c = cosf(rad);

	PSMTXRotTrig(m, axis, s, c);
}

void PSMTXRotTrig(register GC_Mtx m, register char axis, register f32 sinA,
                  register f32 cosA)
{
	register f32 fc0;
	register f32 fc1;
	register f32 nsinA;
	register f32 fw0, fw1, fw2, fw3;

	fc0 = 0.0f;
	fc1 = 1.0f;

#ifdef __MWERKS__ // clang-format off
  asm {
    ori         axis, axis, 0x20
    ps_neg      nsinA, sinA
    cmplwi      axis, 'x'
    beq         _case_x
    cmplwi      axis, 'y'
    beq         _case_y
    cmplwi      axis, 'z'
    beq         _case_z
    b           _end

_case_x:
    psq_st      fc1,  0(m), 1, qr0
    psq_st      fc0,  4(m), 0, qr0
    ps_merge00  fw0, sinA, cosA
    psq_st      fc0, 12(m), 0, qr0
    ps_merge00  fw1, cosA, nsinA
    psq_st      fc0, 28(m), 0, qr0
    psq_st      fc0, 44(m), 1, qr0
    psq_st      fw0, 36(m), 0, qr0
    psq_st      fw1, 20(m), 0, qr0
    b           _end;

_case_y:
    ps_merge00  fw0, cosA, fc0
    ps_merge00  fw1, fc0, fc1
    psq_st      fc0, 24(m), 0, qr0
    psq_st      fw0,  0(m), 0, qr0
    ps_merge00  fw2, nsinA, fc0
    ps_merge00  fw3, sinA, fc0
    psq_st      fw0, 40(m), 0, qr0
    psq_st      fw1, 16(m), 0, qr0
    psq_st      fw3,  8(m), 0, qr0
    psq_st      fw2, 32(m), 0, qr0
    b           _end;

_case_z:
    psq_st      fc0,  8(m), 0, qr0
    ps_merge00  fw0, sinA, cosA
    ps_merge00  fw2, cosA, nsinA
    psq_st      fc0, 24(m), 0, qr0
    psq_st      fc0, 32(m), 0, qr0
    ps_merge00  fw1, fc1, fc0
    psq_st      fw0, 16(m), 0, qr0
    psq_st      fw2,  0(m), 0, qr0
    psq_st      fw1, 40(m), 0, qr0

_end:
  }
#endif // clang-format on
}

static inline void __PSMTXRotAxisRadInternal(register GC_Mtx m,
                                             const register Vec* axis,
                                             register f32 sT, register f32 cT)
{
}

void PSMTXRotAxisRad(register GC_Mtx m, const Vec* axis, register f32 rad)
{
	register f32 tmp0, tmp1, tmp2, tmp3, tmp4;
	register f32 tmp5, tmp6, tmp7, tmp8, tmp9;

	register f32 sT;
	register f32 cT;
	register f32 oneMinusCosT;
	register f32 zero;
	Vec axisNormalized;
	register Vec* axisNormalizedPtr;

	zero              = 0.0f;
	axisNormalizedPtr = &axisNormalized;
	sT                = sinf(rad);
	cT                = cosf(rad);
	oneMinusCosT      = 1.0f - cT;

	PSVECNormalize(axis, axisNormalizedPtr);

	// `rad` reused here -- absolutely disgusting.
	// Also might've been an inline as in prime.
#ifdef __MWERKS__ // clang-format off
  asm {
		psq_l rad, 0x0(axisNormalizedPtr), 0, qr0
		lfs tmp1, 0x8(axisNormalizedPtr)
		ps_merge00 tmp0, cT, cT
		ps_muls0   tmp4, rad, oneMinusCosT
		ps_muls0   tmp5, tmp1, oneMinusCosT
		ps_muls1   tmp3, tmp4, rad
		ps_muls0   tmp2, tmp4, rad
		ps_muls0   rad, rad, sT
		ps_muls0   tmp4, tmp4, tmp1
		fnmsubs    tmp6, tmp1, sT, tmp3
		fmadds     tmp7, tmp1, sT, tmp3
		ps_neg     tmp9, rad
		ps_sum0    tmp8, tmp4, zero, rad
		ps_sum0    tmp2, tmp2, tmp6, tmp0
		ps_sum1    tmp3, tmp0, tmp7, tmp3
		ps_sum0    tmp6, tmp9, zero, tmp4
		ps_sum0    tmp9, tmp4, tmp4, tmp9
		psq_st     tmp8, 0x8(m), 0, qr0
		ps_muls0   tmp5, tmp5, tmp1
		psq_st     tmp2, 0x0(m), 0, qr0
		ps_sum1    tmp4, rad, tmp9, tmp4
		psq_st     tmp3, 0x10(m), 0, qr0
		ps_sum0    tmp5, tmp5, zero, tmp0
		psq_st     tmp6, 0x18(m), 0, qr0
		psq_st     tmp4, 0x20(m), 0, qr0
		psq_st     tmp5, 0x28(m), 0, qr0
  }
#endif // clang-format on
}

void PSMTXTrans(register GC_Mtx m, register f32 xT, register f32 yT,
                register f32 zT)
{
	register f32 c0 = 0.0F;
	register f32 c1 = 1.0F;
#ifdef __MWERKS__ // clang-format off
	asm {
		stfs        xT,     12(m)
		stfs        yT,     28(m)
		psq_st      c0,      4(m), 0, qr0
		psq_st      c0,     32(m), 0, qr0
		stfs        c0,     16(m)
		stfs        c1,     20(m)
		stfs        c0,     24(m)
		stfs        c1,     40(m)
		stfs        zT,     44(m)
		stfs        c1,      0(m)
	}
#endif // clang-format on
}

asm void PSMTXTransApply(const register GC_Mtx src, register GC_Mtx dst, register f32 xT,
                         register f32 yT, register f32 zT)
{
#ifdef __MWERKS__ // clang-format off
	nofralloc
	psq_l       fp4, 0(src),        0, qr0
	psq_l       fp5, 8(src),        0, qr0
	psq_l       fp7, 24(src),       0, qr0
	psq_l       fp8, 40(src),       0, qr0
	ps_sum1     fp5, xT, fp5, fp5
	psq_l       fp6, 16(src),       0, qr0
	ps_sum1     fp7, yT, fp7, fp7
	psq_l       fp9, 32(src),       0, qr0
	ps_sum1     fp8, zT, fp8, fp8

	psq_st      fp4, 0(dst),        0, qr0
	psq_st      fp5, 8(dst),        0, qr0
	psq_st      fp6, 16(dst),       0, qr0
	psq_st      fp7, 24(dst),       0, qr0
	psq_st      fp9, 32(dst),       0, qr0
	psq_st      fp8, 40(dst),       0, qr0
	blr
#endif // clang-format on
}

void PSMTXScale(register GC_Mtx m, register f32 xS, register f32 yS,
                register f32 zS)
{
	register f32 c0 = 0.0F;
#ifdef __MWERKS__ // clang-format off
	asm {
		stfs        xS,      0(m)
		psq_st      c0,      4(m), 0, 0
		psq_st      c0,     12(m), 0, 0
		stfs        yS,     20(m)
		psq_st      c0,     24(m), 0, 0
		psq_st      c0,     32(m), 0, 0
		stfs        zS,     40(m)
		stfs        c0,     44(m)
	}
#endif // clang-format on
}

asm void PSMTXScaleApply(const register GC_Mtx src, register GC_Mtx dst, register f32 xS,
                         register f32 yS, register f32 zS)
{
#ifdef __MWERKS__ // clang-format off
  nofralloc
  psq_l       fp4, 0(src),        0, 0
  psq_l       fp5, 8(src),        0, 0
  ps_muls0    fp4, fp4, xS
  psq_l       fp6, 16(src),       0, 0
  ps_muls0    fp5, fp5, xS
  psq_l       fp7, 24(src),       0, 0
  ps_muls0    fp6, fp6, yS
  psq_l       fp8, 32(src),       0, 0
  psq_st      fp4, 0(dst),        0, 0
  ps_muls0    fp7, fp7, yS
  psq_l       fp2, 40(src),       0, 0
  psq_st      fp5, 8(dst),        0, 0
  ps_muls0    fp8, fp8, zS
  psq_st      fp6, 16(dst),       0, 0
  ps_muls0    fp2, fp2, zS
  psq_st      fp7, 24(dst),       0, 0
  psq_st      fp8, 32(dst),       0, 0
  psq_st      fp2, 40(dst),       0, 0
  blr
#endif // clang-format on
}

void PSMTXQuat(register GC_Mtx m, const register PSQuaternion* q)
{
	register f32 c_zero, c_one, c_two, scale;
	register f32 tmp0, tmp1, tmp2, tmp3, tmp4;
	register f32 tmp5, tmp6, tmp7, tmp8, tmp9;

	c_one = 1.0F;
#ifdef __MWERKS__ // clang-format off
	asm {
		psq_l       tmp0, 0(q), 0, 0
		psq_l       tmp1, 8(q), 0, 0
		fsubs       c_zero, c_one, c_one
		fadds       c_two, c_one, c_one
		ps_mul      tmp2, tmp0, tmp0
		ps_merge10  tmp5, tmp0, tmp0
		ps_madd     tmp4, tmp1, tmp1, tmp2
		ps_mul      tmp3, tmp1, tmp1
		ps_sum0     scale, tmp4, tmp4, tmp4
		ps_muls1    tmp7, tmp5, tmp1
		fres        tmp9, scale
		ps_sum1     tmp4, tmp3, tmp4, tmp2
		ps_nmsub    scale, scale, tmp9, c_two
		ps_muls1    tmp6, tmp1, tmp1
		ps_mul      scale, tmp9, scale
		ps_sum0     tmp2, tmp2, tmp2, tmp2
		fmuls       scale, scale, c_two
		ps_madd     tmp8, tmp0, tmp5, tmp6
		ps_msub     tmp6, tmp0, tmp5, tmp6
		psq_st      c_zero, 12(m), 1, 0
		ps_nmsub    tmp2, tmp2, scale, c_one
		ps_nmsub    tmp4, tmp4, scale, c_one
		psq_st      c_zero, 44(m), 1, 0
		ps_mul      tmp8, tmp8, scale
		ps_mul      tmp6, tmp6, scale
		psq_st      tmp2, 40(m), 1, 0
		ps_madds0   tmp5, tmp0, tmp1, tmp7
		ps_merge00  tmp1, tmp8, tmp4
		ps_nmsub    tmp7, tmp7, c_two, tmp5
		ps_merge10  tmp0, tmp4, tmp6
		psq_st      tmp1, 16(m), 0, 0
		ps_mul      tmp5, tmp5, scale
		ps_mul      tmp7, tmp7, scale
		psq_st      tmp0,  0(m), 0, 0
		psq_st      tmp5,  8(m), 1, 0
		ps_merge10  tmp3, tmp7, c_zero
		ps_merge01  tmp9, tmp7, tmp5
		psq_st      tmp3, 24(m), 0, 0
		psq_st      tmp9, 32(m), 0, 0
	}
#endif // clang-format on
}

void C_MTXLookAt(GC_Mtx m, const Vec* camPos, const Vec* camUp, const Vec* target) {
    Vec vLook;
    Vec vRight;
    Vec vUp;

    ASSERTMSGLINE(2105, m, "MTXLookAt():  NULL MtxPtr 'm' ");
    ASSERTMSGLINE(2106, camPos, "MTXLookAt():  NULL VecPtr 'camPos' ");
    ASSERTMSGLINE(2107, camUp, "MTXLookAt():  NULL VecPtr 'camUp' ");
    ASSERTMSGLINE(2108, target, "MTXLookAt():  NULL Point3dPtr 'target' ");

    vLook.x = camPos->x - target->x;
    vLook.y = camPos->y - target->y;
    vLook.z = camPos->z - target->z;
    VECNormalize(&vLook, &vLook);
    VECCrossProduct(camUp, &vLook, &vRight);
    VECNormalize(&vRight, &vRight);
    VECCrossProduct(&vLook, &vRight, &vUp);
    m[0][0] = vRight.x;
    m[0][1] = vRight.y;
    m[0][2] = vRight.z;
    m[0][3] = -((camPos->z * vRight.z) + ((camPos->x * vRight.x) + (camPos->y * vRight.y)));
    m[1][0] = vUp.x;
    m[1][1] = vUp.y;
    m[1][2] = vUp.z;
    m[1][3] = -((camPos->z * vUp.z) + ((camPos->x * vUp.x) + (camPos->y * vUp.y)));
    m[2][0] = vLook.x;
    m[2][1] = vLook.y;
    m[2][2] = vLook.z;
    m[2][3] = -((camPos->z * vLook.z) + ((camPos->x * vLook.x) + (camPos->y * vLook.y)));
}

void C_MTXLightFrustum(GC_Mtx m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 scaleS,
                       f32 scaleT, f32 transS, f32 transT)
{
	f32 _tmp;

	_tmp    = 1 / (r - l);
	m[0][0] = (scaleS * (2 * n * _tmp));
	m[0][1] = 0;
	m[0][2] = (scaleS * (_tmp * (r + l))) - transS;
	m[0][3] = 0;
	_tmp    = 1 / (t - b);
	m[1][0] = 0;
	m[1][1] = (scaleT * (2 * n * _tmp));
	m[1][2] = (scaleT * (_tmp * (t + b))) - transT;
	m[1][3] = 0;
	m[2][0] = 0;
	m[2][1] = 0;
	m[2][2] = -1;
	m[2][3] = 0;
}

void C_MTXLightPerspective(GC_Mtx m, f32 fovY, f32 aspect, f32 scaleS, f32 scaleT,
                           f32 transS, f32 transT)
{
	f32 angle;
	f32 cot;

	angle   = (0.5f * fovY);
	angle   = angle * 0.017453293f;
	cot     = 1 / tanf(angle);
	m[0][0] = (scaleS * (cot / aspect));
	m[0][1] = 0;
	m[0][2] = -transS;
	m[0][3] = 0;
	m[1][0] = 0;
	m[1][1] = (cot * scaleT);
	m[1][2] = -transT;
	m[1][3] = 0;
	m[2][0] = 0;
	m[2][1] = 0;
	m[2][2] = -1;
	m[2][3] = 0;
}

void C_MTXLightOrtho(GC_Mtx m, f32 t, f32 b, f32 l, f32 r, f32 scaleS, f32 scaleT,
                     f32 transS, f32 transT)
{
	f32 _tmp;

	_tmp    = 1 / (r - l);
	m[0][0] = (2 * _tmp * scaleS);
	m[0][1] = 0;
	m[0][2] = 0;
	m[0][3] = (transS + (scaleS * (_tmp * -(r + l))));
	_tmp    = 1 / (t - b);
	m[1][0] = 0;
	m[1][1] = (2 * _tmp * scaleT);
	m[1][2] = 0;
	m[1][3] = (transT + (scaleT * (_tmp * -(t + b))));
	m[2][0] = 0;
	m[2][1] = 0;
	m[2][2] = 0;
	m[2][3] = 1;
}

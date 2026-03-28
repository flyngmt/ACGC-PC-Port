/* pc_mtx.c - C replacements for PPC paired-singles matrix/vector math */
#include "pc_platform.h"
#include <math.h>

typedef f32 Mtx34[3][4];
typedef f32 Mtx44[4][4];
typedef f32 (*MtxP)[4];

typedef struct { f32 x, y, z; } Vec;

typedef s32 Mtx_t[4][4];
typedef union {
    Mtx_t m;
    long long int force_structure_alignment;
} Mtx ATTRIBUTE_ALIGN(8);

#define FTOFIX32(x) (s32)((x) * (float)0x00010000)

/* --- Dolphin PS* matrix functions (3x4 row-major) --- */

void PSMTXIdentity(MtxP m) {
    m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
    m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
    m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
}

void C_MTXIdentity(MtxP m) {
    PSMTXIdentity(m);
}

void PSMTXCopy(const MtxP src, MtxP dst) {
    memcpy(dst, src, 12 * sizeof(f32));
}

void PSMTXConcat(const MtxP a, const MtxP b, MtxP result) {
    f32 tmp[3][4];
    for (int i = 0; i < 3; i++) {
        tmp[i][0] = a[i][0]*b[0][0] + a[i][1]*b[1][0] + a[i][2]*b[2][0];
        tmp[i][1] = a[i][0]*b[0][1] + a[i][1]*b[1][1] + a[i][2]*b[2][1];
        tmp[i][2] = a[i][0]*b[0][2] + a[i][1]*b[1][2] + a[i][2]*b[2][2];
        tmp[i][3] = a[i][0]*b[0][3] + a[i][1]*b[1][3] + a[i][2]*b[2][3] + a[i][3];
    }
    memcpy(result, tmp, 12 * sizeof(f32));
}

void PSMTXInverse(const MtxP src, MtxP inv) {
    f32 det = src[0][0] * (src[1][1]*src[2][2] - src[1][2]*src[2][1])
            - src[0][1] * (src[1][0]*src[2][2] - src[1][2]*src[2][0])
            + src[0][2] * (src[1][0]*src[2][1] - src[1][1]*src[2][0]);

    if (fabsf(det) < 1e-25f) {
        PSMTXIdentity(inv);
        return;
    }

    f32 invDet = 1.0f / det;

    f32 tmp[3][4];
    tmp[0][0] = (src[1][1]*src[2][2] - src[1][2]*src[2][1]) * invDet;
    tmp[0][1] = (src[0][2]*src[2][1] - src[0][1]*src[2][2]) * invDet;
    tmp[0][2] = (src[0][1]*src[1][2] - src[0][2]*src[1][1]) * invDet;
    tmp[1][0] = (src[1][2]*src[2][0] - src[1][0]*src[2][2]) * invDet;
    tmp[1][1] = (src[0][0]*src[2][2] - src[0][2]*src[2][0]) * invDet;
    tmp[1][2] = (src[0][2]*src[1][0] - src[0][0]*src[1][2]) * invDet;
    tmp[2][0] = (src[1][0]*src[2][1] - src[1][1]*src[2][0]) * invDet;
    tmp[2][1] = (src[0][1]*src[2][0] - src[0][0]*src[2][1]) * invDet;
    tmp[2][2] = (src[0][0]*src[1][1] - src[0][1]*src[1][0]) * invDet;

    tmp[0][3] = -(tmp[0][0]*src[0][3] + tmp[0][1]*src[1][3] + tmp[0][2]*src[2][3]);
    tmp[1][3] = -(tmp[1][0]*src[0][3] + tmp[1][1]*src[1][3] + tmp[1][2]*src[2][3]);
    tmp[2][3] = -(tmp[2][0]*src[0][3] + tmp[2][1]*src[1][3] + tmp[2][2]*src[2][3]);

    memcpy(inv, tmp, 12 * sizeof(f32));
}

void PSMTXMultVec(const MtxP m, const Vec* src, Vec* dst) {
    f32 x = m[0][0]*src->x + m[0][1]*src->y + m[0][2]*src->z + m[0][3];
    f32 y = m[1][0]*src->x + m[1][1]*src->y + m[1][2]*src->z + m[1][3];
    f32 z = m[2][0]*src->x + m[2][1]*src->y + m[2][2]*src->z + m[2][3];
    dst->x = x; dst->y = y; dst->z = z;
}

void PSMTXMultVecSR(const MtxP m, const Vec* src, Vec* dst) {
    f32 x = m[0][0]*src->x + m[0][1]*src->y + m[0][2]*src->z;
    f32 y = m[1][0]*src->x + m[1][1]*src->y + m[1][2]*src->z;
    f32 z = m[2][0]*src->x + m[2][1]*src->y + m[2][2]*src->z;
    dst->x = x; dst->y = y; dst->z = z;
}

void PSMTXMultVecArray(const MtxP m, const Vec* srcBase, Vec* dstBase, u32 count) {
    for (u32 i = 0; i < count; i++) {
        PSMTXMultVec(m, &srcBase[i], &dstBase[i]);
    }
}

void PSMTXScale(MtxP m, f32 sx, f32 sy, f32 sz) {
    m[0][0] = sx;   m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
    m[1][0] = 0.0f; m[1][1] = sy;   m[1][2] = 0.0f; m[1][3] = 0.0f;
    m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = sz;   m[2][3] = 0.0f;
}

void PSMTXTrans(MtxP m, f32 tx, f32 ty, f32 tz) {
    m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = tx;
    m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = ty;
    m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = tz;
}

void PSMTXTransApply(const MtxP src, MtxP dst, f32 tx, f32 ty, f32 tz) {
    if (src != dst) PSMTXCopy(src, dst);
    dst[0][3] += tx;
    dst[1][3] += ty;
    dst[2][3] += tz;
}

void PSMTXScaleApply(const MtxP src, MtxP dst, f32 sx, f32 sy, f32 sz) {
    for (int j = 0; j < 4; j++) {
        dst[0][j] = src[0][j] * sx;
        dst[1][j] = src[1][j] * sy;
        dst[2][j] = src[2][j] * sz;
    }
}

void PSVECNormalize(const Vec* src, Vec* dst) {
    f32 mag = sqrtf(src->x*src->x + src->y*src->y + src->z*src->z);
    if (mag > 0.0f) {
        f32 inv = 1.0f / mag;
        dst->x = src->x * inv;
        dst->y = src->y * inv;
        dst->z = src->z * inv;
    } else {
        dst->x = dst->y = dst->z = 0.0f;
    }
}

void PSVECCrossProduct(const Vec* a, const Vec* b, Vec* dst) {
    f32 x = a->y * b->z - a->z * b->y;
    f32 y = a->z * b->x - a->x * b->z;
    f32 z = a->x * b->y - a->y * b->x;
    dst->x = x; dst->y = y; dst->z = z;
}

f32 PSVECDotProduct(const Vec* a, const Vec* b) {
    return a->x*b->x + a->y*b->y + a->z*b->z;
}

f32 PSVECMag(const Vec* v) {
    return sqrtf(v->x*v->x + v->y*v->y + v->z*v->z);
}

/* --- C_MTX functions (4x4 projection matrices) --- */

void C_MTXFrustum(Mtx44 m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f) {
    f32 tmp;
    tmp     = 1.0f / (r - l);
    m[0][0] = (2.0f * n) * tmp;
    m[0][1] = 0.0f;
    m[0][2] = (r + l) * tmp;
    m[0][3] = 0.0f;
    tmp     = 1.0f / (t - b);
    m[1][0] = 0.0f;
    m[1][1] = (2.0f * n) * tmp;
    m[1][2] = (t + b) * tmp;
    m[1][3] = 0.0f;
    m[2][0] = 0.0f;
    m[2][1] = 0.0f;
    tmp     = 1.0f / (f - n);
    m[2][2] = -(n) * tmp;
    m[2][3] = -(f * n) * tmp;
    m[3][0] = 0.0f;
    m[3][1] = 0.0f;
    m[3][2] = -1.0f;
    m[3][3] = 0.0f;
}

void C_MTXPerspective(Mtx44 m, f32 fovY, f32 aspect, f32 n, f32 f) {
    f32 angle = 0.5f * fovY * PC_DEG_TO_RADf;
    f32 cot = 1.0f / tanf(angle);
    f32 tmp = 1.0f / (f - n);
    m[0][0] = cot / aspect;
    m[0][1] = 0.0f;
    m[0][2] = 0.0f;
    m[0][3] = 0.0f;
    m[1][0] = 0.0f;
    m[1][1] = cot;
    m[1][2] = 0.0f;
    m[1][3] = 0.0f;
    m[2][0] = 0.0f;
    m[2][1] = 0.0f;
    m[2][2] = -n * tmp;
    m[2][3] = -(f * n) * tmp;
    m[3][0] = 0.0f;
    m[3][1] = 0.0f;
    m[3][2] = -1.0f;
    m[3][3] = 0.0f;
}

void C_MTXOrtho(Mtx44 m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f) {
    f32 tmp;
    tmp     = 1.0f / (r - l);
    m[0][0] = 2.0f * tmp;
    m[0][1] = 0.0f;
    m[0][2] = 0.0f;
    m[0][3] = -(r + l) * tmp;
    tmp     = 1.0f / (t - b);
    m[1][0] = 0.0f;
    m[1][1] = 2.0f * tmp;
    m[1][2] = 0.0f;
    m[1][3] = -(t + b) * tmp;
    tmp     = 1.0f / (f - n);
    m[2][0] = 0.0f;
    m[2][1] = 0.0f;
    m[2][2] = -1.0f * tmp;
    m[2][3] = -n * tmp;
    m[3][0] = 0.0f;
    m[3][1] = 0.0f;
    m[3][2] = 0.0f;
    m[3][3] = 1.0f;
}

void C_MTXLookAt(MtxP m, const Vec* camPos, const Vec* camUp, const Vec* target) {
    Vec look, right, up;

    look.x = camPos->x - target->x;
    look.y = camPos->y - target->y;
    look.z = camPos->z - target->z;
    PSVECNormalize(&look, &look);

    PSVECCrossProduct(camUp, &look, &right);
    PSVECNormalize(&right, &right);

    PSVECCrossProduct(&look, &right, &up);

    m[0][0] = right.x; m[0][1] = right.y; m[0][2] = right.z;
    m[0][3] = -(camPos->x*right.x + camPos->y*right.y + camPos->z*right.z);
    m[1][0] = up.x;    m[1][1] = up.y;    m[1][2] = up.z;
    m[1][3] = -(camPos->x*up.x + camPos->y*up.y + camPos->z*up.z);
    m[2][0] = look.x;  m[2][1] = look.y;  m[2][2] = look.z;
    m[2][3] = -(camPos->x*look.x + camPos->y*look.y + camPos->z*look.z);
}

void C_MTXLightPerspective(MtxP m, f32 fovY, f32 aspect, f32 scaleS, f32 scaleT, f32 transS, f32 transT) {
    f32 angle = 0.5f * fovY * PC_DEG_TO_RADf;
    f32 cot = 1.0f / tanf(angle);

    m[0][0] = (cot / aspect) * scaleS;
    m[0][1] = 0.0f;
    m[0][2] = -transS;
    m[0][3] = 0.0f;
    m[1][0] = 0.0f;
    m[1][1] = cot * scaleT;
    m[1][2] = -transT;
    m[1][3] = 0.0f;
    m[2][0] = 0.0f;
    m[2][1] = 0.0f;
    m[2][2] = -1.0f;
    m[2][3] = 0.0f;
}

void C_MTXLightOrtho(MtxP m, f32 t, f32 b, f32 l, f32 r, f32 scaleS, f32 scaleT, f32 transS, f32 transT) {
    f32 tmp;
    tmp = 1.0f / (r - l);
    m[0][0] = 2.0f * tmp * scaleS;
    m[0][1] = 0.0f;
    m[0][2] = 0.0f;
    m[0][3] = (-(r + l) * tmp) * scaleS + transS;

    tmp = 1.0f / (t - b);
    m[1][0] = 0.0f;
    m[1][1] = 2.0f * tmp * scaleT;
    m[1][2] = 0.0f;
    m[1][3] = (-(t + b) * tmp) * scaleT + transT;

    m[2][0] = 0.0f;
    m[2][1] = 0.0f;
    m[2][2] = 0.0f;
    m[2][3] = 1.0f;
}

/* --- N64/libultra matrix functions (fixed-point Mtx) --- */

void guMtxIdentF(float mf[4][4]) {
    int i, j;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            mf[i][j] = (i == j) ? 1.0f : 0.0f;
}

void guMtxF2L(float mf[4][4], Mtx* m) {
    int i, j;
    s32 e1, e2;
    s32 *ai, *af;

    ai = (s32*)&m->m[0][0];
    af = (s32*)&m->m[2][0];

    for (i = 0; i < 4; i++)
        for (j = 0; j < 2; j++) {
            e1 = FTOFIX32(mf[i][j * 2]);
            e2 = FTOFIX32(mf[i][j * 2 + 1]);
            *(ai++) = (e1 & 0xffff0000) | ((u32)e2 >> 16);
            *(af++) = (e1 << 16) | (e2 & 0xffff);
        }
}

void guMtxIdent(Mtx* m) {
    float mf[4][4];
    guMtxIdentF(mf);
    guMtxF2L(mf, m);
}

void guOrthoF(float mf[4][4], float l, float r, float b, float t, float n, float f, float scale) {
    int i, j;
    guMtxIdentF(mf);
    mf[0][0] = 2.0f / (r - l);
    mf[1][1] = 2.0f / (t - b);
    mf[2][2] = -2.0f / (f - n);
    mf[3][0] = -(r + l) / (r - l);
    mf[3][1] = -(t + b) / (t - b);
    mf[3][2] = -(f + n) / (f - n);
    mf[3][3] = 1.0f;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            mf[i][j] *= scale;
}

void guOrtho(Mtx* m, float l, float r, float b, float t, float n, float f, float scale) {
    float mf[4][4];
    guOrthoF(mf, l, r, b, t, n, f, scale);
    guMtxF2L(mf, m);
}

void guPerspectiveF(float mf[4][4], u16* perspNorm, float fovy, float aspect, float near, float far, float scale) {
    float cot;
    int i, j;
    guMtxIdentF(mf);
    fovy *= PC_DEG_TO_RADf;
    cot = cosf(fovy / 2.0f) / sinf(fovy / 2.0f);
    mf[0][0] = cot / aspect;
    mf[1][1] = cot;
    mf[2][2] = (near + far) / (near - far);
    mf[2][3] = -1.0f;
    mf[3][2] = (2.0f * near * far) / (near - far);
    mf[3][3] = 0.0f;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            mf[i][j] *= scale;
    if (perspNorm != NULL) {
        if (near + far <= 2.0f) {
            *perspNorm = (u16)0xFFFF;
        } else {
            *perspNorm = (u16)((2.0f * 65536.0f) / (near + far));
            if (*perspNorm <= 0)
                *perspNorm = (u16)0x0001;
        }
    }
}

void guPerspective(Mtx* m, u16* perspNorm, float fovy, float aspect, float near, float far, float scale) {
    float mf[4][4];
    guPerspectiveF(mf, perspNorm, fovy, aspect, near, far, scale);
    guMtxF2L(mf, m);
}

void guLookAtF(float mf[4][4], float xEye, float yEye, float zEye,
               float xAt, float yAt, float zAt,
               float xUp, float yUp, float zUp) {
    float len, xLook, yLook, zLook, xRight, yRight, zRight;

    guMtxIdentF(mf);

    xLook = xAt - xEye;
    yLook = yAt - yEye;
    zLook = zAt - zEye;

    len = sqrtf(xLook*xLook + yLook*yLook + zLook*zLook);
    len = -1.0f / len;
    xLook *= len;
    yLook *= len;
    zLook *= len;

    xRight = yUp * zLook - zUp * yLook;
    yRight = zUp * xLook - xUp * zLook;
    zRight = xUp * yLook - yUp * xLook;
    len = sqrtf(xRight*xRight + yRight*yRight + zRight*zRight);
    len = 1.0f / len;
    xRight *= len;
    yRight *= len;
    zRight *= len;

    xUp = yLook * zRight - zLook * yRight;
    yUp = zLook * xRight - xLook * zRight;
    zUp = xLook * yRight - yLook * xRight;
    len = sqrtf(xUp*xUp + yUp*yUp + zUp*zUp);
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

    mf[0][3] = 0.0f;
    mf[1][3] = 0.0f;
    mf[2][3] = 0.0f;
    mf[3][3] = 1.0f;
}

void guLookAt(Mtx* m, float xEye, float yEye, float zEye,
              float xAt, float yAt, float zAt,
              float xUp, float yUp, float zUp) {
    float mf[4][4];
    guLookAtF(mf, xEye, yEye, zEye, xAt, yAt, zAt, xUp, yUp, zUp);
    guMtxF2L(mf, m);
}

typedef struct { unsigned char col[3]; char pad1; unsigned char colc[3]; char pad2; signed char dir[3]; char pad3; } pc_Light_t;
typedef union { pc_Light_t l; long long int force_align[2]; } pc_Light;
typedef struct { pc_Light l[2]; } pc_LookAt;
typedef struct { int x1, y1, x2, y2; } pc_Hilite_t;
typedef union { pc_Hilite_t h; long long int force_align[2]; } pc_Hilite;

#define FTOFRAC8(x) ((int)((x) * 128.0f < 127.0f ? (x) * 128.0f : 127.0f) & 0xff)
#define THRESH2 0.1f

void guLookAtHilite(Mtx* m, void* lv, void* hv,
                    float xEye, float yEye, float zEye,
                    float xAt, float yAt, float zAt,
                    float xUp, float yUp, float zUp,
                    float xl1, float yl1, float zl1,
                    float xl2, float yl2, float zl2,
                    int twidth, int theight) {
    pc_LookAt* l = (pc_LookAt*)lv;
    pc_Hilite* h = (pc_Hilite*)hv;
    float mf[4][4];
    float len, xLook, yLook, zLook, xRight, yRight, zRight;
    float xHilite, yHilite, zHilite;

    guMtxIdentF(mf);

    xLook = xAt - xEye;
    yLook = yAt - yEye;
    zLook = zAt - zEye;

    len = -1.0f / sqrtf(xLook*xLook + yLook*yLook + zLook*zLook);
    xLook *= len; yLook *= len; zLook *= len;

    xRight = yUp * zLook - zUp * yLook;
    yRight = zUp * xLook - xUp * zLook;
    zRight = xUp * yLook - yUp * xLook;
    len = 1.0f / sqrtf(xRight*xRight + yRight*yRight + zRight*zRight);
    xRight *= len; yRight *= len; zRight *= len;

    xUp = yLook * zRight - zLook * yRight;
    yUp = zLook * xRight - xLook * zRight;
    zUp = xLook * yRight - yLook * xRight;
    len = 1.0f / sqrtf(xUp*xUp + yUp*yUp + zUp*zUp);
    xUp *= len; yUp *= len; zUp *= len;

    len = 1.0f / sqrtf(xl1*xl1 + yl1*yl1 + zl1*zl1);
    xl1 *= len; yl1 *= len; zl1 *= len;

    xHilite = xl1 + xLook;
    yHilite = yl1 + yLook;
    zHilite = zl1 + zLook;
    len = sqrtf(xHilite*xHilite + yHilite*yHilite + zHilite*zHilite);
    if (len > THRESH2) {
        len = 1.0f / len;
        xHilite *= len; yHilite *= len; zHilite *= len;
        h->h.x1 = twidth * 4 + (int)((xHilite*xRight + yHilite*yRight + zHilite*zRight) * twidth * 2);
        h->h.y1 = theight * 4 + (int)((xHilite*xUp + yHilite*yUp + zHilite*zUp) * theight * 2);
    } else {
        h->h.x1 = twidth * 2;
        h->h.y1 = theight * 2;
    }

    len = 1.0f / sqrtf(xl2*xl2 + yl2*yl2 + zl2*zl2);
    xl2 *= len; yl2 *= len; zl2 *= len;

    xHilite = xl2 + xLook;
    yHilite = yl2 + yLook;
    zHilite = zl2 + zLook;
    len = sqrtf(xHilite*xHilite + yHilite*yHilite + zHilite*zHilite);
    if (len > THRESH2) {
        len = 1.0f / len;
        xHilite *= len; yHilite *= len; zHilite *= len;
        h->h.x2 = twidth * 4 + (int)((xHilite*xRight + yHilite*yRight + zHilite*zRight) * twidth * 2);
        h->h.y2 = theight * 4 + (int)((xHilite*xUp + yHilite*yUp + zHilite*zUp) * theight * 2);
    } else {
        h->h.x2 = twidth * 2;
        h->h.y2 = theight * 2;
    }

    l->l[0].l.dir[0] = FTOFRAC8(xRight);
    l->l[0].l.dir[1] = FTOFRAC8(yRight);
    l->l[0].l.dir[2] = FTOFRAC8(zRight);
    l->l[1].l.dir[0] = FTOFRAC8(xUp);
    l->l[1].l.dir[1] = FTOFRAC8(yUp);
    l->l[1].l.dir[2] = FTOFRAC8(zUp);
    l->l[0].l.col[0] = 0x00; l->l[0].l.col[1] = 0x00; l->l[0].l.col[2] = 0x00; l->l[0].l.pad1 = 0x00;
    l->l[0].l.colc[0] = 0x00; l->l[0].l.colc[1] = 0x00; l->l[0].l.colc[2] = 0x00; l->l[0].l.pad2 = 0x00;
    l->l[1].l.col[0] = 0x00; l->l[1].l.col[1] = 0x80; l->l[1].l.col[2] = 0x00; l->l[1].l.pad1 = 0x00;
    l->l[1].l.colc[0] = 0x00; l->l[1].l.colc[1] = 0x80; l->l[1].l.colc[2] = 0x00; l->l[1].l.pad2 = 0x00;

    mf[0][0] = xRight; mf[1][0] = yRight; mf[2][0] = zRight;
    mf[3][0] = -(xEye * xRight + yEye * yRight + zEye * zRight);
    mf[0][1] = xUp;    mf[1][1] = yUp;    mf[2][1] = zUp;
    mf[3][1] = -(xEye * xUp + yEye * yUp + zEye * zUp);
    mf[0][2] = xLook;  mf[1][2] = yLook;  mf[2][2] = zLook;
    mf[3][2] = -(xEye * xLook + yEye * yLook + zEye * zLook);
    mf[0][3] = 0; mf[1][3] = 0; mf[2][3] = 0; mf[3][3] = 1;

    guMtxF2L(mf, m);
}

void guScale(Mtx* m, float x, float y, float z) {
    float mf[4][4];
    guMtxIdentF(mf);
    mf[0][0] = x; mf[1][1] = y; mf[2][2] = z; mf[3][3] = 1.0f;
    guMtxF2L(mf, m);
}

void guTranslate(Mtx* m, float x, float y, float z) {
    float mf[4][4];
    guMtxIdentF(mf);
    mf[3][0] = x; mf[3][1] = y; mf[3][2] = z;
    guMtxF2L(mf, m);
}

void guRotateF(float mf[4][4], float a, float x, float y, float z) {
    float s, c, t;
    float len = sqrtf(x*x + y*y + z*z);
    if (len > 0.0f) { x /= len; y /= len; z /= len; }

    a *= PC_DEG_TO_RADf;
    s = sinf(a);
    c = cosf(a);
    t = 1.0f - c;

    guMtxIdentF(mf);
    mf[0][0] = t*x*x + c;    mf[0][1] = t*x*y + s*z; mf[0][2] = t*x*z - s*y;
    mf[1][0] = t*x*y - s*z;  mf[1][1] = t*y*y + c;   mf[1][2] = t*y*z + s*x;
    mf[2][0] = t*x*z + s*y;  mf[2][1] = t*y*z - s*x; mf[2][2] = t*z*z + c;
}

void guRotate(Mtx* m, float a, float x, float y, float z) {
    float mf[4][4];
    guRotateF(mf, a, x, y, z);
    guMtxF2L(mf, m);
}

void guNormalize(float* x, float* y, float* z) {
    float norm = sqrtf(*x * *x + *y * *y + *z * *z);
    if (norm > 0.0f) {
        norm = 1.0f / norm;
        *x *= norm;
        *y *= norm;
        *z *= norm;
    }
}

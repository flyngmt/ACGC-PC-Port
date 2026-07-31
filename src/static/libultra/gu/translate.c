#include "libultra/gu.h"

void guTranslate(N64Mtx *m, float x, float y, float z) {
    float mf[4][4];
    guTranslateF(mf, x, y, z);
    guMtxF2L(mf, m);
}

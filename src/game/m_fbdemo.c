#include "m_fbdemo.h"

#include "gfxalloc.h"
#include "libc64/malloc.h"
#include "libc64/sleep.h"
#include "libultra/gu.h"
#include "m_play.h"
#include "libultra/libultra.h"

static Gfx fbdemo_gfx_init[] = {
    gsDPPipeSync(),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN |
                          G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH),
    gsDPSetCombineMode(G_CC_DECALRGB, G_CC_DECALRGB),
    gsDPSetOtherMode(G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_1PRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_AA_OPA_SURF | G_RM_AA_OPA_SURF2),
    gsSPEndDisplayList(),
};

extern void fbdemo_init_gfx(fbdemo_c* this) {
    int col;
    int col2;
    int colTex;
    int rowTex;

    int row;
    int frame;

    Vtx* vtx;
    Gfx* gfx;

    guMtxIdent(&this->modelView1);
    guMtxIdent(&this->modelView2);
    guOrtho(&this->projection, 0.0f, N64_SCREEN_WIDTH, N64_SCREEN_HEIGHT, 0.0f, -1000.0f, 1000.0f, 1.0f);

    for (frame = 0; frame < 2; frame++) {
        this->frame = frame;
        vtx = (this->frame == 0) ? this->vtxFrame1 : this->vtxFrame2;
        for (rowTex = 0, row = 0; row < (this->rows + 1); rowTex += 0x20, row++) {
            for (colTex = 0, col = 0; col < (this->cols + 1); colTex += 0x20, col++) {
                Vtx_tn* vtxn = &vtx->n;
                vtx++;
                vtxn->ob[0] = col * 0x20;
                vtxn->ob[1] = row * 0x20;
                vtxn->ob[2] = -5;
                vtxn->flag = 0;
                vtxn->tc[0] = colTex << 6;
                vtxn->tc[1] = rowTex << 6;
                vtxn->n[0] = 0;
                vtxn->n[1] = 0;
                vtxn->n[2] = 120;
                vtxn->a = 255;
            }
        }
    }

    gfx = this->gfx;
    for (rowTex = 0, row = 0; row < this->rows; rowTex += 0x20, row++) {
        gSPVertex(gfx++, anime_3_txt + (u32)row * (this->cols + 1) * sizeof(Vtx), 2 * (this->cols + 1), 0);

        colTex = 0;
        col = 0;
        col2 = 0;
        while (col < this->cols) {
            gDPPipeSync(gfx++);

            gDPLoadTextureTile(gfx++, anime_4_txt, G_IM_FMT_RGBA, G_IM_SIZ_16b, N64_SCREEN_WIDTH,
                               N64_SCREEN_HEIGHT, colTex, rowTex, colTex + 0x20, rowTex + 0x20, 0,
                               G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                               G_TX_NOLOD, G_TX_NOLOD);

            gSP1Quadrangle(gfx++, col2, col2 + 1, +(this->cols) + 2 + col2, this->cols + 1 + col2, 0);

            colTex += 0x20;
            col2++;
            col++;
        }
    }

    gDPPipeSync(gfx++);
    gSPEndDisplayList(gfx++);
}

extern void fbdemo_init_data(fbdemo_c* this) {
    int col;
    int row;

    for (row = 0; row < this->rows + 1; row++) {
        for (col = 0; col < this->cols + 1; col++) {
            (this->vtxData + col + row * (this->cols + 1))->x = col * 0x20;
            (this->vtxData + col + row * (this->cols + 1))->y = row * 0x20;
        }
    }
}

extern void fbdemo_cleanup(fbdemo_c* this) {
    msleep(100);

    if (this->vtxData != NULL) {
        free(this->vtxData);
        this->vtxData = NULL;
    }
    if (this->vtxFrame1 != NULL) {
        free(this->vtxFrame1);
        this->vtxFrame1 = NULL;
    }
    if (this->vtxFrame2 != NULL) {
        free(this->vtxFrame2);
        this->vtxFrame2 = NULL;
    }
    if (this->gfx != NULL) {
        free(this->gfx);
        this->gfx = NULL;
    }
}

extern fbdemo_c* fbdemo_init(fbdemo_c* this, int cols, int rows) {
    s32 gridsize;

    bzero(this, sizeof(fbdemo_c));

    this->cols = cols;
    this->rows = rows;

    this->frame = 0;
    this->vtxData = malloc((cols + 1) * sizeof(xy_t) * (rows + 1));

    this->vtxFrame1 = malloc((cols + 1) * sizeof(Vtx) * (rows + 1));
    this->vtxFrame2 = malloc((cols + 1) * sizeof(Vtx) * (rows + 1));

    this->gfx = malloc(((this->cols * 9 + 1) * this->rows + 2) * sizeof(Gfx));

    if ((this->vtxData == NULL) || (this->vtxFrame1 == NULL) || (this->vtxFrame2 == NULL) || (this->gfx == NULL)) {
        if (this->vtxData != NULL) {
            free(this->vtxData);
            this->vtxData = NULL;
        }

        if (this->vtxFrame1 != NULL) {
            free(this->vtxFrame1);
            this->vtxFrame1 = NULL;
        }

        if (this->vtxFrame2 != NULL) {
            free(this->vtxFrame2);
            this->vtxFrame2 = NULL;
        }

        if (this->gfx != NULL) {
            free(this->gfx);
            this->gfx = NULL;
        }

        return NULL;
    }

    fbdemo_init_gfx(this);
    fbdemo_init_data(this);
    this->frame = 0;

    return this;
}

extern void fbdemo_update(fbdemo_c* this) {
    int col;
    int row;
    Vtx* vtx;

    for (row = 0; row < this->rows + 1; row++) {
        for (col = 0; col < this->cols + 1; col++) {
            vtx = (this->frame == 0) ? this->vtxFrame1 : this->vtxFrame2;
            (vtx + col + row * (this->cols + 1))->n.ob[0] = (this->vtxData + col + row * (this->cols + 1))->x;

            vtx = (this->frame == 0) ? this->vtxFrame1 : this->vtxFrame2;
            (vtx + col + row * (this->cols + 1))->n.ob[1] = (this->vtxData + col + row * (this->cols + 1))->y;
        }
    }
}

extern void fbdemo_draw(fbdemo_c* this, Gfx** gfxP) {
    Gfx* gfx = *gfxP;

    gSPDisplayList(gfx++, fbdemo_gfx_init);
    fbdemo_update(this);
#ifdef TARGET_PC
    /* Copy matrices into gfxalloc buffers to avoid seg2k0 collision with
       N64 segment range when struct is heap-allocated in 0x03-0x0F. */
    {
        N64Mtx* proj_copy = (N64Mtx*)gfxalloc(&gfx, sizeof(N64Mtx));
        N64Mtx* mv_copy = (N64Mtx*)gfxalloc(&gfx, sizeof(N64Mtx));
        *proj_copy = this->projection;
        *mv_copy = this->modelView1;
        gSPMatrix(gfx++, proj_copy, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
        gSPMatrix(gfx++, mv_copy, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    }
#else
    gSPMatrix(gfx++, &this->projection, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(gfx++, &this->modelView1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
#endif
    gSPSegment(gfx++, ANIME_3_TXT_SEG, this->frame == 0 ? this->vtxFrame1 : this->vtxFrame2);
    gSPSegment(gfx++, ANIME_4_TXT_SEG, this->zBuffer);
    gSPDisplayList(gfx++, fbdemo_gfx_init);
    gSPDisplayList(gfx++, this->gfx);
    gDPPipeSync(gfx++);
    this->frame ^= 1;
    *gfxP = gfx;
}

extern void fbdemo_move(fbdemo_c* this) {
}

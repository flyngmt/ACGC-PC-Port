/* Per-glyph math matches mFont_gppDrawCharPoly's cut-mode + mFont_gppLoadTexture
 * (half-texel UV inset for bilinear safety, screen-space position inset by the
 * same half texel). State setup mirrors mFontSentence_gppDraw_before: mode DL +
 * combine mode + prim color + a single texture-tile load for the whole atlas.
 *
 * Batching: up to 7 glyphs per gSPVertex (28 verts, fits 5-bit indexing). One
 * gSPNTrianglesInit_5b packs 3 triangles; subsequent gSPNTriangles_5b pack 4
 * each. The whole batch turns into ONE GXBegin/GXEnd inside emu64, so a
 * 46-char string drops from ~46 draw calls to ~7. Longer strings flush and
 * start a new batch. */

#include "pc_text_draw.h"

#include "game.h"
#include "graph.h"
#include "main.h"                       /* SCREEN_WIDTH, SCREEN_HEIGHT */
#include "m_font.h"
#include "m_rcp.h"
#include "dataobject.h"                 /* FONT_nes_tex_font1 */
#include "libforest/gbi_extensions.h"   /* gDPLoadTextureTile_4b_Dolphin */

#include <string.h>
#include <math.h>

/* Matches mFont_CC_FONT: RGB = prim color, A = TEXEL0 * prim (font is GC's
 * 4-bit intensity atlas). Keep in sync with m_font.c if mFont changes. */
#define PC_TEXT_CC 0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0

#define FONT_ATLAS_W (mFont_TEX_CHAR_WIDTH * 16)
#define FONT_ATLAS_H (mFont_TEX_CHAR_HEIGHT * 16)

/* 5-bit indexing caps vertex cache index at 31. 7 glyphs × 4 verts = 28. */
#define PC_TEXT_CHARS_PER_BATCH 7

extern void mFont_gppSetMode(Gfx** gfx_pp);

static inline void pc_trin_init_5b(Gfx** pp, int n,
    int v0, int v1, int v2,
    int v3, int v4, int v5,
    int v6, int v7, int v8) {
  Gfx* g = *pp;
  unsigned int w1 =
      /* bit 0 = mode (0 = 5bit) */
      ((unsigned)(v0 & 0x1F) <<  4)
    | ((unsigned)(v1 & 0x1F) <<  9)
    | ((unsigned)(v2 & 0x1F) << 14)
    | ((unsigned)(v3 & 0x1F) << 19)
    | ((unsigned)(v4 & 0x1F) << 24)
    | ((unsigned)(v5 & 0x07) << 29);
  unsigned int w0 =
      ((unsigned)((v5 >> 3) & 0x03) <<  0)
    | ((unsigned)(v6 & 0x1F)        <<  2)
    | ((unsigned)(v7 & 0x1F)        <<  7)
    | ((unsigned)(v8 & 0x1F)        << 12)
    | ((unsigned)((n - 1) & 0x7F)   << 17)
    | ((unsigned)G_TRIN_INDEPEND    << 24);
  g->words.w0 = w0;
  g->words.w1 = w1;
  *pp = g + 1;
}

static inline void pc_trin_cont_5b(Gfx** pp,
    int v0, int v1, int v2,
    int v3, int v4, int v5,
    int v6, int v7, int v8,
    int v9, int v10, int v11) {
  Gfx* g = *pp;
  unsigned int w1 =
      ((unsigned)(v0 & 0x1F) <<  4)
    | ((unsigned)(v1 & 0x1F) <<  9)
    | ((unsigned)(v2 & 0x1F) << 14)
    | ((unsigned)(v3 & 0x1F) << 19)
    | ((unsigned)(v4 & 0x1F) << 24)
    | ((unsigned)(v5 & 0x07) << 29);
  unsigned int w0 =
      ((unsigned)((v5 >> 3) & 0x03) <<  0)
    | ((unsigned)(v6  & 0x1F)       <<  2)
    | ((unsigned)(v7  & 0x1F)       <<  7)
    | ((unsigned)(v8  & 0x1F)       << 12)
    | ((unsigned)(v9  & 0x1F)       << 17)
    | ((unsigned)(v10 & 0x1F)       << 22)
    | ((unsigned)(v11 & 0x1F)       << 27);
  g->words.w0 = w0;
  g->words.w1 = w1;
  *pp = g + 1;
}

/* Replica of m_font's static mFont_SetVertex_dol — sets screen-space
 * position, s/t texcoords, flag=1 (NONSHARED matrix), zero vertex color. */
static inline void pc_text_set_vtx(Vtx* v, int x, int y, int s, int t) {
    v->v.ob[0] = (s16)x;
    v->v.ob[1] = (s16)y;
    v->v.ob[2] = 0;
    v->v.flag  = 1;
    v->v.tc[0] = (s16)s;
    v->v.tc[1] = (s16)t;
    v->v.cn[0] = 0;
    v->v.cn[1] = 0;
    v->v.cn[2] = 0;
    v->v.cn[3] = 0;
}

int pc_text_width(const char* s) {
    if (!s) return 0;
    int w = 0;
    for (const u8* p = (const u8*)s; *p; p++) {
        w += mFont_GetCodeWidth(*p, TRUE);
    }
    return w;
}

void pc_text_draw(struct game_s* game, const char* s, f32 x, f32 y,
                  int r, int g, int b, int a, f32 scale) {
    if (!game || !game->graph || !s) return;
    int len = (int)strlen(s);
    if (len <= 0) return;
    if (fabsf(scale) < 0.001f) return;

    GRAPH* graph = game->graph;

    OPEN_DISP(graph);
    Gfx* gfx = NOW_FONT_DISP;

    /* --- One-shot state setup (same as mFontSentence_gppDraw_before) --- */
    mFont_gppSetMode(&gfx);
    gDPPipeSync(gfx++);
    gDPSetCombineMode(gfx++, PC_TEXT_CC, PC_TEXT_CC);
    gDPSetPrimColor(gfx++, 0, 0, r, g, b, a);
    /* gDPLoadTextureTile_4b_Dolphin expands to two submacros that each take
     * `pkt` by value and don't advance it, so we must pass gfx++ to get
     * two increments (one per submacro).
     */
    gDPLoadTextureTile_4b_Dolphin(gfx++, FONT_nes_tex_font1, G_IM_FMT_I,
                                  FONT_ATLAS_W, FONT_ATLAS_H);

    /* --- Batched glyph emission --- */
    const f32 half_sw = (f32)SCREEN_WIDTH  * 0.5f;
    const f32 half_sh = (f32)SCREEN_HEIGHT * 0.5f;
    const f32 inv_half_t = 0.5f / (f32)mFont_TEX_CHAR_HEIGHT; /* mFont uses t=16 */

    f32 cur_x = x;
    int pos = 0;
    while (pos < len) {
        int batch_n = len - pos;
        if (batch_n > PC_TEXT_CHARS_PER_BATCH) batch_n = PC_TEXT_CHARS_PER_BATCH;

        Vtx* vtx = GRAPH_ALLOC_TYPE(graph, Vtx, batch_n * 4);
        if (!vtx) break;

        for (int i = 0; i < batch_n; i++) {
            int c = (u8)s[pos + i];
            int code_w = mFont_GetCodeWidth((u8)c, TRUE);
            if (code_w <= 0) code_w = mFont_TEX_CHAR_WIDTH;

            /* UV rect in atlas — same formula as mFont_gppLoadTexture +
             * the half-texel inset applied in mFont_gppDrawCharPoly. */
            int row = c >> 4;
            int col = c & 0x0F;
            int uls_px = col * mFont_TEX_CHAR_WIDTH;
            int ult_px = row * mFont_TEX_CHAR_HEIGHT;
            int uls_fx = (uls_px << 6) + 32;
            int ult_fx = (ult_px << 6) + 32;
            int lrs_fx = ((uls_px + code_w) << 6) - 32;
            int lrt_fx = ((ult_px + mFont_TEX_CHAR_HEIGHT) << 6) - 32;

            /* Screen-space quad corners. Match mFont_gppDrawCharPoly:
             * convert to centered/flipped coords, then inset by half texel. */
            f32 char_w = (f32)code_w                        * scale;
            f32 char_h = (f32)mFont_TEX_CHAR_HEIGHT_F32     * scale;
            f32 vx_tl = cur_x - half_sw;
            f32 vy_tl = -(y - half_sh);
            f32 t0    = char_w;
            f32 t1    = -char_h;
            f32 inv_half_s = 0.5f / (f32)code_w;

            f32 vx_br = vx_tl + t0 * (1.0f - inv_half_s);
            f32 vy_br = vy_tl + t1 * (1.0f - inv_half_t);
            vx_tl = vx_tl + t0 * inv_half_s;
            vy_tl = vy_tl + t1 * inv_half_t;

            int ulx = (int)(vx_tl * mFont_SCALE_F);
            int uly = (int)(vy_tl * mFont_SCALE_F);
            int lrx = (int)(vx_br * mFont_SCALE_F);
            int lry = (int)(vy_br * mFont_SCALE_F);

            /* Vertex order matches mFont_gppDrawCharPoly's: TL, BL, BR, TR.
             * Triangles (0,1,2) + (0,2,3) cover the quad. */
            Vtx* v = &vtx[i * 4];
            pc_text_set_vtx(v + 0, ulx, uly, uls_fx, ult_fx);
            pc_text_set_vtx(v + 1, ulx, lry, uls_fx, lrt_fx);
            pc_text_set_vtx(v + 2, lrx, lry, lrs_fx, lrt_fx);
            pc_text_set_vtx(v + 3, lrx, uly, lrs_fx, ult_fx);

            cur_x += char_w;
        }

        /* One gSPVertex covers the whole batch. */
        gSPVertex(gfx++, vtx, batch_n * 4, 0);

        /* Build triangle index list. 2 tris per glyph, contiguous. */
        int tri_count = batch_n * 2;
        int idx[PC_TEXT_CHARS_PER_BATCH * 2][3];
        for (int i = 0; i < batch_n; i++) {
            int bs = i * 4;
            idx[i * 2 + 0][0] = bs + 0;
            idx[i * 2 + 0][1] = bs + 1;
            idx[i * 2 + 0][2] = bs + 2;
            idx[i * 2 + 1][0] = bs + 0;
            idx[i * 2 + 1][1] = bs + 2;
            idx[i * 2 + 1][2] = bs + 3;
        }

        /* Init packet carries 3 triangles (pad with zeros if fewer). */
        int t0a = idx[0][0], t0b = idx[0][1], t0c = idx[0][2];
        int t1a = tri_count > 1 ? idx[1][0] : 0;
        int t1b = tri_count > 1 ? idx[1][1] : 0;
        int t1c = tri_count > 1 ? idx[1][2] : 0;
        int t2a = tri_count > 2 ? idx[2][0] : 0;
        int t2b = tri_count > 2 ? idx[2][1] : 0;
        int t2c = tri_count > 2 ? idx[2][2] : 0;
        pc_trin_init_5b(&gfx, tri_count,
                        t0a, t0b, t0c,
                        t1a, t1b, t1c,
                        t2a, t2b, t2c);

        /* Continuation packets carry 4 triangles each. emu64 stops
         * reading once n_faces hits zero, so padding zeros are ignored. */
        for (int t = 3; t < tri_count; t += 4) {
            int a0 = idx[t][0], a1 = idx[t][1], a2 = idx[t][2];
            int b0 = (t + 1 < tri_count) ? idx[t + 1][0] : 0;
            int b1 = (t + 1 < tri_count) ? idx[t + 1][1] : 0;
            int b2 = (t + 1 < tri_count) ? idx[t + 1][2] : 0;
            int c0 = (t + 2 < tri_count) ? idx[t + 2][0] : 0;
            int c1 = (t + 2 < tri_count) ? idx[t + 2][1] : 0;
            int c2 = (t + 2 < tri_count) ? idx[t + 2][2] : 0;
            int d0 = (t + 3 < tri_count) ? idx[t + 3][0] : 0;
            int d1 = (t + 3 < tri_count) ? idx[t + 3][1] : 0;
            int d2 = (t + 3 < tri_count) ? idx[t + 3][2] : 0;
            pc_trin_cont_5b(&gfx,
                            a0, a1, a2,
                            b0, b1, b2,
                            c0, c1, c2,
                            d0, d1, d2);
        }

        pos += batch_n;
    }

    SET_FONT_DISP(gfx);
    CLOSE_DISP(graph);
}

#include "evw_anime.h"

#include "m_play.h"
#include "libforest/gbi_extensions.h"
#include "m_rcp.h"

static double scroll_phase = 0.0;

extern void evw_anime_reset_scroll_phase() {
    scroll_phase = 0.0;
}

extern void evw_anime_add_scroll_phase(GAME* game) {
    scroll_phase += game->graph->dt_num_60fps_frames;
}

extern double evw_anime_get_scroll_phase() {
    return scroll_phase;
}

static Gfx* evw_tex_scroll_set(GAME_PLAY* play, EVW_ANIME_SCROLL* scroll) {
    // const f32 dt_scale = GRAPH_BASE_FRAME_RATE * play->game.graph->delta_time;
    // int scroll_x = scroll->x * (play->game_frame * dt_scale);
    // int scroll_y = scroll->y * (play->game_frame * dt_scale);
    int scroll_x = (int)(scroll->x * scroll_phase);
    int scroll_y = (int)(scroll->y * scroll_phase);

    return tex_scroll2_dolphin(play->game.graph, scroll_x, -scroll_y, scroll->width, scroll->height);
}

static void evw_anime_scroll1(GAME_PLAY* play, int segment, void* evw_data) {
    EVW_ANIME_SCROLL* scroll = (EVW_ANIME_SCROLL*)evw_data;
    Gfx* scroll_gfx = evw_tex_scroll_set(play, scroll);
    GRAPH* g = play->game.graph;

    OPEN_DISP(g);

    gSPSegment(NOW_BG_OPA_DISP++, segment, scroll_gfx);
    gSPSegment(NOW_POLY_OPA_DISP++, segment, scroll_gfx);
    gSPSegment(NOW_POLY_XLU_DISP++, segment, scroll_gfx);

    CLOSE_DISP(g);
}

static Gfx* evw_two_tex_scroll_set(GAME_PLAY* play, EVW_ANIME_SCROLL* scrolls) {
    f32 phase = scroll_phase;

    int x0 = (int)(scrolls[0].x * phase);
    int y0 = (int)(scrolls[0].y * phase);

    int x1 = (int)(scrolls[1].x * phase);
    int y1 = (int)(scrolls[1].y * phase);

    return two_tex_scroll_dolphin(play->game.graph, 0, x0, -y0, scrolls[0].width, scrolls[0].height, 1, x1, -y1,
                                  scrolls[1].width, scrolls[1].height);
}

static void evw_anime_scroll2(GAME_PLAY* play, int segment, void* evw_data) {
    EVW_ANIME_SCROLL* scrolls = (EVW_ANIME_SCROLL*)evw_data;
    Gfx* scroll_gfx = evw_two_tex_scroll_set(play, scrolls);
    GRAPH* g = play->game.graph;

    OPEN_DISP(g);

    gSPSegment(NOW_BG_OPA_DISP++, segment, scroll_gfx);
    gSPSegment(NOW_POLY_OPA_DISP++, segment, scroll_gfx);
    gSPSegment(NOW_POLY_XLU_DISP++, segment, scroll_gfx);

    CLOSE_DISP(g);
}

static void evw_color_set(GAME_PLAY* play, int segment, const EVW_ANIME_COL_PRIM* prim, const EVW_ANIME_COL_ENV* env) {
    Gfx* col_gfx = GRAPH_ALLOC_TYPE(play->game.graph, Gfx, 3);

    /* Setup small display list for initializing color settings */
    gDPSetPrimColor(col_gfx + 0, 0, prim->l, prim->r, prim->g, prim->b, prim->a);
    gDPSetEnvColor(col_gfx + 1, env->r, env->g, env->b, env->a);
    gSPEndDisplayList(col_gfx + 2);

    OPEN_DISP(play->game.graph);

    /* Point the necessary Gfx buffers to our color display list */
    gSPSegment(NOW_BG_OPA_DISP++, segment, col_gfx);
    gSPSegment(NOW_POLY_OPA_DISP++, segment, col_gfx);
    gSPSegment(NOW_POLY_XLU_DISP++, segment, col_gfx);

    CLOSE_DISP(play->game.graph);
}

static void evw_anime_colreg_manual(GAME_PLAY* play, int segment, void* evw_data) {
    EVW_ANIME_COLREG* color_reg = (EVW_ANIME_COLREG*)evw_data;

    int frame_idx = ((int)scroll_phase) % color_reg->frame_count;
    EVW_ANIME_COL_PRIM* prim = color_reg->prim_colors;
    EVW_ANIME_COL_ENV* env = color_reg->env_colors;

    prim += frame_idx;
    env += frame_idx;

    evw_color_set(play, segment, prim, env);
}

static int morf_calc(int now, int target, f32 rate) {
    return now + (int)(rate * (f32)(target - now));
}

static void evw_anime_colreg_linear(GAME_PLAY* play, int segment, void* evw_data) {
    EVW_ANIME_COLREG* color_reg = (EVW_ANIME_COLREG*)evw_data;
    EVW_ANIME_COL_PRIM* src_prim = color_reg->prim_colors;
    EVW_ANIME_COL_ENV* src_env = color_reg->env_colors;

    u16* keyframe = color_reg->keyframes;
    u32 game_frame = play->game_frame;
    int anime_frame = ((int)scroll_phase) % color_reg->frame_count;
    int now_keyframe;
    int last_keyframe;
    int frame_idx = 1;
    int i;

    keyframe++;
    for (i = 1; i < color_reg->key_count; i++) {
        if (anime_frame < *keyframe) {
            break;
        }

        keyframe++;
        frame_idx++;
    }

    {
        EVW_ANIME_COL_PRIM inter_prim;
        EVW_ANIME_COL_ENV inter_env;
        int a;
        int b;

        now_keyframe = keyframe[0];
        last_keyframe = keyframe[-1];
        a = anime_frame - last_keyframe;
        b = now_keyframe - last_keyframe;

        src_prim += frame_idx;
        src_env += frame_idx;

        /* Interpolate primitive color */
        inter_prim.r = morf_calc(src_prim[-1].r, src_prim[0].r, (f32)a / (f32)b);
        inter_prim.g = morf_calc(src_prim[-1].g, src_prim[0].g, (f32)a / (f32)b);
        inter_prim.b = morf_calc(src_prim[-1].b, src_prim[0].b, (f32)a / (f32)b);
        inter_prim.a = morf_calc(src_prim[-1].a, src_prim[0].a, (f32)a / (f32)b);
        inter_prim.l = morf_calc(src_prim[-1].l, src_prim[0].l, (f32)a / (f32)b);

        /* Interpolate environment color */
        inter_env.r = morf_calc(src_env[-1].r, src_env[0].r, (f32)a / (f32)b);
        inter_env.g = morf_calc(src_env[-1].g, src_env[0].g, (f32)a / (f32)b);
        inter_env.b = morf_calc(src_env[-1].b, src_env[0].b, (f32)a / (f32)b);
        inter_env.a = morf_calc(src_env[-1].a, src_env[0].a, (f32)a / (f32)b);

        evw_color_set(play, segment, &inter_prim, &inter_env);
    }
}

// Ragrange is probably Lagrange
static f32 RagrangeInt(int num_keyframes, f32* keyframes, f32* values, f32 now_frame) {
    f32 stack[EVW_COLOR_BUF_MAX];
    f32 res;
    f32 n;
    f32 m;
    int i;

    /* BUG: fixed stack buffer size but no input length validation. */
    for (i = 0; i < num_keyframes; i++) {
        int j;
        n = keyframes[i];
        m = 1.0f;

        /* Adjust keyframe by difference between all previous keyframes and the current keyframe */
        for (j = 0; j < i; j++) {
            m *= n - keyframes[j];
        }

        j++;
        for (j; j < num_keyframes; j++) {
            m *= n - keyframes[j];
        }

        stack[i] = values[i] / m;
    }

    res = 0.0f;
    for (i = 0; i < num_keyframes; i++) {
        int j;
        m = 1.0f;

        for (j = 0; j < i; j++) {
            m *= now_frame - keyframes[j];
        }

        j++;
        for (j; j < num_keyframes; j++) {
            m *= now_frame - keyframes[j];
        }

        res += m * stack[i];
    }

    return res;
}

static u8 RagrangeInt_Color(int num_keyframes, f32* keyframes, f32* values, f32 now_frame) {
    return (u8)(int)RagrangeInt(num_keyframes, keyframes, values, now_frame);
}

typedef struct {
    f32 keyframe_stack[EVW_COLOR_BUF_MAX];

    f32 prim_r_stack[EVW_COLOR_BUF_MAX];
    f32 prim_g_stack[EVW_COLOR_BUF_MAX];
    f32 prim_b_stack[EVW_COLOR_BUF_MAX];
    f32 prim_a_stack[EVW_COLOR_BUF_MAX];
    f32 prim_l_stack[EVW_COLOR_BUF_MAX];

    f32 env_r_stack[EVW_COLOR_BUF_MAX];
    f32 env_g_stack[EVW_COLOR_BUF_MAX];
    f32 env_b_stack[EVW_COLOR_BUF_MAX];
    f32 env_a_stack[EVW_COLOR_BUF_MAX];
} EVW_ANIME_COLREG_F;

static void evw_anime_colreg_nonlinear(GAME_PLAY* play, int segment, void* evw_data) {
    EVW_ANIME_COLREG* colreg = (EVW_ANIME_COLREG*)evw_data;

    EVW_ANIME_COL_PRIM* prim_p;
    EVW_ANIME_COL_ENV* env_p;
    EVW_ANIME_COL_PRIM* prim_src = colreg->prim_colors;
    EVW_ANIME_COL_ENV* env_src = colreg->env_colors;
    u16* keyframes = colreg->keyframes;
    f32 now_frame = MOD_F(scroll_phase, colreg->frame_count);
    int i;

    EVW_ANIME_COLREG_F colreg_float;

    /* BUG: fixed stack buffer size but no input length validation. */
    for (i = 0; i < colreg->key_count; i++) {
        colreg_float.keyframe_stack[i] = (int)keyframes[i];

        prim_p = &prim_src[i];
        env_p = &env_src[i];

        colreg_float.prim_r_stack[i] = (int)prim_p->r;
        colreg_float.prim_g_stack[i] = (int)prim_p->g;
        colreg_float.prim_b_stack[i] = (int)prim_p->b;
        colreg_float.prim_a_stack[i] = (int)prim_p->a;
        colreg_float.prim_l_stack[i] = (int)prim_p->l;

        colreg_float.env_r_stack[i] = (int)env_p->r;
        colreg_float.env_g_stack[i] = (int)env_p->g;
        colreg_float.env_b_stack[i] = (int)env_p->b;
        colreg_float.env_a_stack[i] = (int)env_p->a;
    }

    {
        EVW_ANIME_COL_PRIM nonlinear_prim;
        EVW_ANIME_COL_ENV nonlinear_env;

        nonlinear_prim.r =
            RagrangeInt_Color(colreg->key_count, colreg_float.keyframe_stack, colreg_float.prim_r_stack, now_frame);
        nonlinear_prim.g =
            RagrangeInt_Color(colreg->key_count, colreg_float.keyframe_stack, colreg_float.prim_g_stack, now_frame);
        nonlinear_prim.b =
            RagrangeInt_Color(colreg->key_count, colreg_float.keyframe_stack, colreg_float.prim_b_stack, now_frame);
        nonlinear_prim.a =
            RagrangeInt_Color(colreg->key_count, colreg_float.keyframe_stack, colreg_float.prim_a_stack, now_frame);
        nonlinear_prim.l =
            RagrangeInt_Color(colreg->key_count, colreg_float.keyframe_stack, colreg_float.prim_l_stack, now_frame);

        nonlinear_env.r =
            RagrangeInt_Color(colreg->key_count, colreg_float.keyframe_stack, colreg_float.env_r_stack, now_frame);
        nonlinear_env.g =
            RagrangeInt_Color(colreg->key_count, colreg_float.keyframe_stack, colreg_float.env_g_stack, now_frame);
        nonlinear_env.b =
            RagrangeInt_Color(colreg->key_count, colreg_float.keyframe_stack, colreg_float.env_b_stack, now_frame);
        nonlinear_env.a =
            RagrangeInt_Color(colreg->key_count, colreg_float.keyframe_stack, colreg_float.env_a_stack, now_frame);

        evw_color_set(play, segment, &nonlinear_prim, &nonlinear_env);
    }
}

static void evw_anime_texanime(GAME_PLAY* play, int segment, void* evw_data) {
    EVW_ANIME_TEXANIME* texanime = (EVW_ANIME_TEXANIME*)evw_data;
    GRAPH* g = play->game.graph;
    int frame = (int)(scroll_phase) % (texanime->frame_count * 2);
    void* tex_p = texanime->texture_tbl[texanime->animation_pattern[frame / 2]]; // 60fps pattern back to 30fps

    OPEN_DISP(g);

    gSPSegment(NOW_BG_OPA_DISP++, segment, tex_p);
    gSPSegment(NOW_POLY_OPA_DISP++, segment, tex_p);
    gSPSegment(NOW_POLY_XLU_DISP++, segment, tex_p);

    CLOSE_DISP(g);
}

typedef void (*EVW_ANIME_PROC)(GAME_PLAY*, int, void*);

extern void Evw_Anime_Set(GAME_PLAY* play, EVW_ANIME_DATA* evw_anime_data) {
    static EVW_ANIME_PROC evw_anime_proc[EVW_ANIME_TYPE_NUM] = {
        &evw_anime_scroll1,       &evw_anime_scroll2,          &evw_anime_colreg_manual,
        &evw_anime_colreg_linear, &evw_anime_colreg_nonlinear, &evw_anime_texanime,
    };

    if (evw_anime_data != NULL) {
        int segment = evw_anime_data->segment;

        if (segment != 0) {
            do {
                segment = evw_anime_data->segment;
                (*evw_anime_proc[evw_anime_data->type])(play, G_MWO_SEGMENT_7 + ABS(segment), evw_anime_data->data_p);
                evw_anime_data++;
            } while (segment >= 0);
        }
    }
}

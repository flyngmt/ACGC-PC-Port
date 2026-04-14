#ifndef EVW_ANIME_H
#define EVW_ANIME_H

#include "types.h"
#include "m_play_h.h"
#include "game_h.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EVW_COLOR_BUF_MAX 50

enum {
    EVW_ANIME_TYPE_SCROLL1,
    EVW_ANIME_TYPE_SCROLL2,
    EVW_ANIME_TYPE_COLREG_MANUAL,
    EVW_ANIME_TYPE_COLREG_LINEAR,
    EVW_ANIME_TYPE_COLREG_NONLINEAR,
    EVW_ANIME_TYPE_TEXANIME,

    EVW_ANIME_TYPE_NUM
};

/* sizeof(EVW_ANIME_COL_PRIM) == 0x5 */
typedef struct evw_anime_col_prim_s {
    /* 0x00 */ u8 r;
    /* 0x01 */ u8 g;
    /* 0x02 */ u8 b;
    /* 0x03 */ u8 a;
    /* 0x04 */ u8 l;
} EVW_ANIME_COL_PRIM;

/* sizeof(EVW_ANIME_COL_ENV) == 0x4 */
typedef struct evw_anime_col_env_s {
    /* 0x00 */ u8 r;
    /* 0x01 */ u8 g;
    /* 0x02 */ u8 b;
    /* 0x03 */ u8 a;
} EVW_ANIME_COL_ENV;

/* sizeof(EVW_ANIME_COLREG) == 0x10 */
typedef struct evw_anime_col_reg_s {
    /* 0x00 */ u16 frame_count; /* total frames in the animation */
    /* 0x02 */ u16 key_count;   /* number of animation keyframes */

    /* 0x04 */ EVW_ANIME_COL_PRIM* prim_colors; /* list of primitive colors per-keyframe */
    /* 0x08 */ EVW_ANIME_COL_ENV* env_colors;   /* list of environment colors per-keyframe */

    /* 0x0C */ u16* keyframes; /* list of keyframe frame indices */
} EVW_ANIME_COLREG;

/* sizeof(EVW_ANIME_SCROLL) == 0x4 */
typedef struct evw_anime_scroll_s {
    /* 0x00 */ s8 x;      /* x (s) texture position */
    /* 0x01 */ s8 y;      /* y (t) texture position */
    /* 0x02 */ u8 width;  /* texture width */
    /* 0x03 */ u8 height; /* texture height */
} EVW_ANIME_SCROLL;

/* sizeof(EVW_ANIME_TEXANIME) == 0x10 */
typedef struct evw_anime_texanime_s {
    /* 0x00 */ u16 frame_count; /* total frames in the animation */
    /* 0x02 */ u16 key_count;   /* number of animation keyframes */

    /* 0x04 */ void** texture_tbl;    /* list of each texture */
    /* 0x08 */ u8* animation_pattern; /* list of which texture to use per keyframe (runs at 30 FPS) */

    /* 0x0C */ u16* keyframes; /* list of keyframe frame indices */
} EVW_ANIME_TEXANIME;

/* sizeof(EVW_ANIME_DATA) == 0x8 */
typedef struct evw_anime_s {
    /* 0x00 */ s8 segment; /* Negative segments signal the end of the animation data array */
    /* 0x02 */ s16 type;
    /* 0x04 */ void* data_p;
} EVW_ANIME_DATA;

extern void Evw_Anime_Set(GAME_PLAY* play, EVW_ANIME_DATA* evw_anime_data);
extern void evw_anime_add_scroll_phase(GAME* game);
extern void evw_anime_reset_scroll_phase();
extern f64 evw_anime_get_scroll_phase();

#ifdef __cplusplus
}
#endif

#endif

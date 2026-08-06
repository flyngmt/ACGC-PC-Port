#ifndef AC_INSECT_H_H
#define AC_INSECT_H_H

#include "types.h"
#include "m_actor.h"
#include "m_lib.h"
#include "ac_tools.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aINS_ACTOR_NUM 9
#define aINS_MAX_STRESS_DIST (3 * mFI_UNIT_BASE_SIZE_F)
#define aINS_PATIENCE_STEP 0.5f

enum insect_type {
    aINS_INSECT_TYPE_COMMON_BUTTERFLY,
    aINS_INSECT_TYPE_YELLOW_BUTTERFLY,
    aINS_INSECT_TYPE_TIGER_BUTTERFLY,
    aINS_INSECT_TYPE_PURPLE_BUTTERFLY,
    aINS_INSECT_TYPE_ROBUST_CICADA,
    aINS_INSECT_TYPE_WALKER_CICADA,
    aINS_INSECT_TYPE_EVENING_CICADA,
    aINS_INSECT_TYPE_BROWN_CICADA,
    aINS_INSECT_TYPE_BEE,
    aINS_INSECT_TYPE_COMMON_DRAGONFLY,
    aINS_INSECT_TYPE_RED_DRAGONFLY,
    aINS_INSECT_TYPE_DARNER_DRAGONFLY,
    aINS_INSECT_TYPE_BANDED_DRAGONFLY,
    aINS_INSECT_TYPE_LONG_LOCUST,
    aINS_INSECT_TYPE_MIGRATORY_LOCUST,
    aINS_INSECT_TYPE_CRICKET,
    aINS_INSECT_TYPE_GRASSHOPPER,
    aINS_INSECT_TYPE_BELL_CRICKET,
    aINS_INSECT_TYPE_PINE_CRICKET,
    aINS_INSECT_TYPE_DRONE_BEETLE,
    aINS_INSECT_TYPE_DYNASTID_BEETLE,
    aINS_INSECT_TYPE_FLAT_STAG_BEETLE,
    aINS_INSECT_TYPE_JEWEL_BEETLE,
    aINS_INSECT_TYPE_LONGHORN_BEETLE,
    aINS_INSECT_TYPE_LADYBUG,
    aINS_INSECT_TYPE_SPOTTED_LADYBUG,
    aINS_INSECT_TYPE_MANTIS,
    aINS_INSECT_TYPE_FIREFLY,
    aINS_INSECT_TYPE_COCKROACH,
    aINS_INSECT_TYPE_SAW_STAG_BEETLE,
    aINS_INSECT_TYPE_MOUNTAIN_BEETLE,
    aINS_INSECT_TYPE_GIANT_BEETLE,
    aINS_INSECT_TYPE_SNAIL,
    aINS_INSECT_TYPE_MOLE_CRICKET,
    aINS_INSECT_TYPE_POND_SKATER,
    aINS_INSECT_TYPE_BAGWORM,
    aINS_INSECT_TYPE_PILL_BUG,
    aINS_INSECT_TYPE_SPIDER,
    aINS_INSECT_TYPE_ANT,
    aINS_INSECT_TYPE_MOSQUITO,
    aINS_INSECT_TYPE_NUM,

    aINS_INSECT_TYPE_SPIRIT = aINS_INSECT_TYPE_NUM,
    aINS_INSECT_TYPE_NONE,
    aINS_INSECT_TYPE_EXTENDED_NUM
};

enum {
    aINS_MAKE_NEW,
    aINS_MAKE_EXIST,

    aINS_MAKE_NUM
};

enum {
    aINS_INIT_NORMAL,
    aINS_INIT_RELEASE,

    aINS_INIT_NUM
};

enum {
    aINS_PROGRAM_CHOU,
    aINS_PROGRAM_BATTA,
    aINS_PROGRAM_TONBO,
    aINS_PROGRAM_TENTOU,
    aINS_PROGRAM_HOTARU,
    aINS_PROGRAM_SEMI,
    aINS_PROGRAM_KABUTO,
    aINS_PROGRAM_GOKI,
    aINS_PROGRAM_HITODAMA,
    aINS_PROGRAM_AMENBO,
    aINS_PROGRAM_KA,
    aINS_PROGRAM_DANGO,
    aINS_PROGRAM_KERA,
    aINS_PROGRAM_MINO,

    aINS_PROGRAM_NUM
};

enum {
    aINS_BG_CHECK_TYPE_NONE,
    aINS_BG_CHECK_TYPE_REG_ATTR,
    aINS_BG_CHECK_TYPE_REG_NO_ATTR,
    aINS_BG_CHECK_TYPE_NO_UNIT_COLUMN_ATTR,
    aINS_BG_CHECK_TYPE_NO_UNIT_COLUMN_NO_ATTR,

    aINS_BG_CHECK_TYPE_NUM
};

/* sizeof(aINS_Init_c) == 0x18 */
typedef struct insect_init_s {
    /* 0x00 */ int insect_type;
    /* 0x04 */ xyz_t position;
    /* 0x10 */ int extra_data;
    /* 0x14 */ GAME* game;
} aINS_Init_c;

typedef void (*aINS_MOVE_PROC)(ACTOR*);
typedef void (*aINS_ACTION_PROC)(ACTOR*, GAME*);

static inline f32 aINS_dt_step(GAME* game, f32 step) {
    return step * (f32)game->graph->dt_num_60fps_frames;
}

static inline s16 aINS_dt_angle_step(GAME* game, s16 step) {
    f32 dt_step = (f32)step * (f32)game->graph->dt_num_60fps_frames;

    if (dt_step < 1.0f) {
        dt_step = 1.0f;
    }

    return (s16)dt_step;
}

static inline int aINS_dt_phase(GAME* game, int* phase, int period) {
    const int scale = 0x10000;
    int limit = period * scale;
    int add = (int)((f32)game->graph->dt_num_60fps_frames * (f32)scale);

    if (add <= 0 && game->graph->dt_num_60fps_frames > 0.0) {
        add = 1;
    }

    *phase += add;
    while (*phase >= limit) {
        *phase -= limit;
    }

    return *phase / scale;
}

static inline void aINS_dt_dec_s32_timer(GAME* game, int* timer, f32* accum) {
    int ticks;

    *accum += (f32)game->graph->dt_num_60fps_frames;
    ticks = (int)*accum;

    if (ticks > 0) {
        *accum -= (f32)ticks;
        *timer -= ticks;

        if (*timer < 0) {
            *timer = 0;
            *accum = 0.0f;
        }
    }
}

static inline void aINS_dt_dec_s16_timer(GAME* game, s16* timer, f32* accum) {
    int value = *timer;

    aINS_dt_dec_s32_timer(game, &value, accum);
    *timer = (s16)value;
}

/* sizeof(aINS_INSECT_ACTOR) == 0x288 */
typedef struct insect_actor_s {
    TOOLS_ACTOR tools_actor; /* why tools actor? */
    int exist_flag;
    int type;
    aINS_MOVE_PROC move_proc;
    int action;
    aINS_ACTION_PROC action_proc;
    f32 _1E0;
    f32 _1E4;
    f32 speed_step;
    f32 target_speed;
    f32 patience;
    ClObjPipe_c col_pipe;
    f32 bg_range;
    f32 bg_height;
    int bg_type;
    mActor_name_t item;
    struct {
        u8 destruct : 1;
        u8 bit_1 : 1;
        u8 bit_2 : 1;
        u8 bit_3 : 1;
        u8 bit_4 : 1;
        u8 bit_5 : 1;
        u8 bit_6 : 1;
        u8 bit_7 : 1;
    } insect_flags;
    f32 life_time;
    f32 alpha_time;
    f32 timer;
    int continue_timer;
    int flag;

    /* Dynamic for each insect actor type */
    int s32_work0;
    int s32_work1;
    int s32_work2;
    int s32_work3;

    f32 f32_work0;
    f32 f32_work1;
    f32 f32_work2;
    f32 f32_work3;

    int _254;
    int _258;
    int alpha0;
    int alpha1;
    int alpha2;
    s16 ut_x;
    s16 ut_z;

    Lights point_light;
    Light_list* light_list;
    int light_flag;
    s16 light_counter;
    s16 light_step;
#ifdef TARGET_PC
    /* The cockroach actor stores an item pointer in s32_work3 on GameCube. */
    mActor_name_t* pc_item_p;
#endif
} aINS_INSECT_ACTOR;

/* sizeof(aINS_CTRL_ACTOR) == 0x183C */
typedef struct insect_ctrl_actor_s {
    ACTOR actor_class;
    aINS_INSECT_ACTOR insect_actor[aINS_ACTOR_NUM];
} aINS_CTRL_ACTOR;

/* sizeof(aINS_overlay_entry_c) == 0x1C08 */
typedef struct insect_overlay_s {
    ATTRIBUTE_ALIGN(8) u8 data[0x1C00];
    int _1C00;
    int _1C04;
} aINS_overlay_entry_c;

typedef struct {
    aINS_overlay_entry_c entries[3];
} aINS_overlay_c;

enum {
    aINS_PL_ACT_NONE,
    aINS_PL_ACT_REFLECT_AXE,
    aINS_PL_ACT_REFLECT_SCOOP,
    aINS_PL_ACT_DIG_SCOOP,
    aINS_PL_ACT_SHAKE_TREE,

    aINS_PL_ACT_NUM
};

typedef ACTOR* (*aINS_make_insect_proc)(aINS_Init_c*, int);
typedef void (*aINS_make_ant_proc)(aINS_Init_c*, s8, s8);
typedef void (*aINS_dt_proc)(ACTOR*, GAME*);
typedef ACTOR* (*aINS_make_actor_proc)(GAME*, int, xyz_t*);
typedef void (*aINS_set_pl_act_tim_proc)(int, int, int);
typedef int (*aINS_chk_live_insect_proc)(int, int, GAME*);
typedef void (*aINS_position_move_proc)(ACTOR*);
typedef ACTOR* (*aINS_search_near_insect_proc)(f32, f32, GAME*);

/* sizeof(aINS_Clip_c) == 0x50 */
typedef struct ac_insect_clip_s {
    /* 0x00 */ aINS_make_insect_proc make_insect_proc;
    /* 0x04 */ aINS_make_ant_proc make_ant_proc; // unused clip proc in AC
    /* 0x08 */ void* unused_08;
    /* 0x0C */ aINS_dt_proc dt_proc;
    /* 0x10 */ aINS_make_actor_proc make_actor_proc;
    /* 0x14 */ aINS_set_pl_act_tim_proc set_pl_act_tim_proc;
    /* 0x18 */ aINS_chk_live_insect_proc chk_live_insect_proc;
    /* 0x1C */ aINS_search_near_insect_proc search_near_insect_proc;
    /* 0x20 */ int pl_action;
    /* 0x24 */ int pl_action_ut_x;
    /* 0x28 */ int pl_action_ut_z;
    /* 0x2C */ aINS_position_move_proc position_move_proc;
    /* 0x30 */ int ant_spawn_pending;
    /* 0x34 */ aINS_Init_c ant_spawn_info;
    /* 0x4C */ s8 ant_bx;
    /* 0x4D */ s8 ant_bz;
} aINS_Clip_c;

/* must include m_common_data.h to use this macro */
#define aINS_CLIP (Common_Get(clip).insect_clip)

#ifdef __cplusplus
}
#endif

#endif

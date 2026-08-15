#ifndef AC_GYOEI_H
#define AC_GYOEI_H

#include "types.h"
#include "ac_tools.h"
#include "ac_gyoei_h.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aGYO_MAX_GYOEI 2
#define aGYO_EXIST_MAX 4

enum {
    aGYO_GYO_TYPE_TEST,
    aGYO_GYO_TYPE_KASEKI,

    aGYO_GYO_TYPE_NUM
};

enum {
    aGYO_ROD_NORMAL,
    aGYO_ROD_GOLDEN,

    aGYO_ROD_NUM
};

enum {
    aGYO_DRAW_TYPE_GYOEI,
    aGYO_DRAW_TYPE_FISH,

    aGYO_DRAW_TYPE_NUM
};

/* TODO: should we use the internal names for fish? */
enum fish_type {
    aGYO_TYPE_CRUCIAN_CARP,
    aGYO_TYPE_BROOK_TROUT,
    aGYO_TYPE_CARP,
    aGYO_TYPE_KOI,
    aGYO_TYPE_CATFISH,
    aGYO_TYPE_SMALL_BASS,
    aGYO_TYPE_BASS,
    aGYO_TYPE_LARGE_BASS,
    aGYO_TYPE_BLUEGILL,
    aGYO_TYPE_GIANT_CATFISH,
    aGYO_TYPE_GIANT_SNAKEHEAD,
    aGYO_TYPE_BARBEL_STEED,
    aGYO_TYPE_DACE,
    aGYO_TYPE_PALE_CHUB,
    aGYO_TYPE_BITTERLING,
    aGYO_TYPE_LOACH,
    aGYO_TYPE_POND_SMELT,
    aGYO_TYPE_SWEETFISH,
    aGYO_TYPE_CHERRY_SALMON,
    aGYO_TYPE_LARGE_CHAR,
    aGYO_TYPE_RAINBOW_TROUT,
    aGYO_TYPE_STRINGFISH,
    aGYO_TYPE_SALMON,
    aGYO_TYPE_GOLDFISH,
    aGYO_TYPE_PIRANHA,
    aGYO_TYPE_AROWANA,
    aGYO_TYPE_EEL,
    aGYO_TYPE_FRESHWATER_GOBY,
    aGYO_TYPE_ANGELFISH,
    aGYO_TYPE_GUPPY,
    aGYO_TYPE_POPEYED_GOLDFISH,
    aGYO_TYPE_COELACANTH,
    aGYO_TYPE_CRAWFISH,
    aGYO_TYPE_FROG,
    aGYO_TYPE_KILLIFISH,
    aGYO_TYPE_JELLYFISH,
    aGYO_TYPE_SEA_BASS,
    aGYO_TYPE_RED_SNAPPER,
    aGYO_TYPE_BARRED_KNIFEJAW,
    aGYO_TYPE_ARAPAIMA,

    aGYO_TYPE_NUM,

    /* non-fish fish */
    aGYO_TYPE_WHALE = aGYO_TYPE_NUM,
    aGYO_TYPE_EMPTY_CAN,
    aGYO_TYPE_BOOT,
    aGYO_TYPE_OLD_TIRE,
    aGYO_TYPE_SALMON2,

    aGYO_TYPE_EXTENDED_NUM
};

#define aGYO_TYPE_INVALID -1

#define aGYO_IS_FISH_TRASH(type) ((type) >= aGYO_TYPE_EMPTY_CAN && (type) <= aGYO_TYPE_OLD_TIRE)

enum {
    aGYO_SIZE_XXS,
    aGYO_SIZE_XS,
    aGYO_SIZE_S,
    aGYO_SIZE_M,
    aGYO_SIZE_L,
    aGYO_SIZE_XL,
    aGYO_SIZE_XXL,
    aGYO_SIZE_WHALE,

    aGYO_SIZE_NUM
};

typedef struct gyo_ctrl_actor_s aGYO_CTRL_ACTOR;

typedef void (*aGYO_ACT_PROC)(ACTOR*, GAME*);

/* sizeof(aGYO_CTRL_ACTOR) == 0x254 */
struct gyo_ctrl_actor_s {
    /* 0x000 */ TOOLS_ACTOR tools_class;
    /* 0x1CC */ ACTOR* linked_actor; /* Generally UKI_ACTOR */
    /* 0x1D0 */ int exist;
    /* 0x1D4 */ int draw_type;
    /* 0x1D8 */ int gyo_type;
    /* 0x1DC */ s16 size_type;
    /* 0x1E0 */ int action;
    /* 0x1E4 */ aGYO_ACT_PROC act_proc;
    /* 0x1E8 */ int anim_frame;
    /* 0x1EC */ f32 speed_step;
    /* 0x1F0 */ f32 speed;
    /* 0x1F4 */ f32 range;
    /* 0x1F8 */ int _1F8;
    /* 0x1FC */ ClObjPipe_c col_pipe;
    /* 0x218 */ int work0;
    /* 0x21C */ f32 fwork0;
    /* 0x220 */ f32 fwork1;
    /* 0x224 */ f32 fwork2;
    /* 0x228 */ f32 fwork3;
    /* 0x22C */ s16 swork0;
    /* 0x22E */ s16 swork1;
    /* 0x230 */ s16 swork2;
    /* 0x232 */ s16 swork3;
    /* 0x234 */ s16 swork4;
    /* 0x236 */ s16 move_counter;
    /* 0x238 */ s16 move_angle;
    /* 0x23A */ s16 pattern_subcounter;
    /* 0x23C */ s16 pattern_counter;
    /* 0x23E */ s16 touch_counter;
    /* 0x240 */ u16 gyo_flags;
    /* 0x242 */ u8 swim_flag;
    /* 0x243 */ u8 escape_flag;
    /* 0x244 */ int alpha;
    /* 0x248 */ int col_flags;
    /* 0x24C */ u8* overlay_p;
    /* 0x250 */ f32 draw_accum;
};

typedef struct gyoei_actor_s GYOEI_ACTOR;

/* sizeof(GYOEI_ACTOR) == 0x634 */
struct gyoei_actor_s {
    /* 0x000 */ ACTOR actor_class;
    /* 0x174 */ aGYO_CTRL_ACTOR ctrl[aGYO_MAX_GYOEI];
    /* 0x61C */ u8 exist[aGYO_EXIST_MAX];
    /* 0x620 */ int segment_type[aGYO_EXIST_MAX];
    /* 0x630 */ f32 logic_accum;
};

extern void aGTT_actor_init(ACTOR* actorx, GAME* game); // ac_gyo_test.c
extern void aGKK_actor_init(ACTOR* actorx, GAME* game); // ac_gyo_kaseki

extern ACTOR_PROFILE Gyoei_Profile;

#ifdef __cplusplus
}
#endif

#endif
